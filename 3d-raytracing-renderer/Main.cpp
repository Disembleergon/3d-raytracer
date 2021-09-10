#include "TestFunctions.h"
#include <tuple>
#include <vector>

int main()
{
    World w{};

    Plane underground{};
    underground.material.color = highvalueColor(153, 238, 255);
    w.addShape<Plane>(underground);

    Cylinder cyl{};
    cyl.material.color = Color{0, 1, 0.3};
    cyl.minimum = 0;
    cyl.maximum = 2;
    w.addShape<Cylinder>(cyl);

    w.light = PointLight{point(2, 10, -5), Color{1, 1, 1}};

    Camera cam{2000, 1000, M_PI / 3};
    cam.setTransformation(view_transform(point(0, 3, -5), point(0, 1, 0), vector(0, 1, 0)));

    w.render(cam).toPPM("C:\\Users\\tompe\\desktop\\scene.ppm");
}
