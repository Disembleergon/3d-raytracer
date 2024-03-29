#include "Patterns.h"
#include "Shape.h"
#include "SimplexNoise.h"
#include "Tuple.h"

#include <cmath>

Color TestPattern::pattern_at(Tuple p)
{
    return Color{p.x, p.y, p.z};
}

Color StripePattern::pattern_at(Tuple p)
{
    if (static_cast<int>(std::floor(p.x)) % 2 == 0)
        return a->pattern_at(a->getInversedTransform() * p);
    return b->pattern_at(b->getInversedTransform() * p);
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
    const double squareroot = sqrt(powX + powZ);

    if (static_cast<int>(std::floor(squareroot)) % 2 == 0)
        return a->pattern_at(a->getInversedTransform() * p);
    return b->pattern_at(b->getInversedTransform() * p);
}

Color CheckersPattern::pattern_at(Tuple p)
{
    if (static_cast<int>(std::floor(p.x) + std::floor(p.y) + std::floor(p.z)) % 2 == 0)
        return a->pattern_at(a->getInversedTransform() * p);
    return b->pattern_at(b->getInversedTransform() * p);
}

Color PerlinNoisePattern::pattern_at(Tuple pnt)
{
    SimplexNoise noise{};
    const auto distortion = noise.Noise(pnt.x, pnt.y, pnt.z) * scaleValue;
    auto disturbedPoint = point(pnt.x + distortion, pnt.y + distortion, pnt.z + distortion);
    return p->pattern_at(p->getInversedTransform() * disturbedPoint);
}

Color BlendPattern::pattern_at(Tuple p)
{
    auto clrA = a->pattern_at(a->getInversedTransform() * p);
    auto clrB = b->pattern_at(b->getInversedTransform() * p);
    return (clrA + clrB) * 0.5f;
}

Color JitteredPattern::pattern_at(Tuple pnt)
{
    SimplexNoise noise{};
    auto newX = pnt.x + noise.Noise(pnt.x, pnt.y, pnt.z) * scaleValue;
    auto newY = pnt.y + noise.Noise(pnt.x, pnt.y, pnt.z + 1) * scaleValue;
    auto newZ = pnt.z + noise.Noise(pnt.x, pnt.y, pnt.z + 2) * scaleValue;
    auto newPoint = point(newX, newY, newZ);

    return p->pattern_at(p->getInversedTransform() * newPoint);
}

Color SolidPattern::pattern_at(Tuple p)
{
    return clr;
}
