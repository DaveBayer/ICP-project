#ifndef __LINE_H__
#define __LINE_H__

#include <iostream>

#include "station.h"

class Line
{
private:
    static uint32_t lineCount;
    uint32_t n;
    std::vector<std::string> slist;
    std::vector<uint32_t> forward, backward;
public:
    Line();
    uint32_t getNumber();
    std::vector<std::string> getSNames();
    friend std::istream &operator>>(std::istream &, Line &);
    ~Line();
};

#endif	//  __LINE_H__
