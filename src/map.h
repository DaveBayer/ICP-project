#ifndef __MAP_H__
#define __MAP_H__

#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include "error.h"
#include "graph.h"
#include "station.h"
#include "street.h"
#include "line.h"

class Map
{
private:
	float w, h;
	std::vector<Street> streets;
	std::vector<Station> stations;
	std::vector<Line> lines;
	Graph g;
public:
	Map();
	Map(float w, float h);

	void addStreet(Street);
	void addStreets(std::vector<Street>);
	void closeStreet(Street);
	void closeStreet(Point, Point);

	void addStation(Station);
	void addStations(std::vector<Station>);

	void addLine(Line);
	void addLines(std::vector<Line>);

	void createGraph();
	void setLinesInGraph();
	void outputGraph();

	~Map();
};

#endif	//	__MAP_H__
