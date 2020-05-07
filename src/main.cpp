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
//    m2.outputGraph();

    return 0;
}
