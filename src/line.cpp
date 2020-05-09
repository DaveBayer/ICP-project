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
    if (std::getline(is, line)) {
        std::istringstream iss(line);

        while (std::getline(iss, line, ' '))
            l.slist.push_back(line);

        if (std::getline(is, line)) {
            std::istringstream iss(line);

            while (std::getline(iss, line, ' ')) {
                uint32_t n = std::stoul(line);
                l.forward.push_back(n);
            }

            if (std::getline(is, line)) {
                std::istringstream iss(line);

                while (std::getline(iss, line, ' ')) {
                    uint32_t n = std::stoul(line);
                    l.backward.push_back(n);
                }
            } else
                errExit(1, "Missing backward");
        } else
            errExit(1, "Missing forward");
    }

    return is;
}

Line::~Line(){}