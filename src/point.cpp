#include "point.h"

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

bool Point::between(const Point &A, const Point &B)
{
    return !(x < std::min(A.x, B.x) && 
        x > std::max(A.x, B.x) &&
        y < std::min(A.y, B.y) &&
        y > std::max(A.y, B.y));
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
    return floatEQ(A.x, B.x) && floatEQ(A.y, B.y);
}

float Point::dist(const Point A) const
{
    return sqrt(pow(x - A.x,2) + pow(y - A.y,2));
}

std::ostream &operator<<(std::ostream &os, Point P)
{
    os << P.x << " " << P.y;
    return os;
}

std::istream &operator>>(std::istream &is, Point &P)
{
    is >> P.x >> P.y;
    return is;
}

Point::~Point(){}