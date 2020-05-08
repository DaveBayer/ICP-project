#include "float_eq.h"

static const float epsilon = .00001f;

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