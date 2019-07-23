#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

enum teamColor{blue, red};

class Player
{
public:
    Player(int _id, int team);

    void draw();

    //----- Getters and Setters -----//
    void setPosition(Position newPos);
    int getId() const;
    void setId(int value);
    int getTeam() const;
    void setTeam(int value);
    int getRadius() const;
    void setRadius(int value);

protected:
    QGraphicsScene *scene;
    QGraphicsEllipseItem *body;
    Position* pos;

    int id;
    int team;
    int radius;
};

#endif // PLAYER_H
