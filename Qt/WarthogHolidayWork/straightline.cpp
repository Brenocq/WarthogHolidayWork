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
    path.clear();
    float distance = start->distanceTo(*end);
    int resolution = 100;// Number of points in the path
    QVector2D startV2;
    startV2 = end->toVector()-start->toVector();
    startV2.normalize();
    startV2 = startV2*distance/resolution;

    Position *nextPos = new Position(start->getX()+startV2.x(),start->getY()+startV2.y(),0);
    path.push_back(nextPos);
    for (int i=0;i<resolution;i++) {
        nextPos = new Position(0,0,0);
        nextPos->setNewPosition(path.back()->getX()+startV2.x(),
                               path.back()->getY()+startV2.y(),
                               0);
        path+=nextPos;
    }
}
