#ifndef __STATION_H__
#define __STATION_H__
#include <string>

#include "street.h"

class Station
{
private:
	Point P;
	Street s;
public:
	Station(/* args */);
	~Station();
};

#endif	//	__STATION_H__