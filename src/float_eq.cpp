/**
 * @file float_eq.cpp
 * @brief Tento soubor obsahuje implementaci funkce pro rovnost dvou čísel v plovoucí řádové čárce
 * @author David Bayer (xbayer09)
 * @author Michal Szymik (xszymi00)
 * @date 10.5.2020
 */
#include "float_eq.h"

/***************************************************************************************
*    Title: Comparison
*    Author: Michael Borgwardt
*    Date: 15. 5. 2020
*    Code version:
*    Availability: https://floating-point-gui.de/errors/comparison/
*    Published under the Creative Commons Attribution License (BY):
*    http://creativecommons.org/licenses/by/3.0/
*
***************************************************************************************/
static const float epsilon = .00001f;

/**
 * @param a první číslo v plovoucí řádové čárce
 * @param b druhé číslo v plovoucí řádové čárce
 * @return true pokud se rovnají
 */
bool floatEQ(float a, float b)
{
    float abs_a = fabsf(a);
    float abs_b = fabsf(b);
    float diff = fabs(a - b);

    if (a == b)
        return true;
    
    else if (a == 0.f ||
             b == 0.f ||
             (abs_a + abs_b < std::numeric_limits<float>::min()))
        return diff < (epsilon * std::numeric_limits<float>::min());
    else
        return diff / std::fmin(abs_a + abs_b, std::numeric_limits<float>::max()) < epsilon;
}

/***************************************************************************************/
