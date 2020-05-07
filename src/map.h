#ifndef __MAP_H__
#define __MAP_H__

#include <fstream>
#include <sstream>
#include <vector>

#include "graph.h"
#include "street.h"

class Map
{
private:
	float w, h;
	std::vector<Street> streets;
	Graph g;
public:
	Map();
	Map(float w, float h);
	Map(float w, float h, std::vector<Street> s);

	void addStreet(Street &);
	void closeStreet(Street);
	void closeStreet(Point, Point);

	void createGraph();
	void outputGraph();

	int readMap(const char *);

	~Map();
};

#endif	//	__MAP_H__
