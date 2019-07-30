#ifndef QUADTREE_H
#define QUADTREE_H
#include <QVector>
#include <QPoint>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

class QuadTree
{
public:
    QuadTree(QPoint _center, int _width, int _height, int _nodeCapacity, QGraphicsScene *_scene);

    bool insert(QPoint *point);
    void subdivide();
    bool containPoint(QPoint *point);

    void draw();
    void noDraw();
    void setScene(QGraphicsScene *value);

private:
    // Rect info
    QPoint *center;
    int width;
    int height;
    // Points info
    int nodeCapacity;
    QVector<QPoint*> points;
    // Children
    QuadTree* northEast;
    QuadTree* northWest;
    QuadTree* southEast;
    QuadTree* southWest;
    bool isSubdivaded;

    QGraphicsScene *scene;
    QGraphicsRectItem *rect;
};

#endif // QUADTREE_H
