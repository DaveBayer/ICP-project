#include "street.h"

uint32_t Street::StreetCount = 0;

Street::Street(Point new_A, Point new_B, std::string new_name)
: A(new_A), B(new_B), name(new_name)
{
    id = StreetCount++;
//    v = A ^ B;
};

uint32_t Street::getID()
{
    return id;
}

std::string Street::getName()
{
    return name;
}

std::vector<Point> Street::getPoints()
{
    std::vector<Point> ret;
    ret.push_back(A);
    ret.push_back(B);
    return ret;
}

bool Street::intersect(Street s, Point &p)
{
    auto pts = s.getPoints();
 
 	auto a1 = B.getY() - A.getY();
 	auto b1 = A.getX() - B.getX();
 	auto c1 = a1 * A.getX() + b1 * A.getY();

 	auto a2 = pts[1].getY() - pts[0].getY();
 	auto b2 = pts[0].getX() - pts[1].getX();
 	auto c2 = a2 * pts[0].getX() + b2 * pts[0].getY();


 	auto determinant = a1 * b2 - a2 * b1;

 	if (determinant == 0) {
 		return false;
 	} else {
 		auto x = (b2*c1 - b1*c2)/determinant; 
        auto y = (a1*c2 - a2*c1)/determinant; 

        if (x >= std::min(A.getX(), B.getX()) && 
        	x <= std::max(A.getX(), B.getX()) &&
        	y >= std::min(A.getY(), B.getY()) &&
            y <= std::max(A.getY(), B.getY())) {
        	p = Point(x,y);
        	return true;

        } else {
        	return false;
        }
 	}
}

Street::~Street(){}