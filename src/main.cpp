#include <fstream>

#include "error.h"
#include "graph.h"
#include "line.h"
#include "map.h"
#include "point.h"
#include "station.h"
#include "street.h"
#include <QApplication>
#include "mainwindow.h"

std::ifstream fileOpen(const char *name)
{
    std::ifstream f;
    f.open(name, std::ios::in);
    if (!(f.is_open()))
        errExit(1, "File cannot be opened");
    return f;
}

std::vector<Street> getStreets(const char *name)
{
    std::vector<Street> streets;
    std::ifstream f = fileOpen(name);
    while (!f.eof()) {
        Street s;
        f >> s;
        streets.push_back(s);
    }
        
    f.close();
    return streets;
}

std::vector<Station> getStations(const char *name)
{
    std::vector<Station> stations;
    std::ifstream f = fileOpen(name);
    Station s;
    while (f >> s){
        stations.push_back(s);
    }
    f.close();

    return stations;
}

std::vector<Line> getLines(const char *name)
{
    std::vector<Line> lines;
    std::ifstream f = fileOpen(name);
    while (!f.eof()) {
        Line l;
        f >> l;
        lines.push_back(l);
    }
    f.close();
    return lines;
}

int main(int argc, char  *argv[])
{
    
    std::vector<Street> streets = getStreets(argv[1]);
    std::vector<Station> stations = getStations(argv[2]);
    std::vector<Line> lines = getLines(argv[3]);

    Map m(600.f, 600.f, streets, stations);


    m.addLines(lines);
    m.setLinesInGraph();



    QApplication app(argc, argv);
    MainWindow mainWindow(&m);
    mainWindow.createButtons();
    mainWindow.createScene();
    mainWindow.setGeometry(200, 200, 1000, 950);
    mainWindow.createSystemClock();
    mainWindow.createStreetMap();
    mainWindow.createLines();
    mainWindow.createView();
    mainWindow.createMainLayout();
    mainWindow.connectButtons();

    mainWindow.finish();
    mainWindow.show();

    return app.exec();
}
