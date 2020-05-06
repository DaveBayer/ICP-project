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
    std::cout << "Points created.." << std::endl;

    Street s1(pts[0], pts[1], "prvni");
    std::cout << "Street 1 created.." << std::endl;

    Street s2(pts[2], pts[3], "druha");
    std::cout << "Streets 2 created.." << std::endl;
    
    Map m(20.f, 20.f);
    
    std::cout << "Map created.." << std::endl;
    m.addStreet(s1);
    m.addStreet(s2);

    std::cout << "Streets added to map" << std::endl;

    return 0;
}
