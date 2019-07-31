#include "straightline.h"

StraightLine::StraightLine():
     NavigationAlgorithm()
{

}

StraightLine::StraightLine(Position* _start, Position* _end):
    NavigationAlgorithm(_start,_end)
{

}

StraightLine::~StraightLine()
{
}

void StraightLine::generatePath()
{
    NavigationAlgorithm::generatePath();// Clean old path
    float distance = start->distanceTo(*end);
    int resolution = 20;// Number of points in the path
    QVector2D startV2;
    startV2 = start->toVector()-end->toVector();
    startV2.normalize();
    startV2 = startV2*distance/resolution;

    Position *nextPos = new Position(end->getX(),end->getY(),0);
    path.push_back(nextPos);
    for (int i=0;i<resolution;i++) {
        nextPos = new Position(0,0,0);
        nextPos->setNewPosition(path.back()->getX()+startV2.x(),
                               path.back()->getY()+startV2.y(),
                               0);
        path+=nextPos;
    }
}

void StraightLine::draw()
{

}

void StraightLine::clean()
{

}
