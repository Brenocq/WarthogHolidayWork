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
    ~QuadTree();
    bool insert(QPoint *point);
    void subdivide();
    bool containPoint(QPoint *point);
    QuadTree* getQtreeAtPoint(QPoint *point);
    QVector<QuadTree *> neighbors(QRect *rect);
    bool intersects(QRect *rect);


    void draw();
    void clean();
    //----- Getters and Setters -----//
    void setScene(QGraphicsScene *value);
    QPoint *getCenter() const;
    int getWidth() const;
    int getHeight() const;
    QVector<QPoint *> getPoints() const;

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
    bool drawn;

    QGraphicsScene *scene;
    QGraphicsRectItem *rect;
};

#endif // QUADTREE_H
