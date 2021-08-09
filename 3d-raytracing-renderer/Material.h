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
    member_t reflective{0};
    member_t transparency{0};
    member_t refractive_index{1};
    pattern_ptr pattern;

    bool operator==(const Material &m)
    {
        return ambient == m.ambient && diffuse == m.diffuse && specular == m.specular && shininess == m.shininess &&
               color == m.color;
    }
};

namespace RefractiveIndex
{
inline constexpr double glass = 1.5;
inline constexpr double ice = 1.31;
inline constexpr double diamond = 2.417;
inline constexpr double water = 1.33;

} // namespace RefractiveIndex
