#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "navigationalgorithm.h"
#include "straightline.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QDebug>

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
    Position *getPos() const;
    void setPos(Position *value);
    NavigationAlgorithm *getNavAlg() const;
    void setNavAlg(NavigationAlgorithm *value);

protected:
    QGraphicsScene *scene;
    QGraphicsEllipseItem *body;
    Position* pos;
    NavigationAlgorithm *navAlg;

    int id;
    int team;
    int radius;
};

#endif // PLAYER_H
