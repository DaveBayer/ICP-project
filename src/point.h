#ifndef __POINT_H__
#define __POINT_H__

#include <stdlib.h>
#include <cmath>

#include <vector>

class Point
{
private:
    float x, y;
public:
    Point();
    Point(float x, float y);

    float getX();
    float getY();

    std::vector<float> makeLine(Point, Point);

    friend std::vector<float> operator^(const Point &A, const Point &B);
    friend Point operator+(const Point &A, const Point &B);
    friend Point operator-(const Point &A, const Point &B);
    

    static float dist(Point A, Point B);
    ~Point();
};

#endif  //  __POINT_H__
