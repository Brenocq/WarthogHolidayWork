#include "navigationalgorithm.h"

NavigationAlgorithm::NavigationAlgorithm()
{

}

NavigationAlgorithm::NavigationAlgorithm(Position* _start, Position* _end):
    start(_start), end(_end)
{
}

NavigationAlgorithm::~NavigationAlgorithm()
{

}

void NavigationAlgorithm::generatePath()
{

}

Position NavigationAlgorithm::nextPos()
{
    return *(path.back());
}

//----- Getters and Setters -----//
QVector<Position*> NavigationAlgorithm::getObstacles() const
{
    return obstacles;
}

void NavigationAlgorithm::setObstacles(const QVector<Position*> &value)
{
    obstacles = value;
}

QVector<Position*> NavigationAlgorithm::getPath() const
{
    return path;
}

void NavigationAlgorithm::setStart(Position *value)
{
    start = value;
}

void NavigationAlgorithm::setEnd(Position *value)
{
    end = value;
}

Position *NavigationAlgorithm::getStart() const
{
    return start;
}

Position *NavigationAlgorithm::getEnd() const
{
    return end;
}
