#ifndef POSITION_H
#define POSITION_H


class Position
{
public:
    Position(float _x, float _y, float _angle);


    //----- Getters and Setters -----//
    float getX() const;
    void setX(float value);
    float getY() const;
    void setY(float value);
    float getAngle() const;
    void setAngle(float value);
    void setNewPosition(float _x, float _y, float _angle);

private:
    float x;
    float y;
    float angle;
};

#endif // POSITION_H
