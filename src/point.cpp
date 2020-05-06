#include "point.h"

const float epsilon = 0.01;

Point::Point(){};

Point::Point(float new_x, float new_y)
: x(new_x), y(new_y){}

float Point::getX()
{
    return x;
}

float Point::getY()
{
    return y;
}

std::vector<float> operator^(const Point &A, const Point &B)
{
    std::cout << "newvec";
    std::vector<float> v(A.x - B.x, A.y - B.y);
    std::cout << "tady";
//  to norm vec    
    float c = v[0];
    v[0] = v[1];
    v[1] = - c;
    std::cout << "tu";
//  get c from point A and norm vec
    c = - (v[0] * A.x + v[1] * A.y);
    std::cout << "t";
//  transform ax + by + c = 0 to y = ax + b
    std::vector<float> ret(- (v[0] / c), - (v[1] / c));
    std::cout << "r";
    return ret;
}

Point operator+(const Point &A,const Point &B)
{
    float x = A.x + B.x;
    float y = A.y + B.y;
    Point R(x,y);
    return R;
};

Point operator-(const Point &A,const Point &B)
{
    float x = A.x - B.x;
    float y = A.y - B.y;
    Point R(x,y);
    return R;
};

bool operator==(const Point &A, const Point &B)
{
    return std::fabs(A.x - B.x) < epsilon * std::max(std::abs(A.x), std::abs(B.x)) && 
           std::fabs(A.y - B.y) < epsilon * std::max(std::abs(A.y), std::abs(B.y));
}

float Point::dist(const Point A) const
{
    return sqrt(pow(x - A.x,2) + pow(y - A.y,2));
}

Point::~Point(){}