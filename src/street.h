#ifndef __STREET_H__
#define __STREET_H__
#include <string>
#include <cmath>

#include "point.h"

class Street
{
private:
	static uint32_t StreetCount;
	uint32_t id;
	Point A, B;
	std::vector<float> v;		/*	y = v[0]x + v[1]*/
	std::string name;
public:
	Street(Point A, Point B, std::string name);
	
	uint32_t getID();
	std::vector<Point> getPoints();
	bool intersect(Street, Point &);

	~Street();
};

#endif	//	__STREET_H__
