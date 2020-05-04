#ifndef __STREET_H__
#define __STREET_H__
#include <string>
#include <cmath>

#include "point.h"
#include "map.h"

class Street
{
private:
	uint32_t id;
	Point A, B;
	std::vector<float> v;		/*	y = v[0]x + v[1]*/
	std::string name;
public:
	Street(Point A, Point B, std::string name);
	~Street();
};

#endif	//	__STREET_H__
