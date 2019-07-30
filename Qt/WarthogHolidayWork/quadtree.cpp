#include "quadtree.h"

QuadTree::QuadTree(QPoint _center, int _width, int _height, int _nodeCapacity, QGraphicsScene *_scene):
    width(_width), height(_height),
    nodeCapacity(_nodeCapacity),isSubdivaded(false),scene(_scene)
{
    center = new QPoint();
    center->setX(_center.x());
    center->setY(_center.y());
}

bool QuadTree::insert(QPoint *point)
{
    if(!containPoint(point)){
        return false;
    }
    //qDebug() <<"("<<center->x()<<","<<center->y()<<") p:"<< points.size();
    if(points.size()<nodeCapacity){
        points+=point;
        return true;
    }else{
        if(!isSubdivaded) subdivide();

        if (northEast->insert(point)) return true;
        if (northWest->insert(point)) return true;
        if (southEast->insert(point)) return true;
        if (southWest->insert(point)) return true;
        return false;
    }
}

void QuadTree::subdivide()
{
    isSubdivaded = true;
    QPoint subCenter;

    subCenter.setX(center->x()+width/4);
    subCenter.setY(center->y()+height/4);
    northEast = new QuadTree(subCenter,width/2,height/2,nodeCapacity,scene);

    subCenter.setX(center->x()-width/4);
    subCenter.setY(center->y()+height/4);
    northWest = new QuadTree(subCenter,width/2,height/2,nodeCapacity,scene);

    subCenter.setX(center->x()+width/4);
    subCenter.setY(center->y()-height/4);
    southEast = new QuadTree(subCenter,width/2,height/2,nodeCapacity,scene);

    subCenter.setX(center->x()-width/4);
    subCenter.setY(center->y()-height/4);
    southWest = new QuadTree(subCenter,width/2,height/2,nodeCapacity,scene);
}

bool QuadTree::containPoint(QPoint *point)
{
    return ((point->x()>=center->x()-width/2) && (point->x()<=center->x()+width/2))&&
           ((point->y()>=center->y()-height/2) && (point->y()<=center->y()+height/2));
}

void QuadTree::draw()
{
    //qDebug()<<"("<<center->x()<<","<<center->y()<<") h:"<<height<<" w:"<<width;
    QBrush infillBrush(QColor(0,0,0,0));// Without infill
    QPen outlinePen(QColor(0,0,0,255));// Black
    rect = scene->addRect(center->x()-width/2, center->y()-height/2, width, height, outlinePen, infillBrush);

    if(isSubdivaded){
        northEast->draw();
        northWest->draw();
        southEast->draw();
        southWest->draw();
    }
}

void QuadTree::noDraw()
{
    scene->removeItem(rect);

    if(isSubdivaded){
        northEast->noDraw();
        northWest->noDraw();
        southEast->noDraw();
        southWest->noDraw();
    }
}

void QuadTree::setScene(QGraphicsScene *value)
{
    scene = value;
}
