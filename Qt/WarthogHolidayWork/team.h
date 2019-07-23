#ifndef TEAM_H
#define TEAM_H

#include <QGraphicsScene>
#include "robot.h"

class Team
{
public:
    Team(QGraphicsScene *_scene, int _color = blue);

    void update();
private:
    int qtdRobots = 4;
    Robot *robots[4];
    int color;
};

#endif // TEAM_H
