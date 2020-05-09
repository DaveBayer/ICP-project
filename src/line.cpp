#include "line.h"

uint32_t Line::lineCount = 0;

Line::Line()
: n(++lineCount){}

uint32_t Line::getNumber()
{
    return n;
}

std::vector<std::string> Line::getSNames()
{
    return slist;
}

std::istream &operator>>(std::istream &is, Line &l)
{
    l.slist.clear();

    std::string line;
    while (std::getline(is, line)) {
        std::istringstream iss(line);
        std::string station;

        if (!(is >> station)) {
            std::cerr << "invalid format\n";
            exit(1);
        
        } else
            l.slist.push_back(station);
    }

    return is;
}

Line::~Line(){}
