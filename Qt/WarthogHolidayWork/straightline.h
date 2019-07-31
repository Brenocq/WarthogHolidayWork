#ifndef STRAIGHTLINE_H
#define STRAIGHTLINE_H
#include "navigationalgorithm.h"

class StraightLine : public NavigationAlgorithm
{
public:
    StraightLine();
    StraightLine(Position* _start, Position* _end);
    ~StraightLine();
    void generatePath();
    void draw();
    void clean();
};

#endif // STRAIGHTLINE_H
