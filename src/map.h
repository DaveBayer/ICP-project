#ifndef __MAP_H__
#define __MAP_H__

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
	Map(float w, float h);
	Map(float w, float h, std::vector<Street> s);

	void addStreet(Street &);
	void closeStreet(Street);
	void closeStreet(Point, Point);

	void createGraph();
	
	void outputGraph();

	~Map();
};

#endif	//	__MAP_H__
