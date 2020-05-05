#include "point.h"

Point::Point(){};

Point::Point(float x, float y):x(x), y(y)
{
    if (x < 0.f ||
        y < 0.f)
        exit(1);
};

float Point::getX()
{
    return this->x;
}

float Point::getY()
{
    return this->y;
}

std::vector<float> operator^(const Point &A, const Point &B)
{
    Point v = A - B;

//  to norm vec    
    float c = v.x;
    v.x = v.y;
    v.y = - c;

//  get c from point A and norm vec
    c = - (v.x * A.x + v.y * A.y);

//  transform ax + by + c = 0 to y = ax + b
    std::vector<float> ret(- (v.x / c), - (v.y / c));

    return ret;
}

Point operator+(const Point &A,const Point &B){
    float x = A.x + B.x;
    float y = A.y + B.y;
    Point R(x,y);
    return R;
};

Point operator-(const Point &A,const Point &B){
    float x = A.x - B.x;
    float y = A.y - B.y;
    Point R(x,y);
    return R;
};

static float Point::dist(Point A, Point B) 
{
    return sqrt(pow(A.getX() - B.getX(),2) + pow(A.getY() - B.getY(),2));
}