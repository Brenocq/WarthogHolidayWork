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
    body->setFlag(QGraphicsItem::ItemIsMovable, true);
    body->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    head = scene->addEllipse(-7, -7, 14, 14, outlinePen, *headBrush);
    head->setParentItem(body);
    textId = scene->addText(QString::number(id));
    textId->setX(-8);
    textId->setY(-radius-20);
    textId->setParentItem(body);

    draw();
}

void Robot::update()
{
    // Update position if was moved by mouse
    if(team==blue){
        pos->setX(float(body->pos().x()));
        pos->setY(float(body->pos().y()));
    }else{
        pos->setX(float(-body->pos().x()));
        pos->setY(float(-body->pos().y()));
    }

    // Draw current robot
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

QVariant QGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();
        if (!rect.contains(newPos)) {
            // Keep the item inside the scene rect.
            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
            return newPos;
        }
    }
    return QGraphicsItem::itemChange(change, value);
}
