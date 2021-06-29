#include "TestFunctions.h"

int main()
{

    World w{};

    Sphere sp{};

    auto sphereSolid1 = SolidPattern{highvalueColor(62, 107, 98)};
    auto sphereSolid2 = SolidPattern{highvalueColor(178, 192, 161)};
    auto sphereStripe =
        StripePattern{makePattern_ptr<SolidPattern>(sphereSolid1), makePattern_ptr<SolidPattern>(sphereSolid2)};

    sp.material.pattern =
        makePattern_ptr<JitteredPattern>(JitteredPattern{makePattern_ptr<StripePattern>(sphereStripe), 0.6});
    sp.material.pattern->setTransform(rotate_z(toRadians(50)) * scaling(0.4, 0.4, 0.4));
    sp.material.specular = 0.9;
    sp.material.diffuse = 0.7;
    sp.material.ambient = 0.6;
    sp.setTransform(translation(0, 1, 0));
    w.objects.push_back(&sp);

    Plane underground{};

    // pattern config

    auto solidOne = SolidPattern{highvalueColor(158, 201, 212)};
    auto solidTwo = SolidPattern{highvalueColor(66, 91, 123)};
    auto sOneStripe = StripePattern{makePattern_ptr<SolidPattern>(solidOne), makePattern_ptr<SolidPattern>(solidTwo)};

    auto sOne = JitteredPattern{makePattern_ptr<StripePattern>(sOneStripe), 0.6};
    auto sTwo = StripePattern{makePattern_ptr(solidTwo), makePattern_ptr(solidOne)};

    sTwo.setTransform(rotate_y(toRadians(90)) * scaling(0.7, 0.7, 0.7));
    sOne.setTransform(scaling(0.7, 0.7, 0.7));

    // pattern config end

    underground.material.pattern = makePattern_ptr<BlendPattern>(
        BlendPattern{makePattern_ptr<JitteredPattern>(sOne), makePattern_ptr<StripePattern>(sTwo)});
    w.objects.push_back(&underground);

    w.light = PointLight{point(-10, 10, -5), Color{1, 1, 1}};

    Camera cam{400, 200, M_PI / 3};
    cam.setTransformation(view_transform(point(0, 1, -5), point(0, 1, 0), vector(0, 1, 0)));

    w.render(cam).toPPM("C:\\Users\\tompe\\desktop\\scene.ppm");

    system("pause");
    return 0;
}
