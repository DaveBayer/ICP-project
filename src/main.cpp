#include "graph.h"
#include "line.h"
#include "map.h"
#include "point.h"
#include "station.h"
#include "street.h"
#include <QApplication>
#include "mainwindow.h"

void getPoints(std::vector<Point> &pts)
{
    pts.push_back(Point(0.f, 0.f));
    pts.push_back(Point(2.f, 2.f));
    pts.push_back(Point(2.f, 0.f));
    pts.push_back(Point(0.f, 2.f));
}

int main(int argc, char  *argv[])
{
    // std::vector<Point> pts;
    // getPoints(pts);
    // std::cout << "Points created.." << std::endl;

    // Street s1(pts[0], pts[1], "prvni");
    // std::cout << "Street 1 created.." << std::endl;

    // Street s2(pts[2], pts[3], "druha");
    // std::cout << "Streets 2 created.." << std::endl;
    
    Map m(600, 600);
    
    // std::cout << "Map created.." << std::endl;
    // m.addStreet(s1);
    // m.addStreet(s2);

    // std::cout << "Streets added to map" << std::endl;

    Point p1(100,100);
    Point p2(100,500);
    Point p3(200,100);
    Point p4(200,500);
    Point p5(300,100);
    Point p6(300,500);
    Point p7(400,100);
    Point p8(400,500);
    Point p9(500,100);
    Point p10(500,500);
    Point ph1(100,100);
    Point ph2(500,100);
    Point ph3(100,200);
    Point ph4(500,200);
    Point ph5(100,300);
    Point ph6(500,300);
    Point ph7(100,400);
    Point ph8(500,400);
    Point ph9(100,500);
    Point ph10(500,500);

    Street s1(p1,p2, "");
    Street s2(p3,p4, "");
    Street s3(p5,p6, "");
    Street s4(p7,p8, "");
    Street s5(p9,p10, "");
    Street s6(ph1,ph2, "");
    Street s7(ph3,ph4, "");
    Street s8(ph5,ph6, "");
    Street s9(ph7,ph8, "");
    Street s10(ph9,ph10, "");

    m.addStreet(s1);
    m.addStreet(s2);
    m.addStreet(s3);
    m.addStreet(s4);
    m.addStreet(s5);
    m.addStreet(s6);
    m.addStreet(s7);
    m.addStreet(s8);
    m.addStreet(s9);
    m.addStreet(s10);

    std::vector<Line> lines;

    Point pr1(100,100);
    Point pr2(100,200);
    Point pr3(300,200);
    Point pr4(300,400);
    Point pr5(500,400);
    Point pr6(500,500);

    std::vector<Point> route = {pr1,pr2,pr3,pr4,pr5,pr6};

    Line l1("line 1");
    Line l2("line 2");
    Line l3("line 1");
    Line l4("line 2");
    Line l5("line 1");
    Line l6("line 2");

    l1.setRoute(route);


    lines.push_back(l1);
    lines.push_back(l2);
    lines.push_back(l3);
    lines.push_back(l4);
    lines.push_back(l5);
    lines.push_back(l6);
    // GUI Window

    QApplication app(argc, argv);
    MainWindow mainWindow;
    // mainWindow.setGeometry(100, 100, 800, 500);
    mainWindow.createStreetMap(m.getStreets());
    mainWindow.createLines(lines);
    mainWindow.finish();
    mainWindow.show();

    return app.exec();
}
