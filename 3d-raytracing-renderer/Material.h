#pragma once
#include "Color.h"
#include "Pattern.h"

using member_t = double;

struct Material
{
    member_t ambient{0.1};
    member_t diffuse{0.9};
    member_t specular{0.9};
    member_t shininess{200};
    Color color{1, 1, 1};
    member_t reflective = 0;
    pattern_ptr pattern;

    bool operator==(const Material &m)
    {
        return ambient == m.ambient && diffuse == m.diffuse && specular == m.specular && shininess == m.shininess &&
               color == m.color;
    }
};
