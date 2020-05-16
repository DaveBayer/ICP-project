/**
 * @file street.cpp
 * @brief Tento soubor obsahuje implementace metod třídy Street
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#include "street.h"

uint32_t Street::StreetCount = 0;

Street::Street()
: id(StreetCount++){}

/**
 * @param new_A první krajní bod ulice
 * @param new_B druhý krajní bod ulice
 * @param new_name jméno ulice
 */
Street::Street(Point new_A, Point new_B, std::string new_name)
: id(StreetCount++), A(new_A), B(new_B), name(new_name){}

/**
 * @return id ulice
 */
uint32_t Street::getID()
{
    return id;
}

/**
 * @return jméno ulice
 */
std::string Street::getName()
{
    return name;
}

/**
 * @return vektor s krajními body ulice
 */
std::vector<Point> Street::getPoints()
{
    std::vector<Point> ret;
    ret.push_back(A);
    ret.push_back(B);
    return ret;
}

/**
 * @param s ulice pro spočítání průsečíku
 * @param P průsečík ulic
 * @return true pokud mají ulice průsečík
 */
bool Street::intersect(Street s, Point &P)
{
    auto det = [](std::vector<float> &a, std::vector<float> &b) -> float
    { return a[0] * b[1] - a[1] * b[0]; };

    std::vector<float> a(2), b(2), c(2), d(2), xdiff(2), ydiff(2), d2(2);

    auto pts1 = this->getPoints();
    auto pts2 = s.getPoints();

    a[0] = pts1[0].getX();
    a[1] = pts1[0].getY();
    b[0] = pts1[1].getX();
    b[1] = pts1[1].getY();
    c[0] = pts2[0].getX();
    c[1] = pts2[0].getY();
    d[0] = pts2[1].getX();
    d[1] = pts2[1].getY();

    xdiff[0] = pts1[0].getX() - pts1[1].getX();
    xdiff[1] = pts2[0].getX() - pts2[1].getX();

    ydiff[0] = pts1[0].getY() - pts1[1].getY();
    ydiff[1] = pts2[0].getY() - pts2[1].getY();

    float div = det(xdiff, ydiff);

    if (floatEQ(div, 0.f))
        return false;

    d2[0] = det(a, b);
    d2[1] = det(c, d);

    float x = det(d2, xdiff) / div;
    float y = det(d2, ydiff) / div;
    P = Point(x,y);

    return P.between(s.A, s.B) && P.between(A, B);
}

/**
 * @param is in stream
 * @param s instance třídy Street pro zápis
 * @return in stream
 */
std::istream &operator>>(std::istream &is, Street &s)
{
    std::string line;
    if (std::getline(is, line)) {
        std::istringstream iss(line);
        if (!(iss >> s.A >> s.B >> s.name))
            errExit(1, "Invalid istream format");
    }
    
    return is;
}

Street::~Street(){}
