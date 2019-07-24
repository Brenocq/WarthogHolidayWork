#ifndef TEAM_H
#define TEAM_H

#include <QGraphicsScene>
#include "robot.h"

class Team
{
public:
    Team(QGraphicsScene *_scene, int _qtdRobots, int _color = blue);

    void update();

    Robot* getRobot(int id);
private:
    const int qtdRobots;
    Robot* robots[10];
    int color;
};

#endif // TEAM_H
