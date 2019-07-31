#include "potentialfield.h"
#include <vector>

PotentialField::PotentialField():
    NavigationAlgorithm()
{
}

PotentialField::PotentialField(Position* _start, Position* _end):
    NavigationAlgorithm(_start,_end)
{
}

PotentialField::~PotentialField()
{

}

void PotentialField::generatePath()
{
    NavigationAlgorithm::generatePath();// Clean old path
    qreal concavity = 1.2;
    float repulsiveForce = 1500;
    float attractiveForce = 15;
    QVector<Position*> resultPath;
    // Add curr position to the start
    resultPath.push_back(start);
    //----- Generate path -----//
    float distToGoal=resultPath.back()->distanceTo(*end);
    while(resultPath.size()<300 && distToGoal>10){
        distToGoal = resultPath.back()->distanceTo(*end);

        QVector<QVector2D> vectors;
        // Obstacle vectors
        for (int i=0;i<obstacles.size();i++) {
            QVector2D obsVector;

            if(start->getTeam()==obstacles[i]->getTeam()){
                obsVector = resultPath.back()->toVector()-obstacles[i]->toVector();
            }else{
                obsVector = resultPath.back()->toVector()+obstacles[i]->toVector();
            }

            obsVector.normalize();
            obsVector = obsVector*repulsiveForce;
            qreal distance;
            if(start->getTeam()==obstacles[i]->getTeam())
                distance = qreal(resultPath.back()->distanceTo(*obstacles[i]));
            else {
                qreal deltaX = qreal(resultPath.back()->getX()+obstacles[i]->getX());
                qreal deltaY = qreal(resultPath.back()->getY()+obstacles[i]->getY());
                distance = qSqrt(deltaX*deltaX + deltaY*deltaY);
            }
            obsVector = obsVector/float(qPow(distance,concavity));
            vectors.push_back(obsVector);
        }
        // Goal vector
        QVector2D goalVector;
        goalVector = end->toVector()-resultPath.back()->toVector();
        goalVector.normalize();
        goalVector = goalVector*attractiveForce;
        vectors.push_back(goalVector);
        // Result vector
        QVector2D resultVector(0,0);
        for (int i=0;i<vectors.size();i++) {
            resultVector = resultVector + vectors[i];
        }
        // Calculate new position
        Position *nextPos = new Position(0,0,0);
        nextPos->setNewPosition(resultPath.back()->getX()+resultVector.x(),
                                resultPath.back()->getY()+resultVector.y(),
                                0);
        resultPath.push_back(nextPos);
    }
    std::reverse(resultPath.begin(), resultPath.end());
    path = resultPath;
}

void PotentialField::draw()
{

}

void PotentialField::clean()
{

}
