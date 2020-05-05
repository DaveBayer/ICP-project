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

static bool Street::intersect(Street s1, Street s2, Point &p)
{
    auto pts1 = s1.getPoints();
    auto pts2 = s2.getPoints();
 
 	auto a1 = pts1[1][1] - pts1[0][1];
 	auto b1 = pts1[0][0] - pts1[1][0];
 	auto c1 = a1*(pts1[0][0]) + b1*pts1[0][1];

 	auto a2 = pts2[1][1] - pts2[0][1];
 	auto b2 = pts2[0][0] - pts2[1][0];
 	auto c2 = a2*(pts2[0][0]) + b2*pts2[0][1];


 	auto determinant = a1*b2 - a2*b1;

 	if (determinant == 0) {
 		return false;
 	}else{
 		auto x = (b2*c1 - b1*c2)/determinant; 
        auto y = (a1*c2 - a2*c1)/determinant; 

        if (x >= min(pts1[0].getX(),pts1[1].getX()) && 
        	x <= max(pts1[0].getX(),pts1[1].getX()) &&
        	y >= min(pts1[0].getY(),pts1[1].getY()) && y <= max(pts1[0].getY(),pts1[1].getY())) {
        	p = Point(x,y);
        	return true;
        } else {
        	return false;
        }
 	}
}