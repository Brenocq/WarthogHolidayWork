#ifndef POSITION_H
#define POSITION_H
#include <QVector2D>

enum teamColor{blue, red};

class Position
{
public:
    Position(float _x, float _y, float _angle);
    float distanceTo(Position other);
    float angleTo(Position other);
    QVector2D toVector();
    //----- Getters and Setters -----//
    float getX() const;
    void setX(float value);
    float getY() const;
    void setY(float value);
    float getAngle() const;
    void setAngle(float value);
    void setNewPosition(float _x, float _y, float _angle);
    int getTeam() const;
    void setTeam(int value);

private:
    float x;
    float y;
    float angle;
    int team;// Position relative to the team
};

#endif // POSITION_H
