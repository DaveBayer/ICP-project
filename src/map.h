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
	

	/// Přidání ulice do mapy
	void addStreet(Street);
	/// Přidání ulic do mapy
	void addStreets(std::vector<Street>);
	/// Přidání stanice do mapy
	void addStation(Station);
	/// Přidání stanic do mapy
	void addStations(std::vector<Station>);
public:
	/// Vytvoření prázdné mapy
	Map();
	/// Vytvoření mapy s šířkou, délkou, ulicemi a stanicemi
	Map(float, float, std::vector<Street>, std::vector<Station>);

	void closeStreet(Point, Point, std::vector<uint32_t> &);
	void openStreets();


	/// Přidání linky do mapy
	void addLine(Line);
	/// Přidání linek do mapy
	void addLines(std::vector<Line>);

	/// Metoda pro začlenění linek do grafu
	void setLinesInGraph();
	void setDetour(uint32_t, std::vector<Point>);
	std::vector<std::pair<std::string, float>> getLineSchedule(uint32_t, bool);
	bool isStation(Point);

	Graph g;	///< graf pro interní reprezentaci uli, stanic a linek
	std::vector<Street> streets;	///< vektor ulic nacházejících se v mapě
	std::vector<Station> stations;	///< vektor stanic nacházejících se v mapě
	std::vector<Line> lines;	///< vektor linek zobrazovaných v mapě

	/// Zrušení grafu
	~Map();
};

#endif	//	__MAP_H__
