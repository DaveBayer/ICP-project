#include "station.h"

Station::Station(Point P, uint32_t sid, std::string name)
: P(P), street_id(sid), name(name){}

uint32_t Station::getStreetID()
{
    return street_id;
}

Point Station::getPoint()
{
    return P;
}

std::string Station::getName()
{
    return name;
}

std::istream &operator>>(std::istream &is, Station &s)
{
    is >> s.P >> s.street_id >> s.name;
    return is;
}

Station::~Station(){}
