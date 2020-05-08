#ifndef __POINT_H__
#define __POINT_H__

#include <stdlib.h>

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>

#include "float_eq.h"

class Point
{
private:
    float x, y;
public:
    Point();
    Point(float x, float y);

    float getX();
    float getY();

    bool between(const Point &, const Point &);

    std::vector<float> makeLine(Point, Point);

    friend std::vector<float> operator^(const Point &A, const Point &B);
    friend Point operator+(const Point &A, const Point &B);
    friend Point operator-(const Point &A, const Point &B);
    friend bool operator==(const Point &A, const Point &B);

    float dist(const Point A) const;
    
    friend std::ostream &operator<<(std::ostream &, Point);
    friend std::istream &operator>>(std::istream &, Point &);
    ~Point();
};

#endif  //  __POINT_H__
