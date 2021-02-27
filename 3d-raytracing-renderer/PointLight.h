#pragma once
#include "Color.h"
#include "Tuple.h"
#include <math.h>

struct PointLight
{

    Tuple position{0, 0, 0, 0};
    // describes intensity/color of the light source
    Color intensity{0, 0, 0};
};

inline Color lighting(const Material &mat, const PointLight &light, const Tuple &poi, const Tuple &eyev,
                      const Tuple &normalv)
{

    // combine the surface color with the light's color/intensity
    Color effective_color = mat.color * light.intensity;

    // find the direction to the light source
    Tuple lightv = normalize(light.position - poi);

    // compute the ambient contribution
    Color ambient = effective_color * mat.ambient;

    /*	light_dot_normal represents the cosine of the angle between the
        light vectorand the normal vector.A negative number means the
        light is on the other side of the surface. */

    double light_dot_normal = dot(lightv, normalv);

    if (light_dot_normal < 0)
    {
        return ambient;
    }

    // compute the diffuse contribution
    Color diffuse = effective_color * mat.diffuse * light_dot_normal;

    /*	reflect_dot_eye represents the cosine of the angle between the
        reflection vectorand the eye vector.A negative number means the
        light reflects away from the eye. */

    Tuple reflectv = reflect(lightv * -1, normalv);
    double reflect_dot_eye = dot(reflectv, eyev);

    if (reflect_dot_eye <= 0)
        return (ambient + diffuse);

    // compute the specular contribution
    double factor = pow(reflect_dot_eye, mat.shininess);
    Color specular = light.intensity * mat.specular * factor;

    // return final shading
    return (ambient + diffuse + specular);
}
