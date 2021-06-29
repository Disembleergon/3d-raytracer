#include "TestFunctions.h"

int main()
{

    World w{};

    Plane ground{};

    // ---- pattern -----

    SolidPattern grey1{highvalueColor(114, 115, 117)};
    SolidPattern grey2{highvalueColor(73, 74, 77)};
    StripePattern stripe1{makePattern_ptr<SolidPattern>(grey1), makePattern_ptr<SolidPattern>(grey2)};
    stripe1.setTransform(scaling(0.2, 0.2, 0.2) * rotate_y(toRadians(45)));

    SolidPattern pink1{highvalueColor(214, 39, 71)};
    SolidPattern pink2{highvalueColor(255, 105, 132)};
    StripePattern stripe2{makePattern_ptr<SolidPattern>(pink1), makePattern_ptr<SolidPattern>(pink2)};
    stripe2.setTransform(scaling(0.2, 0.2, 0.2) * rotate_y(toRadians(-45)));

    CheckersPattern checkers{makePattern_ptr<StripePattern>(stripe1), makePattern_ptr<StripePattern>(stripe2)};
    ground.material.pattern = makePattern_ptr<CheckersPattern>(checkers);

    // ---- pattern end -----

    w.addShape<Plane>(ground);

    w.light = PointLight{point(-10, 10, -5), Color{1, 1, 1}};

    Camera cam{400, 200, M_PI / 3};
    cam.setTransformation(view_transform(point(-1, 1.5, -1), point(2, 0, 5), vector(0, 1, 0)));

    w.render(cam).toPPM("C:\\Users\\tompe\\desktop\\scene.ppm");

    system("pause");
    return 0;
}
