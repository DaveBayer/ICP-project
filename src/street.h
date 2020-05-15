/**
 * @file street.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy Street
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#ifndef __STREET_H__
#define __STREET_H__

#include <iostream>
#include <string>
#include <cmath>

#include "error.h"
#include "float_eq.h"
#include "point.h"

/**
 * @class Street
 * @brief Třída reprezentující ulici
 */
class Street
{
private:
	static uint32_t StreetCount;	///< Celkový počet ulic
	uint32_t id;	///< id ulice
	Point A;	///< počáteční bod ulice
	Point B;	///< koncový bod ulice
	std::string name;	///< jméno ulice
public:
	/// Vytvoření prázdné ulice
	Street();
	/// Vytvoření inicializované ulice
	Street(Point A, Point B, std::string name);
	
	/// Metoda pro získání id ulice
	uint32_t getID();
	/// Metoda pro získání jména ulice
	std::string getName();
	/// Metoda pro získání bodů vymezující ulici
	std::vector<Point> getPoints();

	/// Metoda pro zjištění průsečíku dvou ulic
	bool intersect(Street, Point &);

	friend std::istream &operator>>(std::istream &, Street &);
	
	/// Zrušení ulice
	~Street();
};

#endif	//	__STREET_H__
