#include "dialog.h"
#include "ui_dialog.h"
#include "straightline.h"
#include "potentialfield.h"
#include "astar.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    qtdRobots(4), isRunning(false)
{
    ui->setupUi(this);

    // Create scene
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QColor(90,255,90));

    // Update comboBox
    ui->teamComboBox->addItem("Blue");
    ui->teamComboBox->addItem("Red");
    ui->navComboBox->addItem("Straight Line");
    ui->navComboBox->addItem("PF");
    ui->navComboBox->addItem("QuadTree + A*");
    for (int i=0;i<4;i++) {
        ui->numberComboBox->addItem("Robot " + QString::number(i));
    }

    // Create teams
    teams[0] = new Team(scene, qtdRobots, blue);
    teams[1] = new Team(scene, qtdRobots, red);

    // Execute update every 20ms
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);
    // Move every 20ms
    timerMove = new QTimer(this);
    QObject::connect(timerMove, SIGNAL(timeout()), this, SLOT(moveRobots()));
    timerMove->start(20);

    // Create selection ellipse
    QBrush infillBrush(QColor(0,0,0,0));// Without infill
    QPen outlinePen(QColor(255,0,0,255));// Red
    selection = scene->addEllipse(0, 0, 60, 60, outlinePen, infillBrush);

    // Create destination square
    infillBrush.setColor(QColor(255,0,255));//   Magenta infill
    outlinePen.setColor(QColor(255,0,0,255));//  Without outline
    destination = scene->addRect(-5, -5, 10, 10, outlinePen, infillBrush);
    destination->setFlag(QGraphicsItem::ItemIsMovable, true);

    // Create path lines
    lines.resize(qtdRobots*2);
    dots.resize(qtdRobots*2);

    // Update selected robot
    connect(ui->teamComboBox, SIGNAL(activated(int)), this, SLOT(updatePathPlanning()));
    connect(ui->numberComboBox, SIGNAL(activated(int)), this, SLOT(updatePathPlanning()));
    connect(ui->runButton, SIGNAL (released()),this, SLOT (runOrPause()));
    updatePathPlanning();

    //----- Update obstacles -----//
    for (int i=0;i<qtdRobots*2;i++){
        QVector<Position*> *robotObstacles = new QVector<Position*>;// Position of all robots except robot i
        int team = blue;
        int robotNum = i;
        if(i>=qtdRobots){
            robotNum-=qtdRobots;
            team = red;
        }
        for (int j=0;j<qtdRobots*2;j++){
            if(j!=i){
                int obsTeam = blue;// Obstacle team
                int obsNum = j;
                if(j>=qtdRobots){
                    obsNum-=qtdRobots;
                    obsTeam = red;
                }

                Robot *obsRobot = teams[obsTeam]->getRobot(obsNum);
                Position *obsPos = obsRobot->getPos();
                robotObstacles->push_back(obsPos);
            }
        }
        Robot *robot = teams[team]->getRobot(robotNum);
        robot->getNavAlg()->setObstacles(*robotObstacles);
    }
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::update(){
    updatePathPlanning();
    // Update teams position
    teams[0]->update();
    teams[1]->update();
    selectedRobot->getNavAlg()->draw();
    // Update UI interface
    showPaths();
}

void Dialog::moveRobots()
{
    if(isRunning){
        for (int team=0;team<2;team++) {
            for(int robot=0;robot<qtdRobots;robot++){
                teams[team]->getRobot(robot)->move();
            }
        }
    }
}

void Dialog::updatePathPlanning(){
    static int lastTeamNum=-1;
    static int lastRobotNum=-1;
    static QString selectedNav = "Straight Line";
    //----- Define robot team and number -----//
    int teamNum;
    QString textRobotNum;
    int robotNum;
    QString strNavAlg = ui->navComboBox->currentText();
    Position *iniPos = new Position(0,0,0);
    Position *endPos = new Position(0,0,0);
    ui->teamComboBox->currentText()=="Blue"? teamNum=blue: teamNum=red ;
    textRobotNum = ui->numberComboBox->currentText();
    robotNum = textRobotNum.split(" ")[1].toInt();

    iniPos->setTeam(teamNum);
    endPos->setTeam(teamNum);
    selectedRobot=teams[teamNum]->getRobot(robotNum);
    //----- Update square position -----//
    if(lastTeamNum!=teamNum || lastRobotNum!=robotNum){
        Position* pos = selectedRobot->getNavAlg()->getEnd();
        if(teamNum==0){
            destination->setX(int(pos->getX()));
            destination->setY(int(pos->getY()));
        }else{
            destination->setX(int(-pos->getX()));
            destination->setY(int(-pos->getY()));
        }
    }

    if(teamNum==blue){
        iniPos->setX(int(selectedRobot->getPos()->getX()));
        iniPos->setY(int(selectedRobot->getPos()->getY()));
        endPos->setX(int(destination->pos().x()));
        endPos->setY(int(destination->pos().y()));

    }else{
        iniPos->setX(-int(selectedRobot->getPos()->getX()));
        iniPos->setY(-int(selectedRobot->getPos()->getY()));
        endPos->setX(-int(destination->pos().x()));
        endPos->setY(-int(destination->pos().y()));
    }
    ui->pathLabel->setText("(" +
                           QString::number(int(iniPos->getX()))+
                           ","+
                           QString::number(int(iniPos->getY()))+
                           ") -> ("+
                           QString::number(int(endPos->getX()))+
                           ","+
                           QString::number(int(endPos->getY()))+
                           ")");

    selectedRobot->setDestination(endPos);
    if(lastTeamNum!=teamNum || lastRobotNum!=robotNum || selectedNav!=strNavAlg){
        if(selectedNav==strNavAlg){
            ui->navComboBox->setCurrentIndex(selectedRobot->getSelectedNav());
        }

        if(lastTeamNum!=-1){
            teams[lastTeamNum]->getRobot(lastRobotNum)->getNavAlg()->clean();
        }

        if(strNavAlg=="Straight Line"){
            selectedRobot->setNavAlg(new StraightLine());
            selectedRobot->setSelectedNav(0);
        }else if(strNavAlg == "PF"){
            selectedRobot->setNavAlg(new PotentialField());
            selectedRobot->setSelectedNav(1);
        }else if(strNavAlg == "QuadTree + A*"){
            AStar *aStar = new AStar();
            aStar->setScene(scene);
            selectedRobot->setNavAlg(aStar);
            selectedRobot->setSelectedNav(2);
        }
    }

    lastTeamNum = teamNum;
    lastRobotNum = robotNum;
    selectedNav = strNavAlg;
}

void Dialog::showPaths()
{
    //----- Path blue team -----//
    Robot* robot;
    for(int i=0;i<qtdRobots;i++) {
        robot = teams[0]->getRobot(i);
        QVector<Position*> path = robot->getNavAlg()->getPath();
        int pathSize = path.size();

        // Clear old lines
        for (int j=0;j<lines[i].size();j++) {
            scene->removeItem(lines[i][j]);
            delete lines[i][j];
        }
        // Clear old dots
        for (int j=0;j<dots[i].size();j++) {
            scene->removeItem(dots[i][j]);
            delete dots[i][j];
        }
        lines[i].clear();
        dots[i].clear();
        for (int j=1;j<pathSize;j++) {
            Position* pos1 = path[pathSize-j];
            Position* pos2 = path[pathSize-j-1];
            QLineF line(qreal(pos1->getX()),qreal(pos1->getY()) , qreal(pos2->getX()),qreal(pos2->getY()));
            QPen linePen(QColor(0,0,255,255));
            QBrush circleBrush(QColor(50,50,200));

            lines[i].push_back(scene->addLine(line, linePen));
            dots[i].push_back(scene->addEllipse(pos1->getX()-2, pos1->getY()-2, 4, 4, linePen, circleBrush));
        }
    }
    //----- Path red team -----//
    for(int i=0;i<qtdRobots;i++) {
        robot = teams[1]->getRobot(i);
        QVector<Position*> path = robot->getNavAlg()->getPath();
        int pathSize = path.size();

        // Clear old lines
        for (int j=0;j<lines[i+qtdRobots].size();j++) {
            scene->removeItem(lines[i+qtdRobots][j]);
            delete lines[i+qtdRobots][j];
        }
        // Clear old dots
        for (int j=0;j<dots[i+qtdRobots].size();j++) {
            scene->removeItem(dots[i+qtdRobots][j]);
            delete dots[i+qtdRobots][j];
        }
        lines[i+qtdRobots].clear();
        dots[i+qtdRobots].clear();
        for (int j=1;j<pathSize;j++) {
            Position* pos1 = path[pathSize-j];
            Position* pos2 = path[pathSize-j-1];
            QLineF line(qreal(-pos1->getX()),qreal(-pos1->getY()) , qreal(-pos2->getX()),qreal(-pos2->getY()));
            QPen linePen(QColor(255,0,0,255));
            QBrush circleBrush(QColor(200,50,50));

            lines[i+qtdRobots].push_back(scene->addLine(line, linePen));
            dots[i+qtdRobots].push_back(scene->addEllipse(-pos1->getX()-2, -pos1->getY()-2, 4, 4, linePen, circleBrush));
        }
    }
    //----- Update selection circle -----//
    float selecX = selectedRobot->getPos()->getX();
    float selecY = selectedRobot->getPos()->getY();
    if(selectedRobot->getTeam()==red){
        selecX*=-1;
        selecY*=-1;
    }

    selection->setX(int(selecX-30));
    selection->setY(int(selecY-30));
}

void Dialog::runOrPause()
{
    isRunning=!isRunning;
    if(isRunning){
        ui->runButton->setText("Pause");
    }else{
        ui->runButton->setText("Run");
    }
}
