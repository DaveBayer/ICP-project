#include <fstream>

#include "error.h"
#include "graph.h"
#include "line.h"
#include "map.h"
#include "point.h"
#include "station.h"
#include "street.h"

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
    while (f >> s)
        stations.push_back(s);
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

int main(int argc, char const *argv[])
{
    std::vector<Street> streets = getStreets(argv[1]);
    std::vector<Station> stations = getStations(argv[2]);
    std::vector<Line> lines = getLines(argv[3]);

    Map m(600.f, 600.f);

    m.addStreets(streets);
    m.addStations(stations);
    m.createGraph();

    m.addLines(lines);
    m.setLinesInGraph();

    return 0;
}
