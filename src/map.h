/**
 * @file map.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy Map
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#ifndef __MAP_H__
#define __MAP_H__

#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include "error.h"
#include "graph.h"
#include "station.h"
#include "street.h"
#include "line.h"

/**
 * @class Map
 * @brief Tato třída nese data mapy a její graf
 */
class Map
{
private:
	float w;	///< šířka mapy
	float h;	///< výška mapy
	
	/// Přidání ulice do mapy
	void addStreet(Street);
	/// Přidání ulic do mapy
	void addStreets(std::vector<Street>);
	/// Přidání stanice do mapy
	void addStation(Station);
	/// Přidání stanic do mapy
	void addStations(std::vector<Station>);
public:
	Graph g;	///< graf pro interní reprezentaci uli, stanic a linek
	std::vector<Street> streets;	///< vektor ulic nacházejících se v mapě
	std::vector<Station> stations;	///< vektor stanic nacházejících se v mapě
	std::vector<Line> lines;	///< vektor linek zobrazovaných v mapě

	/// Vytvoření prázdné mapy
	Map();
	/// Vytvoření mapy s šířkou, délkou, ulicemi a stanicemi
	Map(float, float, std::vector<Street>, std::vector<Station>);

	/// Metoda pro uzavření ulice zadané dvěma body
	void closeStreet(Point, Point, std::vector<uint32_t> &);
	/// Metoda pro otevření všech ulic
	void openStreets();

	/// Přidání linky do mapy
	void addLine(Line);
	/// Přidání linek do mapy
	void addLines(std::vector<Line>);

	/// Metoda pro začlenění linek do grafu
	void setLinesInGraph();
	/// Metoda pro určení objížďky linky
	void setDetour(uint32_t, std::vector<Point>);
	/// Metoda pro získání jízdního řádu linky
	std::vector<std::pair<std::string, float>> getLineSchedule(uint32_t, bool);
	/// Metoda pro zjištění, zda zadaný bod je stanicí
	bool isStation(Point);

	/// Zrušení grafu
	~Map();
};

#endif	//	__MAP_H__
