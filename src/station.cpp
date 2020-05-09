#include "station.h"

Station::Station(){}

Station::Station(Point P, uint32_t sid, std::string name)
: P(P), street_id(sid), name(name){}

uint32_t Station::getStreetID()
{
    return street_id;
}

void Station::setStreetID(uint32_t sid)
{
    street_id = sid;
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
    std::string line;
    if (std::getline(is, line)) {
        std::istringstream iss(line);
        if (!(iss >> s.P >> s.name))
            errExit(1, "Invalid istream format");
    }
    
    return is;
}

Station::~Station(){}
