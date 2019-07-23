#ifndef ROBOT_H
#define ROBOT_H

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "player.h"

class Robot : public Player
{
public:
    Robot(QGraphicsScene *_scene, int _id, int _team);

    void update();
    void draw();
private:
    QGraphicsEllipseItem *head;
};

#endif // ROBOT_H
