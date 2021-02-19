#pragma once
#include "Matrix.h"
#include "Ray.h"
#include <math.h>

// Camera is always 1 unit from the canvas away

class Ray;

struct Camera
{

    const int hsize;
    const int vsize;
    const double fov;
    Matrix transform = IDENTITY_MATRIX();
    double pixel_size;
    double half_width;
    double half_height;

    Camera(const int &hs, const int &vs, const double &field_of_view) : hsize{hs}, vsize{vs}, fov{field_of_view}
    {

        const double half_view = tan(fov / 2);
        const double aspect = hsize / vsize;

        if (aspect >= 1)
        {
            half_width = half_view;
            half_height = half_view / aspect;
        }
        else
        {
            half_width = half_view * aspect;
            half_height = half_view;
        }
        pixel_size = (half_width * 2) / hsize;
    }

    Ray ray_for_pixel(const int &px, const int &py);
};
