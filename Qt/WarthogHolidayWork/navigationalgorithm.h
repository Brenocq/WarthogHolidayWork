#ifndef NAVIGATIONALGORITHM_H
#define NAVIGATIONALGORITHM_H
#include "position.h"
#include <QVector>
#include <QDebug>
#include <QtMath>

class NavigationAlgorithm
{
public:
    NavigationAlgorithm();
    NavigationAlgorithm(Position* _start, Position* _end);
    virtual ~NavigationAlgorithm();

    virtual void generatePath();
    Position nextPos();
    //----- Getters and Setters -----//
    QVector<Position*> getObstacles() const;
    void setObstacles(const QVector<Position*> &value);
    QVector<Position*> getPath() const;
    Position *getStart() const;
    void setStart(Position *value);
    void setEnd(Position *value);
    Position *getEnd() const;

protected:
    Position* start;
    Position* end;
    QVector<Position*> obstacles;
    QVector<Position*> path;
};

#endif // NAVIGATIONALGORITHM_H
