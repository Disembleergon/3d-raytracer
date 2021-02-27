#pragma once

#include <iostream>
#include <math.h>
#include <string>
#include "Equal.h"

using scalar_t = double;

struct Color
{
    scalar_t red = 0;
    scalar_t green = 0;
    scalar_t blue = 0;

    Color normize(const scalar_t red_max, const scalar_t green_max, const scalar_t blue_max)
    {
        /*scalar_t n_red = (red - 0) * (255 / (red_max - 0));
        scalar_t n_green = (green - 0) * (255 / (green_max - 0));
        scalar_t n_blue = (blue - 0) * (255 / (blue_max - 0));*/

        return Color{floor(red >= 1.0 ? 255 : red * 255), floor(green >= 1.0 ? 255 : green * 255),
                     floor(blue >= 1.0 ? 255 : blue * 255)};

        /* return Color{n_red, n_green, n_blue};*/
    }

    bool operator==(const Color &clr)
    {
        return floatEqual(red, clr.red) && floatEqual(green, clr.green) && floatEqual(blue, clr.blue);
    }
};

inline Color operator+(const Color &clr1, const Color &clr2)
{
    return {clr1.red + clr2.red, clr1.green + clr2.green, clr1.blue + clr2.blue};
}

inline Color operator-(const Color &clr1, const Color &clr2)
{
    return {clr1.red - clr2.red, clr1.green - clr2.green, clr1.blue - clr2.blue};
}

inline Color operator*(const Color &clr1, const Color &clr2)
{
    return {clr1.red * clr2.red, clr1.green * clr2.green, clr1.blue * clr2.blue};
}

inline Color operator*(const Color &clr1, scalar_t scala)
{
    return {clr1.red * scala, clr1.green * scala, clr1.blue * scala};
}

inline Color operator/(const Color &clr1, const Color &clr2)
{
    return {clr1.red / clr2.red, clr1.green / clr2.green, clr1.blue / clr2.blue};
}
