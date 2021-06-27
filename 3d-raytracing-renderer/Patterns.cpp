#include "Patterns.h"
#include "Shape.h"
#include "SimplexNoise.h"
#include "Tuple.h"

#include <math.h>

Color StripePattern::pattern_at(Tuple p)
{
    if (static_cast<int>(std::floor(p.x)) % 2 == 0)
        return a;
    return b;
}

Color GradientPattern::pattern_at(Tuple p)
{
    auto red = a.red + (p.x * (b.red - a.red));
    auto green = a.green + (p.x * (b.green - a.green));
    auto blue = a.blue + (p.x * (b.blue - a.blue));

    return Color{red, green, blue};
}

Color RingPattern::pattern_at(Tuple p)
{
    const double powX = p.x * p.x;
    const double powZ = p.z * p.z;
    const double squareroot = sqrtf(powX + powZ);

    if (static_cast<int>(std::floor(squareroot)) % 2 == 0)
        return a;
    return b;
}

Color CheckersPattern::pattern_at(Tuple p)
{
    if (static_cast<int>(std::floor(p.x) + std::floor(p.y) + std::floor(p.z)) % 2 == 0)
        return a;
    return b;
}

Color PerlinNoisePattern::pattern_at(Tuple pnt)
{
    SimplexNoise noise{};
    const float distortion = noise.Noise(pnt.x, pnt.y, pnt.z);
    auto disturbedPoint = point(pnt.x + distortion, pnt.y + distortion, pnt.z + distortion);
    return p->pattern_at(p->getInversedTransform() * disturbedPoint);
}

Color BlendPattern::pattern_at(Tuple p)
{
    auto clrA = a->pattern_at(a->getInversedTransform() * p);
    auto clrB = b->pattern_at(b->getInversedTransform() * p);
    return (clrA + clrB) * 0.5f;
}
