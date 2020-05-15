/**
 * @file station.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy Station
 * @author David Bayer (xbayer09)
 * @author Michal Szymik
 * @date $Date: 10.5.2020
 */
#ifndef __STATION_H__
#define __STATION_H__

#include <string>
#include <sstream>
#include <iostream>

#include "street.h"
#include "point.h"

/**
 * @class Station
 * @brief Tato třídá uchovává data stanice
 */
class Station
{
private:
	Point P;	///< pozice stanice
	uint32_t street_id;		///< id ulice, na které stanice leží
	std::string name;	///< jméno stanice
public:
	/// Vytvoření prázdné stanice
	Station();
	/// Vytvoření inicializované stanice
	Station(Point, uint32_t, std::string);

	/// Metoda pro získání pozice stanice
	Point getPoint();
	/// Metoda pro získání id ulice, na které stanice leží
	uint32_t getStreetID();
	/// Metoda pro nastavení id ulice, na které stanice leží
	void setStreetID(uint32_t);
	/// Metoda pro získání jména stanice
	std::string getName();

	friend std::istream &operator>>(std::istream &, Station &);
	/// Zrušení stanice
	~Station();
};

#endif	//	__STATION_H__