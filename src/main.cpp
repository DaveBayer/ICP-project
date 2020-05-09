#include "graph.h"
#include "line.h"
#include "map.h"
#include "point.h"
#include "station.h"
#include "street.h"
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char  *argv[])
{

    std::vector<Line> lines;

    Point pr1(100,100);
    Point pr2(100,200);
    Point pr3(300,200);
    Point pr4(300,400);
    Point pr5(500,400);
    Point pr6(500,500);

    std::vector<Point> route1 = {pr1,pr2,pr3,pr4,pr5,pr6};

    

    

    Point s1(0,0);
    Point s2(150,0);
    Point s3(320,0);
    Point s4(600,350);

    Point cs1(600,0);

    std::vector<std::vector<Point>> route_line;
    std::vector<Point> part1 = {s1};
    std::vector<Point> part2 = {s1,s2};
    std::vector<Point> part3 = {s2,s3};
    std::vector<Point> part4 = {s3,cs1,s4};
    std::vector<Point> part5 = {s4};

    route_line.push_back(part1);
    route_line.push_back(part2);
    route_line.push_back(part3);
    route_line.push_back(part4);
    route_line.push_back(part5);


   Line l1("line 1");
    l1.length = 950;
    struct timetable_s connection1 = {.start = (0 + 0 + 2), .route = route_line};
    struct timetable_s connection2 = {.start = (1*60*60 + 0*60 + 2), .route = route_line};
    struct timetable_s connection3 = {.start = (1*60*60 + 10*60 + 50), .route = route_line};
    l1.timetable.push_back(connection1);
    l1.timetable.push_back(connection2);
    l1.timetable.push_back(connection3);
    Line l2("line 2");
    Line l3("line 1");
    Line l4("line 2");
    Line l5("line 1");
    Line l6("line 2");
//     
//     
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
    std::cout<<m2.g<<std::endl;
    std::vector<Point> route2;
    Point node1(0,0);
    Point node2(600, 420);
    // m2.g.getPath(node1, node2, route2);
    l1.setRoute(route1);
    // l2.setRoute(route2);
    lines.push_back(l1);
    lines.push_back(l2);
    // lines.push_back(l3);
    // lines.push_back(l4);
    // lines.push_back(l5);
    // lines.push_back(l6);
    // GUI Window

    QApplication app(argc, argv);
    MainWindow mainWindow;
    // mainWindow.setGeometry(100, 100, 800, 500);
    mainWindow.createSystemClock();
    // mainWindow.createStreetMap(m2.getStreets());
    mainWindow.createStreetMap(m2.getGraphMap());
    mainWindow.createLines(lines);
    mainWindow.finish();
    mainWindow.show();

    return app.exec();
}
