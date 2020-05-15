/**
 * @file line.h
 * @brief Tento soubor obsahuje deklarace atributů a metod třídy Line
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#ifndef __LINE_H__
#define __LINE_H__

#include <iostream>
#include <vector>
#include <string>

#include "station.h"

struct timetable_s {
    uint32_t start;
};

/**
 * @class Line
 * @brief Třída reprezentující linku
 */
class Line
{
private:
    static uint32_t lineCount;  ///< Celkový počet linek
    uint32_t n;     ///< id linky
    std::vector<std::string> slist; ///< Vektor zastávek
public:    
    std::vector<uint32_t> forward;      ///< vektor s časy odjezdů z výchozí stanice 
    std::vector<uint32_t> backward;     ///< vektor s časy odjezdů z koncové stanice

    /// Vytvoření prázndé linky
    Line();
    /// Metoda pro získání čísla linky
    uint32_t getNumber();
    /// Metoda pro získání vektoru se jmény stanic
    std::vector<std::string> getSNames();

    friend std::istream &operator>>(std::istream &, Line &);
    
    /// Zrušení linky
    ~Line();
};

#endif  //  __LINE_H__
