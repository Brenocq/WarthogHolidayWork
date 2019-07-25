#include "position.h"
#include <QtMath>

Position::Position(float _x, float _y, float _angle):
    x(_x),y(_y),angle(_angle)
{
    angle<0?angle+=360:angle;
    angle>360?angle-=360:angle;
}

float Position::distanceTo(Position other)
{
    float dX = getX()-other.getX();
    float dY = getY()-other.getY();
    return float( qSqrt(qreal(dX*dX+dY*dY)) );
}

QVector2D Position::toVector()
{
    QVector2D result(getX(),getY());
    return result;
}

//----- Getters and Setters -----//
float Position::getX() const
{
    return x;
}

void Position::setX(float value)
{
    x = value;
}

float Position::getY() const
{
    return y;
}

void Position::setY(float value)
{
    y = value;
}

float Position::getAngle() const
{
    return angle;
}

void Position::setAngle(float value)
{
    angle = value;
    angle<0?angle+=360:angle;
    angle>360?angle-=360:angle;
}

void Position::setNewPosition(float _x, float _y, float _angle)
{
    x=_x;
    y=_y;
    angle=_angle;
}


