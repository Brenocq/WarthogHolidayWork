#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // Create scene
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QColor(90,255,90));

    // Update comboBox
    ui->teamComboBox->addItem("Blue");
    ui->teamComboBox->addItem("Red");
    ui->navComboBox->addItem("PF");
    ui->navComboBox->addItem("A*");
    for (int i=0;i<4;i++) {
        ui->numberComboBox->addItem("Robot " + QString::number(i));
    }

    // Create teams
    teams[0] = new Team(scene, 4, blue);
    teams[1] = new Team(scene, 4, red);

    // Execute update every 20ms
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);

    // Create selection ellipse
    QBrush infillBrush(QColor(0,0,0,0));// Without infill
    QPen outlinePen(QColor(255,0,0,255));// Red
    selection = scene->addEllipse(0, 0, 60, 60, outlinePen, infillBrush);

    // Create destination square
    infillBrush.setColor(QColor(255,0,255));//   Magenta infill
    outlinePen.setColor(QColor(255,0,0,255));//  Without outline
    destination = scene->addRect(-5, -5, 10, 10, outlinePen, infillBrush);
    destination->setFlag(QGraphicsItem::ItemIsMovable, true);

    // Update selected robot
    connect(ui->teamComboBox, SIGNAL(activated(int)), this, SLOT(updatePathPlanning()));
    connect(ui->numberComboBox, SIGNAL(activated(int)), this, SLOT(updatePathPlanning()));
    updatePathPlanning();
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::update(){
    // Update teams position
    teams[0]->update();
    teams[1]->update();
    // Update UI interface
    updatePathPlanning();
}

void Dialog::updatePathPlanning()
{
    int teamNum;
    QString textRobotNum;
    int robotNum;
    Position iniPos(0,0,0);
    Position endPos(0,0,0);

    ui->teamComboBox->currentText()=="Blue"? teamNum=blue: teamNum=red ;
    textRobotNum = ui->numberComboBox->currentText();
    robotNum = textRobotNum.split(" ")[1].toInt();

    if(teamNum==blue){
        iniPos.setX(int(teams[teamNum]->getRobot(robotNum)->getPos()->getX()));
        iniPos.setY(int(teams[teamNum]->getRobot(robotNum)->getPos()->getY()));
        endPos.setX(int(destination->pos().x()));
        endPos.setY(int(destination->pos().y()));

    }else{
        iniPos.setX(-int(teams[teamNum]->getRobot(robotNum)->getPos()->getX()));
        iniPos.setY(-int(teams[teamNum]->getRobot(robotNum)->getPos()->getY()));
        endPos.setX(-int(destination->pos().x()));
        endPos.setY(-int(destination->pos().y()));
    }
    selection->setX(int(iniPos.getX()-30));
    selection->setY(int(iniPos.getY()-30));
    ui->pathLabel->setText("(" +
                           QString::number(int(iniPos.getX()))+
                           ","+
                           QString::number(int(iniPos.getY()))+
                           ") -> ("+
                           QString::number(int(endPos.getX()))+
                           ","+
                           QString::number(int(endPos.getY()))+
                           ")");

}
