/**
 * @file street.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy Street
 * @author David Bayer (xbayer09)
 * @author Michal Szymik
 * @date $Date: 10.5.2020
 */
#pragma once

#include <iostream>
#include <string>
#include <cmath>

#include "error.h"
#include "float_eq.h"
#include "point.h"

/**
 * @class Point
 * @brief 
 * 
 * 
 */
class Street
{
private:
	static uint32_t StreetCount;	///< Celkový počet ulic
	uint32_t id;	///< id ulice
	Point A, B;		///< počáteční a koncový bod ulice
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
	/// Metoda pro získání krajních bodů ulice
	std::vector<Point> getPoints();

	/// Metoda pro zjištění průsečíku dvou ulic
	bool intersect(Street, Point &);

	friend std::istream &operator>>(std::istream &, Street &);
	
	/// Zrušení ulice
	~Street();
};
