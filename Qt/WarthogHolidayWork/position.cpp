#include "position.h"

Position::Position(float _x, float _y, float _angle):
    x(_x),y(_y),angle(_angle)
{
    angle<0?angle+=360:angle;
    angle>360?angle-=360:angle;
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


