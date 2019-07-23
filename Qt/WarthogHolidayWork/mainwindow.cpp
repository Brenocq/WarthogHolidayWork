#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(paintEvent()));
    timer->start(1000); //time specified in ms
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);//ui->gameScreen
    QPen pen;
    penColor = QColor(0,255,0,255);
    pen.setColor(penColor); //note this
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    QDesktopWidget dw;
    int width = int(dw.width()*0.6-1);
    int height = int(width*0.5);
    painter.drawRect(QRect(0,0,width,height));
    drawRobot();
}

void MainWindow::drawRobot(){
    static int _x=30;
    static int _y=30;
    QPainter painter(this);//ui->gameScreen
    QPen pen;
    penColor = QColor(0,0,0,255);
    pen.setColor(penColor); //note this
    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    painter.setPen(pen);
    QDesktopWidget dw;
    painter.drawEllipse(_x,_y,21,21);
    _x+=30;
    qDebug() << "...";
}
