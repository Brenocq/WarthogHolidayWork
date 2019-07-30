// dialog.h

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTimer>
#include <QVector>
#include "team.h"
#include "quadtree.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void update();
    void moveRobots();
    void updatePathPlanning();
    void showPaths();
    void runOrPause();

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *selection;
    QGraphicsRectItem *destination;
    QVector<QVector<QGraphicsLineItem*>> lines;
    QVector<QVector<QGraphicsEllipseItem*>> dots;
    QTimer *timer;
    QTimer *timerMove;
    Robot *selectedRobot;
    int qtdRobots;
    Team *teams[2];
    QuadTree *qtree;
    bool isRunning;
};
#endif // DIALOG_H
