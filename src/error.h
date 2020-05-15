/**
 * @file error.h
 * @brief Tento soubor obsahuje deklarace chybových funkcí
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#ifndef __ERROR_H__
#define __ERROR_H__

#include <iostream>

/// Funkce pro tisk chybové hlášky a ukončení programu
void errExit(int, std::string);

#endif  //  __ERROR_H__
