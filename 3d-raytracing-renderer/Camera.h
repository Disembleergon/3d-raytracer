#pragma once
#include <cmath>

#include "Matrix.h"

// Camera is always 1 unit from the canvas away

class Ray;

class Camera
{

  private:
    Matrix transform = IDENTITY_MATRIX();
    Matrix inversedTransform = IDENTITY_MATRIX();

  public:
    const int hsize;
    const int vsize;
    const double fov;
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
    void setTransformation(Matrix);
    Matrix getTransformation();
    Matrix getInversedTransformation();
};
