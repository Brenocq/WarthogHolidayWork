#include "navigationalgorithm.h"

NavigationAlgorithm::NavigationAlgorithm(Position* _start, Position* _end):
    start(_start), end(_end)
{

}

Position NavigationAlgorithm::nextPos()
{
    return *(path.back());
}

//----- Getters and Setters -----//
QVector<Player> NavigationAlgorithm::getObstacles() const
{
    return obstacles;
}

void NavigationAlgorithm::setObstacles(const QVector<Player> &value)
{
    obstacles = value;
}

QVector<Position*> NavigationAlgorithm::getPath() const
{
    return path;
}
