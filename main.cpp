#include <iostream>
#define MDEBUG
#include "geometry.h"



int main()
{
    Point* start = new Point();
    Point* end = new Point(10,10);
    GeometryObject* v = new Vector(start, end);
    start->shift(100,100);
    v->print();
    VectorObject* poly = new Polyline({{0,0},{1,1},{2,0}});
    delete v;
    poly->equidistant(0);
    poly->equidistant(1,false);
    delete poly;
    return 0;
}
