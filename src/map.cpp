/**
 * @file map.cpp
 * @brief Tento soubor obsahuje implementace metod třídy Map
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#include "map.h"

Map::Map(){}

/**
 * @param new_w nová šířka mapy
 * @param new_h nová výška mapy
 * @param new_streets vektor ulic
 * @param new_stations vektor stanic
 */
Map::Map(float new_w, float new_h, std::vector<Street> new_streets, std::vector<Station> new_stations)
: w(new_w), h(new_h)
{
    addStreets(new_streets);
    addStations(new_stations);
    g = Graph(streets, stations);
}

/**
 * @param s ulice pro přidání do mapy
 */
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

/**
 * @param v vektor ulic pro přidání do mapy
 */
void Map::addStreets(std::vector<Street> v)
{
    for (auto &i : v)
        addStreet(i);
}

/**
 * @param A první bod ulice
 * @param B poslední bod ulice
 * @param ret vektor zasažených linek
 */
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

/**
 * @param s stanice pro přidání do mapy
 */
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

/**
 * @param v vektor stanic pro přidání do mapy
 */
void Map::addStations(std::vector<Station> v)
{
    for (auto &i : v)
        addStation(i);
}

/**
 * @param l linka pro přidání do mapy
 */
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

/**
 * @param lines vektor linek pro přidání do mapy
 */
void Map::addLines(std::vector<Line> lines)
{
    for (auto &i : lines)
        addLine(i);
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

/**
 * @param P bod
 * @return true pokud bod P je stanicí v mapě
 */
bool Map::isStation(Point P)
{
    auto it = std::find_if(stations.begin(), stations.end(),
        [&P](auto &el) -> bool
        { return P == el.getPoint(); });
    return it != stations.end();
}

/**
 * @param lid číslo linky
 * @param path vektor objízdné trasy linky
 */
void Map::setDetour(uint32_t lid, std::vector<Point> path)
{
    if (!isStation(path.front()) || !isStation(path.back()))
        errExit(1, "Detour must start and end with a station");

    std::vector<std::vector<Point>> paths;
    std::vector<Point> subpath{path.front()};

    for (uint32_t i = 1; i < path.size(); i++) {
        Point P = path[i];
        subpath.push_back(P);

        if (isStation(P)) {
            paths.push_back(subpath);
            subpath = std::vector<Point>{P};
        }
    }

    g.updateLinePath(lid, paths);
}

/**
 * @param lid číslo linky
 * @param rev směr linky
 * @return vektor jmen stanic a vzdáleností mezi nimi
 */
std::vector<std::pair<std::string, float>> Map::getLineSchedule(uint32_t lid, bool rev)
{
    std::vector<std::pair<Point, float>> d = g.countLineSchedule(lid);
    std::vector<std::pair<std::string, float>> ret;

    if (rev) {
        std::reverse(d.begin(), d.end());

        for (uint32_t i = d.size(); i > 0; i--)
            d[i].second = d[i - 1].second;
        
        d.front().second = 0.f;
    }

    for (auto &i : d) {
        auto it = std::find_if(stations.begin(), stations.end(),
            [&i](auto &el) -> bool
            { return i.first == el.getPoint(); });
        if (it != stations.end())
            ret.push_back(std::make_pair(it->getName(), i.second));
        else
            ret.push_back(std::make_pair("", i.second));
    }

    return ret;
}

Map::~Map(){}
