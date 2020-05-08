#ifndef __MAP_H__
#define __MAP_H__

#include <fstream>
#include <sstream>
#include <vector>

#include "graph.h"
#include "station.h"
#include "street.h"

class Map
{
private:
	float w, h;
	std::vector<Street> streets;
	std::vector<Station> stations;
	Graph g;
public:
	Map();
	Map(float w, float h);
	Map(float w, float h, std::vector<Street> s);

	void addStreet(Street);
	void addStreets(std::vector<Street>);
	void closeStreet(Street);
	void closeStreet(Point, Point);

	void addStation(Station);
	void addStations(std::vector<Station>);

	void createGraph();
	void outputGraph();

	int readMap(const char *);

	~Map();
};

#endif	//	__MAP_H__
