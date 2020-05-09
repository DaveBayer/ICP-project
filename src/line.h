#ifndef __LINE_H__
#define __LINE_H__

#include <iostream>

#include "station.h"

struct timetable_s {
    uint32_t start;
};

class Line
{
private:
    static uint32_t lineCount;
    uint32_t n;
    std::vector<std::string> slist;
public:    
    std::vector<uint32_t> forward, backward;

    Line();
    uint32_t getNumber();
    std::vector<std::string> getSNames();
    friend std::istream &operator>>(std::istream &, Line &);
    ~Line();
};

#endif  //  __LINE_H__