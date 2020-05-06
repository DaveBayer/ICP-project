#ifndef __LINE_H__
#define __LINE_H__

#include <cstdint>
#include <string>
#include <vector>
#include "point.h"
class Line
{
private:
	static uint32_t LineCount;
    uint32_t id;
    std::string name;
	std::vector<Point> route;
public:
    Line(std::string name);
    uint32_t getId();
    std::vector<Point> getRoute();
    std::string getName();
    void setRoute(std::vector<Point>&);
    ~Line();
};

#endif	// ___LINE_H__