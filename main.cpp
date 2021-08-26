#include <iostream>
#include "geometry.h"



int main()
{
    Point* start = new Point();
    Point* end = new Point(10,10);
    GeometryObject* v = new Vector(start, end);
    start->shift(100,100);
    v->print();
    delete v;
    return 0;
}
