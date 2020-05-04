#ifndef __MAP_H__
#define __MAP_H__
#include <vector>

#include "street.h"

class Map
{
private:
	float x, y;
	std::vector<Street> streets;
	
public:
	Map(float x, float y);
	Map(float x, float y, std::vector<Street> s);
	void addStreet(Street &s);
	~Map();
};

#endif	//	__MAP_H__
