#include "TestFunctions.h"

int main()
{

    World w{};

    Sphere sp{};
    sp.material.pattern = new PerlinNoisePattern{new RingPattern{highvalueColor(104, 79, 163), Color{1, 1, 1}}};
    // sp.material.pattern->setTransform(rotate_z(toRadians(45)) * translation(-0.6, 0, 0));
    sp.material.specular = 0.9;
    sp.material.diffuse = 0.7;
    sp.material.ambient = 0.6;
    sp.setTransform(translation(0, 1, 0));
    w.objects.push_back(&sp);

    Plane underground{};
    w.objects.push_back(&underground);

    w.light = PointLight{point(-10, 10, -5), Color{1, 1, 1}};

    Camera cam{800, 400, M_PI / 3};
    cam.setTransformation(view_transform(point(0, 1, -5), point(0, 1, 0), vector(0, 1, 0)));

    w.render(cam).toPPM("C:\\Users\\tompe\\desktop\\scene.ppm");

    system("pause");
    return 0;
}
