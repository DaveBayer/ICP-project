/**
 * @file point.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy Point
 * @author David Bayer (xbayer09)
 * @author Michal Szymik
 * @date $Date: 10.5.2020
 */
#pragma once

#include <stdlib.h>

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>

#include "float_eq.h"

/**
 * @class Point
 * @brief 
 * 
 * 
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
    Point(float, float);

    /// Metoda pro získání horizontální souřadnice bodu
    float getX();
    /// Metoda pro získání vertikální souřadnice bodu
    float getY();

    /// Metoda pro zjištění, zda bod leží v prostoru mezi zadanými body
    bool between(const Point &, const Point &);
    /// Metoda pro získání vzdálenosti bodu od zadaného bodu
    float dist(const Point) const;

    friend bool operator==(const Point &A, const Point &B);
    friend std::ostream &operator<<(std::ostream &, Point);
    friend std::istream &operator>>(std::istream &, Point &);
    ~Point();
};
