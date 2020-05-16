/**
 * @file point.cpp
 * @brief Tento soubor obsahuje implementace metod třídy Point
 * @author David Bayer (xbayer09)
 * @author Michal Szymik
 * @date 10.5.2020
 */
#include "point.h"

Point::Point(){};

/**
 * @param new_x horizontální poloha bodu
 * @param new_y vertikální poloha bodu
 */
Point::Point(float new_x, float new_y)
: x(new_x), y(new_y){}

/**
 * @return horizontální polohu bodu
 */
float Point::getX()
{
    return x;
}

/**
 * @return vertikální polohu bodu
 */
float Point::getY()
{
    return y;
}

/**
 * @param A první bod
 * @param B druhý bod
 * @return true pokud bod leží v prostoru mezi bodem A a B
 */
bool Point::between(const Point &A, const Point &B)
{
    return !(x < std::min(A.x, B.x) || 
        x > std::max(A.x, B.x) ||
        y < std::min(A.y, B.y) ||
        y > std::max(A.y, B.y));
}

/**
 * @param A první bod
 * @param B druhý bod
 * @return true pokud jsou body shodné
 */
bool operator==(const Point &A, const Point &B)
{
    return floatEQ(A.x, B.x) && floatEQ(A.y, B.y);
}

/**
 * @param A bod
 * @return euklidovská vzdálenost od bodu A
 */
float Point::dist(const Point A) const
{
    return sqrt(pow(x - A.x,2) + pow(y - A.y,2));
}

/**
 * @param is in stream
 * @param P bod pro zápis
 * @return in stream
 */
std::istream &operator>>(std::istream &is, Point &P)
{
    is >> P.x >> P.y;
    return is;
}

Point::~Point(){}
