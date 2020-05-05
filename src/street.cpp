#include "street.h"

Street::Street(Point A, Point B, std::string name)
: A(A), B(B), name(name)
{
    v = A ^ B;
};

uint32_t Street::getID()
{
    return id;
}

std::vector<Point> Street::getPoints()
{
    std::vector<Point> ret;
    ret.push_back(A);
    ret.push_back(B);
    return ret;
}

static bool Street::intersect(Street s1, Street s2)
{
    
}