/**
 * @file line.cpp
 * @brief Tento soubor obsahuje implementaci metod třídy Line
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#include "line.h"

uint32_t Line::lineCount = 0;

Line::Line()
: n(++lineCount){}

/**
 * @return číslo linky
 */
uint32_t Line::getNumber()
{
    return n;
}

/**
 * @return vektor názvů stanic linky
 */
std::vector<std::string> Line::getSNames()
{
    return slist;
}

/**
 * @param is in stream
 * @param l instance třídy pro zápis
 * @return in stream
 */
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
