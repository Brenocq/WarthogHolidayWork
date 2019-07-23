#include "robot.h"

Robot::Robot(QGraphicsScene *_scene, int _id, int _team):
    Player(_id, _team)
{
    scene = _scene;

    QBrush bodyBrush(QColor(150,150,150));
    QBrush blueBrush(QColor(50,50,200));
    QBrush redBrush(QColor(200,50,50));

    QBrush *headBrush;
    if(team==blue){
        headBrush = new QBrush(blueBrush);
    }else{
        headBrush = new QBrush(redBrush);
    }

    QPen outlinePen(QColor(0,0,0,0));// Without outline

    // Create robot graphical items
    body = scene->addEllipse(-radius, -radius, radius*2, radius*2, outlinePen, bodyBrush);
    head = scene->addEllipse(-7, -7, 14, 14, outlinePen, *headBrush);
    head->setParentItem(body);
    //head->setX(cos(0)*7-7);
    //head->setY(sin(0)*7);
}

void Robot::update()
{
    draw();
}

void Robot::draw()
{
    Player::draw();
    if(team==blue){
        head->setX(cos(pos->getAngle()/180*M_PI)*14);
        head->setY(sin(pos->getAngle()/180*M_PI)*14);
    }else if(team==red){
        head->setX(cos((pos->getAngle()-180)/180*M_PI)*14);
        head->setY(sin((pos->getAngle()-180)/180*M_PI)*14);
    }
}
