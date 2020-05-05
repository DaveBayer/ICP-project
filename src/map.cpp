#include "map.h"

Map::Map(float w, float h)
: w(w), h(h){};

Map::Map(float w, float h, std::vector<Street> s)
: w(w), h(h), streets(s){};

void Map::addStreet(Street &s)
{
    streets.push_back(s);
}

