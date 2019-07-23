#include "team.h"

Team::Team(QGraphicsScene *_scene, int _color):
    color(_color)
{
    for (int i=0;i<qtdRobots;i++) {
        robots[i] = new Robot(_scene,0,color);
    }
    Position newPos(0,0,0);

    for (int i=0;i<2;i++) {
        newPos.setNewPosition(-300,0,0);
        robots[0]->setPosition(newPos);
        newPos.setNewPosition(-150,150,-30);
        robots[1]->setPosition(newPos);
        newPos.setNewPosition(-150,-150,30);
        robots[2]->setPosition(newPos);
        newPos.setNewPosition(-50,0,0);
        robots[3]->setPosition(newPos);
    }

}

void Team::update()
{
    for (int i=0;i<qtdRobots;i++) {
        robots[i]->update();
    }
}
