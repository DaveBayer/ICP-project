#include "line.h"

uint32_t Line::LineCount = 0;

Line::Line(std::string name) : name(name)
{
	id = LineCount++;
}

uint32_t Line::getId()
{
	return id;
}

std::string Line::getName()
{
	return name;
}

std::vector<Point>  Line::getRoute()
{
	return route;
}

void Line::setRoute(std::vector<Point> &route) 
{
	this->route = route;
}

Line::~Line(){}