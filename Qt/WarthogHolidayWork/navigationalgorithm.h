#ifndef NAVIGATIONALGORITHM_H
#define NAVIGATIONALGORITHM_H
#include "position.h"
#include "player.h"
#include <QVector>

class NavigationAlgorithm
{
public:
    NavigationAlgorithm(Position* _start, Position* _end);
    virtual ~NavigationAlgorithm()=0;

    virtual void generatePath()=0;
    Position nextPos();
    //----- Getters and Setters -----//
    QVector<Player> getObstacles() const;
    void setObstacles(const QVector<Player> &value);
    QVector<Position*> getPath() const;

private:
    Position* start;
    Position* end;
    QVector<Player> obstacles;
    QVector<Position*> path;
};

#endif // NAVIGATIONALGORITHM_H
