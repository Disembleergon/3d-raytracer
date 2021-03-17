#pragma once
#include "Color.h"
#include "Tuple.h"

#include <math.h>

class Material;

struct PointLight
{
    Tuple position{0, 0, 0, 0};
    // describes intensity/color of the light source
    Color intensity{0, 0, 0};
};

Color lighting(const Material &mat, const PointLight &light, const Tuple &poi, const Tuple &eyev, const Tuple &normalv,
               const bool in_shadow);
