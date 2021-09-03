#pragma once

#include "Equal.h"
#include <iostream>
#include <math.h>
#include <string>

using member_t = double;

struct Color
{
    member_t red = 0;
    member_t green = 0;
    member_t blue = 0;

    Color normize()
    {
        return Color{floor(red >= 1.0 ? 255 : red * 255), floor(green >= 1.0 ? 255 : green * 255),
                     floor(blue >= 1.0 ? 255 : blue * 255)};
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

inline Color operator*(const Color &clr1, member_t scala)
{
    return {clr1.red * scala, clr1.green * scala, clr1.blue * scala};
}

inline Color operator/(const Color &clr1, const Color &clr2)
{
    return {clr1.red / clr2.red, clr1.green / clr2.green, clr1.blue / clr2.blue};
}

inline Color highvalueColor(const member_t r, const member_t g, const member_t b)
{
    return Color{r / 255, g / 255, b / 255};
}
