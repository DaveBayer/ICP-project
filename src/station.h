#ifndef __STATION_H__
#define __STATION_H__

#include <string>
#include <sstream>
#include <iostream>

#include "street.h"
#include "point.h"

class Station
{
private:
	Point P;
	uint32_t street_id;
	std::string name;
public:
	Station(Point, uint32_t, std::string);
	Point getPoint();
	uint32_t getStreetID();

	friend std::istream &operator>>(std::istream &, Station &);
	~Station();
};

#endif	//	__STATION_H__