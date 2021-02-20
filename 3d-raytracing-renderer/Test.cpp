#include "TestFunctions.h"

int main()
{

    World w{};

    Sphere sp{};
    sp.material.color = Color{0.8, 1, 0.6};
    w.objects.push_back(sp);

    PointLight light{point(-10, 10, -10), Color{1, 1, 1}};
    w.lights.push_back(light);

    Camera cam{300, 150, M_PI / 3};
    cam.transform = view_transform(point(0, 0, -5), point(0, 0, 0), vector(0, 1, 0));
    w.render(cam).toPPM("C:\\Users\\tompe\\desktop\\scene.ppm");

    system("pause");
    return 0;
}
