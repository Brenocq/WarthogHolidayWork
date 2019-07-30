#include "astar.h"

AStar::AStar():
    NavigationAlgorithm()
{
    // Create new QuadTree
    QPoint centerScreen(0,0);
    qTree = new QuadTree(centerScreen, 700,500,3,scene);

}

AStar::AStar(Position *_start, Position *_end):
    NavigationAlgorithm(_start,_end)
{
    // Create new QuadTree
    QPoint centerScreen(0,0);
    qTree = new QuadTree(centerScreen, 700,500,3,scene);

}

AStar::~AStar()
{
}

void AStar::discretizeWorld()
{
    // Delete old QuadTree
    qTree->draw();
    qTree->noDraw();
    delete qTree;
    QPoint centerScreen(0,0);
    qTree = new QuadTree(centerScreen, 700,500,3,scene);

    // Add Points to the QuadTree
    int resolution = 50;
    int radius = 25;
    for (Position* obstacle : obstacles) {
        for (double i=0;i<M_PI*2;i+=M_PI*2/resolution) {
            QPoint point(obstacle->getX()+qCos(i)*radius, obstacle->getY()+qSin(i)*radius);
            if(start->getTeam() != obstacle->getTeam()){
                point.setX(-point.x());
                point.setY(-point.y());
            }

            qTree->insert(&point);
        }
    }
    qTree->draw();
}

void AStar::generatePath()
{
    discretizeWorld();
}

void AStar::setScene(QGraphicsScene *value)
{
    scene = value;
    qTree->setScene(scene);
}
