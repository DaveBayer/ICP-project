#include "map.h"

Map::Map(float new_w, float new_h)
: w(new_w), h(new_h){}

Map::Map(float w, float h, std::vector<Street> s)
: w(w), h(h), streets(s){}

void Map::addStreet(Street &s)
{
    streets.push_back(s);
}




std::vector<Street> Map::getStreets() 
{
	return streets;
}



Map::~Map(){}
