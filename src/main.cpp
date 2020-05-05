#include "graph.h"
#include "line.h"
#include "map.h"
#include "point.h"
#include "station.h"
#include "street.h"

void getPoints(std::vector<Point> &pts)
{
    pts.push_back(Point(0.f, 0.f));
    pts.push_back(Point(2.f, 2.f));
    pts.push_back(Point(2.f, 0.f));
    pts.push_back(Point(0.f, 2.f));
}

int main(int argc, char const *argv[])
{
    std::vector<Point> pts;
    getPoints(pts);

    Street s1(pts[0], pts[1], "prvni");
    Street s2(pts[2], pts[3], "druha");

    Map m(20.f, 20.f);
    
    m.addStreet(s1);
    m.addStreet(s2);

    return 0;
}
