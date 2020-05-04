#include "map.h"

Map::Map(float x, float y)
: x(x), y(y){};

Map::Map(float x, float y, std::vector<Street> s)
: x(x), y(y), streets(s){};

void Map::addStreet(Street &s)
{
    streets.push_back(s);
}

