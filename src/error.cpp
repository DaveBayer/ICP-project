/**
 * @file error.cpp
 * @brief Tento soubor obsahuje implementace chybových funkcí
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#include "error.h"

/**
 * @param errNum chybová návratová hodnota programu
 * @param errMsg řetězec s chybou pro výpis na standardní chybový výstup
 */
void errExit(int errNum, std::string errMsg)
{
    std::cerr << errMsg << std::endl;
    exit(errNum);
}
