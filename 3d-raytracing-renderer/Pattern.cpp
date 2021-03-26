#include "Pattern.h"
#include "Color.h"
#include "Shape.h"
#include "Tuple.h"

Color Pattern::pattern_at_shape(Tuple world_point, Shape *object)
{
    Tuple object_point = object->getInversedTransform() * world_point;
    Tuple pattern_point = getInversedTransform() * object_point;

    return pattern_at(pattern_point);
}

void Pattern::setTransform(Matrix n)
{
    transform = n;
    inversedTransform = n.inverse();
}

Matrix Pattern::getTransform()
{
    return transform;
}

Matrix Pattern::getInversedTransform()
{
    return inversedTransform;
}
