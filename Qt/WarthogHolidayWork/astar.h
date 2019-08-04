#ifndef ASTAR_H
#define ASTAR_H
#include "navigationalgorithm.h"
#include "quadtree.h"

typedef struct _node Node;

struct _node{
    QuadTree *qTree;
    float f;
    float g;
    float h;
    bool prevConnected=true;
    Node *prevNode;
};

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
    void drawOpenClose(QVector<Node*> openList,  QVector<Node*> closedList);
    void clean();

private:
    QuadTree *qTree;
    QVector<Node*> openList;
    QVector<Node*> closedList;

    QGraphicsScene *scene;
    QVector<QGraphicsEllipseItem*> dots;
    QVector<QGraphicsRectItem*> rectangles;
};

#endif // ASTAR_H
