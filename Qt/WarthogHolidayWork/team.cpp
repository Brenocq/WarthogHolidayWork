#include "team.h"

Team::Team(QGraphicsScene *_scene, int _qtdRobots, int _color):
    color(_color), qtdRobots(_qtdRobots)
{
    // Create robots
    for (int i=0;i<qtdRobots;i++) {
        robots[i] = new Robot(_scene,i,color);
    }
    Position newPos(0,0,0);

    // Update position robots
    if(qtdRobots!=4){
        qDebug() << "Please change the robots initial position in teams.cpp";
    }
    newPos.setNewPosition(-300,0,0);
    robots[0]->setPosition(newPos);
    newPos.setNewPosition(-150,150,-30);
    robots[1]->setPosition(newPos);
    newPos.setNewPosition(-150,-150,30);
    robots[2]->setPosition(newPos);
    newPos.setNewPosition(-50,0,0);
    robots[3]->setPosition(newPos);

}

void Team::update()
{
    for (int i=0;i<qtdRobots;i++) {
        robots[i]->update();
    }
}

Robot* Team::getRobot(int id)
{
    return robots[id];
}
