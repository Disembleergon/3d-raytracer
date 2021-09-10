#include "TestFunctions.h"
#include <tuple>
#include <vector>

int main()
{
    std::vector<Tuple> examples = {point(0, 1, 0), point(0.5, 1, 0), point(0, 1, 0.5),
                                   point(0, 2, 0), point(0.5, 2, 0), point(0, 2, 0.5)};

    Cylinder cyl{};
    cyl.minimum = 1;
    cyl.maximum = 2;
    cyl.closed = true;

    for (const auto &example : examples)
    {
        const Tuple n = cyl.local_normal_at(example);
        TESTS::printTuple(n);
    }

    system("pause");
}
