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
 * @brief 
 * 
 * 
 */
class Map
{
private:
	float w;	///< šířka mapy
	float h;	///< výška mapy
	std::vector<Street> streets;	///< vektor ulic nacházejících se v mapě
	std::vector<Station> stations;	///< vektor stanic nacházejících se v mapě
	std::vector<Line> lines;	///< vektor linek zobrazovaných v mapě
	Graph g;	///< graf pro interní reprezentaci uli, stanic a linek
public:
	/// Vytvoření prázdné mapy
	Map();
	/// Vytvoření mapy s šířkou a délkou
	Map(float, float);

	/// Přidání ulice do mapy
	void addStreet(Street);
	/// Přidání ulic do mapy
	void addStreets(std::vector<Street>);

	void closeStreet(Point, Point, std::vector<uint32_t> &);
	void openStreets();

	/// Přidání stanice do mapy
	void addStation(Station);
	/// Přidání stanic do mapy
	void addStations(std::vector<Station>);

	/// Přidání linky do mapy
	void addLine(Line);
	/// Přidání linek do mapy
	void addLines(std::vector<Line>);

	/// Metoda pro vytvoření grafu z ulic a stanic
	void createGraph();
	/// Metoda pro začlenění linek do grafu
	void setLinesInGraph();
	void setDetour(uint32_t, std::vector<Point>);
	std::vector<std::pair<std::string, float>> getLineSchedule(uint32_t);

	void outputGraph();

	/// Zrušení grafu
	~Map();
};
#endif	//	__MAP_H__