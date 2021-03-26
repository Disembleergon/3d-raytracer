#include "Camera.h"
#include "Ray.h"
#include "Tuple.h"

Ray Camera::ray_for_pixel(const int &px, const int &py)
{

    // the offset from the edge of the canvas to the pixel's center
    const double xoffset = (px + 0.5) * pixel_size;
    const double yoffset = (py + 0.5) * pixel_size;

    // the untransformed coordinates of the pixel in world space.
    //  (remember that the camera looks toward -z, so +x is to the *left*.)
    const double world_x = half_width - xoffset;
    const double world_y = half_height - yoffset;

    /*	using the camera matrix, transform the canvas point and the origin,
        and then compute the ray's direction vector.
        (remember that the canvas is at z=-1) */
    Tuple pixel = getInversedTransformation() * point(world_x, world_y, -1);
    Tuple origin = getInversedTransformation() * point(0, 0, 0);
    Tuple direction = normalize(pixel - origin);

    return Ray{origin, direction};
}

void Camera::setTransformation(Matrix n)
{
    transform = n;
    inversedTransform = n.inverse();
}

Matrix Camera::getTransformation()
{
    return transform;
}

Matrix Camera::getInversedTransformation()
{
    return inversedTransform;
}