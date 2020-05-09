#include "map.h"

Map::Map(){}

Map::Map(float new_w, float new_h)
: w(new_w), h(new_h){}

Map::Map(float w, float h, std::vector<Street> s)
: w(w), h(h), streets(s){}

void Map::addStreet(Street s)
{
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

void Map::addStation(Station s)
{
    auto it = std::find_if(streets.begin(), streets.end(),
        [&s](Street &el) -> bool
        { return s.getStreetID() == el.getID(); });

    if (it != streets.end()) {
        auto pts = it->getPoints();
        Point P = s.getPoint();

        float res1 = (P.getX() - pts[0].getX()) * (pts[1].getY() - pts[0].getY());
        float res2 = (P.getY() - pts[0].getY()) * (pts[1].getX() - pts[0].getY());

        if (!(res1 == res2 &&
            P.between(pts[0], pts[1]))) {

            std::cerr << "Station does not lay on the street\n";
            exit(1);

            //TODO Vylepsit exception
        }
        stations.push_back(s);
    }
        
    //  TODO exception
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

        if (it == stations.end()) {
            std::cerr << "Station \'" << i << "\' not found\n";
            exit(1);
        }
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
            
            if (it == stations.end()) {
                std::cerr << "station not found\n";
                exit(1);
            }

            pts.push_back(it->getPoint);
        }

        g.SetUpLine(i.getNumber(), pts);
    }
}

void Map::outputGraph()
{
    std::cout << g;
}

Map::~Map(){}
