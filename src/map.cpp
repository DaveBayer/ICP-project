#include "map.h"

Map::Map(){}

Map::Map(float new_w, float new_h)
: w(new_w), h(new_h){}

void Map::addStreet(Street s)
{
    std::vector<Point> pts (s.getPoints());
    if (!pts[0].between(Point(0.f, 0.f), Point(w, h)) ||
        !pts[1].between(Point(0.f, 0.f), Point(w, h)))
        errExit(1, "Street out of map size");

    auto it = std::find_if(streets.begin(), streets.end(),
        [&s](Street &el) -> bool
        { return s.getID() == el.getID(); });
    
    if (it == streets.end())
        streets.push_back(s);
}

void Map::addStreets(std::vector<Street> v)
{
    for (auto &i : v)
        addStreet(i);
}

void Map::closeStreet(Point A, Point B, std::map<uint32_t, std::vector<uint32_t>> &ret)
{
    uint32_t sid = g.getStreetFromPoints(A, B);
    g.closeStreetEdges(sid);

    ret = g.findLineConflicts(sid);
}
/*
void Map::openStreet()
{
    g.openStreetEdges(sid);

}
*/
void Map::addStation(Station s)
{
    for (auto i : streets) {
        auto pts = i.getPoints();
        Point P = s.getPoint();

        float ab = sqrtf((pts[1].getX() - pts[0].getX()) * (pts[1].getY() - pts[0].getY()));
        float ap = sqrtf((P.getX() - pts[0].getX()) * (P.getY() - pts[0].getY()));
        float pb = sqrtf((pts[1].getX() - P.getX()) * (pts[1].getY() - P.getY()));

        if (floatEQ(ab, ap + pb)) {
            s.setStreetID(i.getID());

            auto it = std::find_if(stations.begin(), stations.end(),
                [&s](auto &el) -> bool
                { return s.getName() == el.getName(); });
            
            if (it == stations.end()) {
                stations.push_back(s);
                return;
            
            } else
                errExit(1, "Readding station");
        }
    }

    errExit(1, "Station must lay on a street");
}

void Map::addStations(std::vector<Station> v)
{
    for (auto &i : v)
        addStation(i);
}

void Map::addLine(Line l)
{
    for (auto &i : l.getSNames()) {
        auto it = std::find_if(stations.begin(), stations.end(),
            [&i](auto &el) -> bool
            { return i == el.getName(); });

        if (it == stations.end())
            errExit(1, "No such station");
    }

    lines.push_back(l);
}

void Map::addLines(std::vector<Line> lines)
{
    for (auto &i : lines)
        addLine(i);
}

void Map::createGraph()
{
    g = Graph(streets, stations);
}

void Map::setLinesInGraph()
{
    for (auto &i : lines) {
        std::vector<Point> pts;

        for (auto &j : i.getSNames()) {
            auto it = std::find_if(stations.begin(), stations.end(),
                [&j](auto &el) -> bool
                { return j == el.getName(); });
            
            if (it == stations.end())
                errExit(1, "No such station");

            pts.push_back(it->getPoint());
        }

        g.SetUpLine(i.getNumber(), pts);
    }
}

Map::~Map(){}
