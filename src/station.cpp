/**
 * @file station.cpp
 * @brief Tento soubor obsahuje implementace metod třídy Station
 * @author David Bayer (xbayer09)
 * @author Michal Szymik
 * @date $Date: 10.5.2020
 */
#include "station.h"

Station::Station(){}

/**
 * @param P bod, na kterém stanice leží
 * @param sid id ulice, na které stanice leží
 * @param name název stanice
 */
Station::Station(Point P, uint32_t sid, std::string name)
: P(P), street_id(sid), name(name){}

/**
 * @return id ulice, na které stanice leží
 */
uint32_t Station::getStreetID()
{
    return street_id;
}

/**
 * @param sid id ulice
 */
void Station::setStreetID(uint32_t sid)
{
    street_id = sid;
}

/**
 * @return bod, na kterém ulice leží
 */
Point Station::getPoint()
{
    return P;
}

/**
 * @return jméno ulice
 */
std::string Station::getName()
{
    return name;
}

/**
 * @param is in stream
 * @param s instance třídy Station pro zápis
 * @return in stream
 */
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
