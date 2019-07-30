#ifndef ASTAR_H
#define ASTAR_H
#include "navigationalgorithm.h"
#include "quadtree.h"

class AStar: public NavigationAlgorithm
{
public:
    AStar();
    AStar(Position* _start, Position* _end);
    ~AStar();
    void discretizeWorld();
    void generatePath();
    void setScene(QGraphicsScene *value);

private:
    QuadTree *qTree;
    QGraphicsScene *scene;
};

#endif // ASTAR_H
