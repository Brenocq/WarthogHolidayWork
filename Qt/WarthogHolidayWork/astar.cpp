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
    int resolution = 30;
    int radius = 25;
    for (Position* obstacle : obstacles) {
        for (double i=0;i<M_PI*2;i+=M_PI*2/resolution) {
            // Add point to Quad Tree
            QPoint point(obstacle->getX()+qCos(i)*radius, obstacle->getY()+qSin(i)*radius);
            if(start->getTeam() != obstacle->getTeam()){
                point.setX(-point.x());
                point.setY(-point.y());
            }
            if(start->getTeam()==red){
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
    clean();

    discretizeWorld();// Create quad-tree

    openList.clear();
    closedList.clear();

    // Start QTree
    QuadTree *startQTree;
    QPoint *point;
    point = new QPoint(int(start->getX()),int(start->getY()));
    if(start->getTeam()==red){
        point->setX(-point->x());
        point->setY(-point->y());
    }
    startQTree = qTree->getQtreeAtPoint(point);
    // End QTree
    QuadTree *endQTree;
    point->setX(int(end->getX()));
    point->setY(int(end->getY()));
    if(start->getTeam()==red){
        point->setX(-point->x());
        point->setY(-point->y());
    }
    endQTree = qTree->getQtreeAtPoint(point);

    QVector<QuadTree *> endNeighbors;
    QRect *rect = new QRect(endQTree->getCenter()->x(),endQTree->getCenter()->y(),endQTree->getWidth()+20,endQTree->getHeight()+20);
    endNeighbors = qTree->neighbors(rect);
    endNeighbors+=endQTree;


    Node *startNode = new Node;
    startNode->qTree = startQTree;
    startNode->g=0;
    startNode->h=start->distanceTo(*end);
    startNode->f = startNode->g + startNode->h;
    startNode->prevConnected=false;

    closedList.push_back(startNode);
    Node *prevNode = startNode;
    Node *currNode = startNode;

    int maxItineration=200;
    //----- A* algorithm -----//
    while(--maxItineration){
        // End condition
        for(auto endNeighbor : endNeighbors){
            if(currNode->qTree == endNeighbor){
                goto done;
            }
        }

        //Vector of neighbors
        QVector<QuadTree *> neighbors;
        QRect *rect = new QRect(currNode->qTree->getCenter()->x(),currNode->qTree->getCenter()->y(),currNode->qTree->getWidth()+20,currNode->qTree->getHeight()+20);
        neighbors = qTree->neighbors(rect);

        // Add new nodes to the open list
        for(auto neighbor : neighbors){
            bool newNode=true;
            for(auto closeNode : closedList){
                if(closeNode->qTree==neighbor){
                    newNode=false;
                }
            }
            for(auto openNode : openList){
                if(openNode->qTree==neighbor){
                    newNode=false;
                }
            }
            if(newNode){
                Node *nextNode = new Node;
                nextNode->qTree=neighbor;
                if(nextNode->qTree->getHeight()>=25){// TODO change hard code (50=robot diameter)
                    // Calcutation h
                    float deltaX;
                    float deltaY;
                    if(start->getTeam()==blue){
                        deltaX = neighbor->getCenter()->x()-end->getX();
                        deltaY = neighbor->getCenter()->y()-end->getY();
                    }else{
                        deltaX = neighbor->getCenter()->x()+end->getX();
                        deltaY = neighbor->getCenter()->y()+end->getY();
                    }
                    nextNode->h = float(sqrt(double(deltaX*deltaX + deltaY*deltaY)));
                    // Calcutation g
                    float gCurr, gPrev;
                    deltaX = neighbor->getCenter()->x()-currNode->qTree->getCenter()->x();
                    deltaY = neighbor->getCenter()->y()-currNode->qTree->getCenter()->y();
                    gCurr = float(sqrt(double(deltaX*deltaX + deltaY*deltaY)))+currNode->g;

                    deltaX = neighbor->getCenter()->x()-prevNode->qTree->getCenter()->x();
                    deltaY = neighbor->getCenter()->y()-prevNode->qTree->getCenter()->y();
                    gPrev = float(sqrt(double(deltaX*deltaX + deltaY*deltaY)))+prevNode->g;

                    if(/*gCurr<gPrev*/true){//It was walking over the obstacles
                        nextNode->g = gCurr;
                        nextNode->f = nextNode->h + nextNode->g;
                        nextNode->prevNode = currNode;
                    }else{
                        nextNode->g = gPrev;
                        nextNode->f = nextNode->h + nextNode->g;
                        nextNode->prevNode = prevNode;
                    }
                   openList.push_back(nextNode);
                }

            }
        }

        // Choose best node
        Node *nextNode;
        if(openList.size()>=1){
            nextNode = openList[0];
        }
        float bestF=1000;
        int indexBestNode=0;
        for(int i=0;i<openList.size();i++){
            if(openList[i]->f<bestF){
                nextNode = openList[i];
                bestF = openList[i]->f;
                indexBestNode = i;
            }
        }
        if(openList.size()>=1){
            openList.remove(indexBestNode);
        }
        closedList.push_back(nextNode);

        prevNode = currNode;
        currNode = nextNode;

    }
    done:

    //----- Generate path -----//
    path+=new Position(end->getX(),end->getY(),0);
    path+=new Position(end->getX(),end->getY(),0);

    Node *pathNode = currNode;// Ignore last node
    while(pathNode!=0x0 && pathNode->prevConnected){// Ignore first node
        Position *nextPos;
        if(start->getTeam()==blue){
            nextPos = new Position(pathNode->qTree->getCenter()->x(),
                                   pathNode->qTree->getCenter()->y(),0);
        }else{
            nextPos = new Position(-pathNode->qTree->getCenter()->x(),
                                   -pathNode->qTree->getCenter()->y(),0);
        }

        path+=nextPos;
        pathNode = pathNode->prevNode;
    }

    path+=new Position(start->getX(),start->getY(),0);
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
    drawOpenClose(openList, closedList);
}

void AStar::drawOpenClose(QVector<Node*> openList, QVector<Node*> closedList)
{
    QBrush redBrush(QColor(255,0,0,100));
    QBrush blueBrush(QColor(0,0,255,100));
    QPen outlinePen(QColor(0,0,0,0));
    for(auto rectangle : rectangles){
        scene->removeItem(rectangle);
    }
    rectangles.clear();

    for(auto open : openList){
        float w = open->qTree->getWidth();
        float h = open->qTree->getHeight();
        QRect *rect = new QRect(open->qTree->getCenter()->x()-w/2,open->qTree->getCenter()->y()-h/2,w,h);
        rectangles.push_back(scene->addRect(*rect, outlinePen, blueBrush));
    }
    for(auto close : closedList){
        float w = close->qTree->getWidth();
        float h = close->qTree->getHeight();
        QRect *rect = new QRect(close->qTree->getCenter()->x()-w/2,close->qTree->getCenter()->y()-h/2,w,h);
        rectangles.push_back(scene->addRect(*rect, outlinePen, redBrush));
    }
}

void AStar::clean()
{
    qTree->clean();
    // Delete old points
    for(auto dot : dots){
        scene->removeItem(dot);
    }
    dots.clear();
    // Delete old rectangles
    for(auto rectangle : rectangles){
        scene->removeItem(rectangle);
    }
    rectangles.clear();
}
