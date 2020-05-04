#include "street.h"

Street::Street(Point A, Point B, std::string name)
: A(A), B(B), name(name)
{
    v = A ^ B;
};

