/**
 * @file graph.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy Graph
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <algorithm>
#include <limits>
#include <map>
#include <vector>
#include <list>
#include <iostream>

#include "error.h"
#include "point.h"
#include "street.h"
#include "station.h"
#include "line.h"

/**
 * @class Graph
 * @brief Tato třída umožňuje vytvořit data k vykreslení konkrétní mapy
 */
class Graph
{
private:
    uint32_t pt_idx;    ///< počet uzlů
    float TrafficCoef;  ///< hodnota koeficientu provozu, výchozí hodnota je 0.5
    std::vector<std::vector<std::pair<float, float>>> adj_mat;  ///< matice hran obsaující jejich váhy a koeficienty provozu
    
    /// Tato metoda inicializuje prázdný graf
    void init();
    /// Tato metoda spočítá nejkratší cestu mezi 2 body v grafu na základě metody UCS
    bool getPath(Point, Point, std::vector<Point> &);
public:
    std::map<uint32_t, std::vector<std::vector<Point>>> line_pts;   ///< mapa linek obsahující vektory tras mezi zastávkami
    std::map<uint32_t, std::vector<std::pair<Point, uint32_t>>> cs; ///< mapa ulic obsahující všechny body, které se na nich nacházejí
    std::vector<std::pair<Point, uint32_t>> nodes;  ///< vektor pro překlad bodu na index do matice hran
    
    /// Vytvoření prázdného grafu
    Graph();
    /// Vytvoření grafu z vektoru ulic
    Graph(std::vector<Street> &);
    /// Vytvoření grafu z vektoru ulic a vektoru zastávek
    Graph(std::vector<Street> &, std::vector<Station> &);

    /// Tato metoda převádí krajní body ulice na její id
    uint32_t getStreetFromPoints(Point, Point);
    /// Tato metoda přeloží bod na index vrcholu
    uint32_t getNodeID(Point);
    /// Tato metoda zpětně přeloží index vrcholu na bod
    Point getNodePoint(uint32_t);
    /// Tato metoda přidá do mapy ulic a překladového vektoru nový vrchol
    void addNode(uint32_t, Point);
    /// Tato metoda přidá do mapy ulic a překladového vektoru nové vrcholy
    void addNodes(uint32_t, std::vector<Point>);

    /// Tato metoda vytvoří hrany v matici hran
    void createEdges();
    /// Tato metoda uzavře všechny grany ulice v matici hran
    void closeStreetEdges(uint32_t);

    /// Tato metoda vrací délku hrany mezi dvěma body
    float getEdgeW(Point, Point);
    /// Tato metoda změní délku hrany mezi dvěma vrcholy na zadanou délku
    void setEdgeW(uint32_t, uint32_t, float);
    /// Tato metoda obnoví původní délku hrany mezi dvěma vrcholy
    void resetEdgeW(uint32_t, uint32_t);
    /// Tatot metoda obnoví původí délku všech hran v matici hran
    void resetEdgesW();

    /// Tato metoda vrátí hodnotu koeficientu provozu
    float getTC();
    /// Tato metoda nastaví hodnotu koeficientu provozu
    void setTC(float);
    /// Tato metoda vrací hodnotu koeficientu provozu hrany mezi dvěma vrcholy
    float getEdgeTC(uint32_t, uint32_t);
    /// Tato metoda vrací hodnotu koeficientu provozu hrany mezi dvěma body
    float getEdgeTC(Point, Point);
    /// Tato metoda zvýší hodnotu koeficientu provozu hrany mezi dvěma vrcholy
    void incEdgeTC(uint32_t, uint32_t);
    /// Tato metoda vyresetuje hodnotu koeficientu provozu hrany mezi dvěma vrcholy
    void resetEdgeTC(uint32_t, uint32_t);

    /// Tato metoda zvýší hodnotu koeficientu provozu celé ulice
    void incStreetTC(Point, Point);
    /// Tato metoda vyresetuje hodnotu koeficientu provozu celé ulice
    void resetStreetTC(Point, Point);
    /// Tato metoda vrátí hodnotu koeficientu provozu celé ulice
    float getStreetTC(Point, Point);

    /// Tato metoda vytvoří vektory vrcholů mezi zastávkami u všech linek
    void SetUpLine(uint32_t, std::vector<Point>);
    /// Tato metoda vrátí vektor linek zasažených uzavírkou ulice
    std::vector<uint32_t> findLineConflicts(uint32_t);
    /// Tato metoda aktualizuje trasu linky
    void updateLinePath(uint32_t, std::vector<std::vector<Point>>);
    /// Tato metoda spočítá vzdálenosti mezi zastávkami
    std::vector<std::pair<Point, float>> countLineSchedule(uint32_t);

    /// Tato metoda vrací true, pokud se jedná o hranu mezi dvěma vrcholy
    bool isEdge(Point,Point);

    /// Zrušení grafu
    ~Graph();
};

#endif  //  __GRAHP_H__
