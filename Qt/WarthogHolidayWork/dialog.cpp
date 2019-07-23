#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QColor(90,255,90));

    teams[0] = new Team(scene, blue);
    teams[1] = new Team(scene, red);

    // Execute every 20ms
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::update(){
    teams[0]->update();
    teams[1]->update();
}
