#ifndef STRAIGHTLINE_H
#define STRAIGHTLINE_H
#include "navigationalgorithm.h"

class StraightLine : public NavigationAlgorithm
{
public:
    StraightLine(Position* _start, Position* _end);

     void generatePath();
};

#endif // STRAIGHTLINE_H
