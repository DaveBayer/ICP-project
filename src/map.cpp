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

void Map::closeStreet(Point A, Point B, std::vector<uint32_t> &ret)
{
    uint32_t sid = g.getStreetFromPoints(A, B);
    g.closeStreetEdges(sid);

    ret = g.findLineConflicts(sid);
}

void Map::openStreets()
{
    g.resetEdgesW();
    setLinesInGraph();
}

void Map::addStation(Station s)
{
    for (auto i : streets) {
        auto pts = i.getPoints();
        Point P = s.getPoint();

        float ab = pts[1].dist(pts[0]);
        float ap = P.dist(pts[0]);
        float pb = pts[1].dist(P);

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

void Map::setDetour(uint32_t lid, std::vector<Point> path)
{
    auto isStation = [=](Point P) -> bool
    {
        auto it = std::find_if(stations.begin(), stations.end(),
            [&P](auto &el) -> bool
            { return P == el.getPoint(); });
        return it != stations.end();
    };

    if (!isStation(path.front()) || !isStation(path.back()))
        errExit(1, "Detour must start and end with a station");

    std::vector<std::vector<Point>> paths;
    std::vector<Point> subpath{path.front()};

    for (uint32_t i = 0; i < path.size(); i++) {
        Point P = stations[i].getPoint();
        subpath.push_back(P);

        if (isStation(P)) {
            paths.push_back(subpath);
            subpath = std::vector<Point>{P};
        }
    }

    g.updateLinePath(lid, paths);
}

Map::~Map(){}
