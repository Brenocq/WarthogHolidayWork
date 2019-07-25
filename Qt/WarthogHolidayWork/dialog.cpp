#include "dialog.h"
#include "ui_dialog.h"
#include "straightline.h"

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
    ui->navComboBox->addItem("A*");
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
    timerMove->start(100);

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
    for (int i=0;i<qtdRobots*2;i++) {
        QVector<QGraphicsLineItem*> linesPath;
        lines.push_back(linesPath);
    }

    // Update selected robot
    connect(ui->teamComboBox, SIGNAL(activated(int)), this, SLOT(updatePathPlanning()));
    connect(ui->numberComboBox, SIGNAL(activated(int)), this, SLOT(updatePathPlanning()));
    connect(ui->runButton, SIGNAL (released()),this, SLOT (runOrPause()));
    updatePathPlanning();
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
    //----- Update square position -----//
    if(lastTeamNum!=teamNum || lastRobotNum!=robotNum){
        Position* pos = teams[teamNum]->getRobot(robotNum)->getNavAlg()->getEnd();
        if(teamNum==0){
            destination->setX(int(pos->getX()));
            destination->setY(int(pos->getY()));
        }else{
            destination->setX(int(-pos->getX()));
            destination->setY(int(-pos->getY()));
        }
        lastTeamNum = teamNum;
        lastRobotNum = robotNum;
    }

    if(teamNum==blue){
        iniPos->setX(int(teams[teamNum]->getRobot(robotNum)->getPos()->getX()));
        iniPos->setY(int(teams[teamNum]->getRobot(robotNum)->getPos()->getY()));
        endPos->setX(int(destination->pos().x()));
        endPos->setY(int(destination->pos().y()));

    }else{
        iniPos->setX(-int(teams[teamNum]->getRobot(robotNum)->getPos()->getX()));
        iniPos->setY(-int(teams[teamNum]->getRobot(robotNum)->getPos()->getY()));
        endPos->setX(-int(destination->pos().x()));
        endPos->setY(-int(destination->pos().y()));
    }
    selection->setX(int(iniPos->getX()-30));
    selection->setY(int(iniPos->getY()-30));
    ui->pathLabel->setText("(" +
                           QString::number(int(iniPos->getX()))+
                           ","+
                           QString::number(int(iniPos->getY()))+
                           ") -> ("+
                           QString::number(int(endPos->getX()))+
                           ","+
                           QString::number(int(endPos->getY()))+
                           ")");

    teams[teamNum]->getRobot(robotNum)->setDestination(endPos);
    if(strNavAlg=="Straight Line"){
        teams[teamNum]->getRobot(robotNum)->setNavAlg(new StraightLine());
    }else if(strNavAlg == "PF"){

    }else if(strNavAlg == "A*"){

    }
}

void Dialog::showPaths()
{
    // Path blue team
    Robot* robot;
    for(int i=0;i<qtdRobots;i++) {
        robot = teams[0]->getRobot(i);
        QVector<Position*> path = robot->getNavAlg()->getPath();
        int pathSize = path.size();

        // Clear old lines
        for (int j=0;j<lines[i].size();j++) {
            scene->removeItem(lines[i][j]);
        }
        lines[i].clear();
        for (int j=1;j<pathSize;j++) {
            Position* pos1 = path[pathSize-j];
            Position* pos2 = path[pathSize-j-1];
            QLineF line(qreal(pos1->getX()),qreal(pos1->getY()) , qreal(pos2->getX()),qreal(pos2->getY()));
            QPen linePen(QColor(0,0,255,255));

            lines[i].push_back(scene->addLine(line, linePen));
        }
    }
    // Path red team
    for(int i=0;i<qtdRobots;i++) {
        robot = teams[1]->getRobot(i);
        QVector<Position*> path = robot->getNavAlg()->getPath();
        int pathSize = path.size();

        // Clear old lines
        for (int j=0;j<lines[i+qtdRobots].size();j++) {
            scene->removeItem(lines[i+qtdRobots][j]);
        }
        lines[i+qtdRobots].clear();
        for (int j=1;j<pathSize;j++) {
            Position* pos1 = path[pathSize-j];
            Position* pos2 = path[pathSize-j-1];
            QLineF line(qreal(-pos1->getX()),qreal(-pos1->getY()) , qreal(-pos2->getX()),qreal(-pos2->getY()));
            QPen linePen(QColor(255,0,0,255));

            lines[i+qtdRobots].push_back(scene->addLine(line, linePen));
        }
    }
}

void Dialog::runOrPause()
{
    isRunning=!isRunning;
}
