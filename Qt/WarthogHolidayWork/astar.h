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
    void draw();
    void clean();

private:
    QuadTree *qTree;
    QGraphicsScene *scene;
    QVector<QGraphicsEllipseItem*> dots;
};

#endif // ASTAR_H
