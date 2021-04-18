#pragma once
#include "Matrix.h"
//#include "Shape.h"

class Color;
class Tuple;
class Shape;

class Pattern
{
  private:
    Matrix transform = IDENTITY_MATRIX();
    Matrix inversedTransform = IDENTITY_MATRIX();
  public:
    virtual Color pattern_at(Tuple) = 0;

    Color pattern_at_shape(Tuple world_point, Shape *object);
    void setTransform(Matrix);
    Matrix getTransform();
    Matrix getInversedTransform();
};