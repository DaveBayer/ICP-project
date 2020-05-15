/**
 * @file point.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy Point
 * @author David Bayer (xbayer09)
 * @author Michal Szymik
 * @date $Date: 10.5.2020
 */
#ifndef __POINT_H__
#define __POINT_H__

#include <stdlib.h>

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>

#include "float_eq.h"

/**
 * @class Point
 * @brief Tato třída reprezentuje bod v dvou dimenzionálním prostoru
 */

class Point
{
private:
    float x;    ///< horizontální souřadnice bodu
    float y;    ///< vertikální souřadnice bodu
public:
    /// Vytvoření prázdného bodu
    Point();
    /// Vytvoření bodu se zadanou pozicí
    Point(float x, float y);

    /// Metoda pro získání horizontální souřadnice bodu
    float getX();
    /// Metoda pro získání vertikální souřadnice bodu
    float getY();

    /// Metoda pro zjištění, zda bod leží v prostoru mezi zadanými body
    bool between(const Point &, const Point &);
    
    /// Metoda pro získání vzdálenosti bodu od zadaného bodu
    float dist(const Point A) const;
    
    /// Operátor pro rovnost dvou bodů
    friend bool operator==(const Point &A, const Point &B);
    /// Operátor pro načtení vstupu
    friend std::istream &operator>>(std::istream &, Point &);
    
    /// Zrušení bodu
    ~Point();
};

#endif  //  __POINT_H__