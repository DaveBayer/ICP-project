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

    std::vector<Street> sv;
    Street s1(pts[0], pts[1], "prvni");
    std::cout << "Street 1 created.." << std::endl;

    Street s2(pts[2], pts[3], "druha");
    std::cout << "Streets 2 created.." << std::endl;

    sv.push_back(s1);
    sv.push_back(s2);
    
    Map m(20.f, 20.f, sv);
    
    std::cout << "Map created.." << std::endl;
    m.createGraph();
    std::cout << "Streets added to map" << std::endl;

    std::cout << "Graph:\n";

    m.outputGraph();

    Map m2;
    switch(m2.readMap(argv[1])) {
    case 0 :
        std::cerr << "No input\n";
        return 0;
    case -1 :
        std::cerr << "No such file\n";
        return -1;
    case -2 :
        std::cerr << "No header\n";
        return -2;
    case -3 :
        std::cerr << "Invalid street format\n";
        return -3;
    default :
        break;
    }
    
    m2.createGraph();
    m2.outputGraph();

    return 0;
}
