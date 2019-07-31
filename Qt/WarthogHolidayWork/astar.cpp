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
    qTree->clean();
    delete qTree;
    QPoint centerScreen(0,0);
    qTree = new QuadTree(centerScreen, 700,500,1,scene);

    // Delete old points
    for(auto dot : dots){
        scene->removeItem(dot);
    }
    dots.clear();

    // Add Points to the QuadTree
    int resolution = 20;
    int radius = 25;
    for (Position* obstacle : obstacles) {
        for (double i=0;i<M_PI*2;i+=M_PI*2/resolution) {
            // Add point to Quad Tree
            QPoint point(obstacle->getX()+qCos(i)*radius, obstacle->getY()+qSin(i)*radius);
            if(start->getTeam() != obstacle->getTeam()){
                point.setX(-point.x());
                point.setY(-point.y());
            }
            qTree->insert(&point);

            // Draw point
            QBrush blackInfill(QColor(0,0,0));
            QPen outlinePen(QColor(0,0,0,0));// Without outline
            dots.push_back(scene->addEllipse(point.x(), point.y(), 3, 3, outlinePen, blackInfill));
        }
    }
}

void AStar::generatePath()
{
    NavigationAlgorithm::generatePath();
    discretizeWorld();

    // Start QTree
    QuadTree *startQTree;
    QPoint *point;
    point = new QPoint(start->getX(),start->getY());
    startQTree = qTree->getQtreeAtPoint(point);

    //Vector of neighbors
    QVector<QPoint *> neighbors;
    QRect *rect = new QRect(startQTree->getCenter()->x(),startQTree->getCenter()->y(),startQTree->getWidth()+6,startQTree->getHeight()+6);
    neighbors = qTree->neighbors(rect);



    qTree->draw();
}

void AStar::setScene(QGraphicsScene *value)
{
    scene = value;
    qTree->setScene(scene);
}

void AStar::draw()
{
    qTree->clean();
    qTree->draw();
}

void AStar::clean()
{
    qTree->clean();
    // Delete old points
    for(auto dot : dots){
        scene->removeItem(dot);
    }
    dots.clear();
}
