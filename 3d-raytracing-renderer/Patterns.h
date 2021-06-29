#pragma once
#include "Color.h"
#include "Pattern.h"

class StripePattern : public Pattern
{
  private:
    pattern_ptr a;
    pattern_ptr b;

  public:
    StripePattern(pattern_ptr pA, pattern_ptr pB) : a{pA}, b{pB}
    {
        // empty
    }

    Color pattern_at(Tuple) override;
};

class GradientPattern : public Pattern
{
  private:
    const Color a;
    const Color b;

  public:
    GradientPattern(const Color pA, const Color pB) : a{pA}, b{pB}
    {
        // empty
    }

    Color pattern_at(Tuple) override;
};

class RingPattern : public Pattern
{
  private:
    pattern_ptr a;
    pattern_ptr b;

  public:
    RingPattern(pattern_ptr pA, pattern_ptr pB) : a{pA}, b{pB}
    {
        // empty
    }

    Color pattern_at(Tuple) override;
};

class CheckersPattern : public Pattern
{
  private:
    pattern_ptr a;
    pattern_ptr b;

  public:
    CheckersPattern(pattern_ptr pA, pattern_ptr pB) : a{pA}, b{pB}
    {
        // empty
    }

    Color pattern_at(Tuple) override;
};

class PerlinNoisePattern : public Pattern
{
  private:
    pattern_ptr p;
    float scaleValue = 0;

  public:
    PerlinNoisePattern(pattern_ptr pattern) : p{pattern}
    {
        // empty
    }

    PerlinNoisePattern(pattern_ptr pattern, float scale) : p{pattern}, scaleValue{scale}
    {
        // empty
    }

    Color pattern_at(Tuple) override;
};

class JitteredPattern : public Pattern
{
  private:
    pattern_ptr p;
    float scaleValue = 0.01;

  public:
    JitteredPattern(pattern_ptr pattern) : p{pattern}
    {
        // empty
    }

    JitteredPattern(pattern_ptr pattern, float scale) : p{pattern}, scaleValue{scale}
    {
        // empty
    }

    Color pattern_at(Tuple) override;
};

class BlendPattern : public Pattern
{
  private:
    pattern_ptr a;
    pattern_ptr b;

  public:
    BlendPattern(pattern_ptr pA, pattern_ptr pB) : a{pA}, b{pB}
    {
        // empty
    }

    Color pattern_at(Tuple) override;
};

class SolidPattern : public Pattern
{
  private:
    const Color clr;

  public:
    SolidPattern(const Color clr) : clr{clr}
    {
        // empty
    }

    Color pattern_at(Tuple) override;
};

// create pattern_ptr. requires a Pattern trype in template
template <typename T> pattern_ptr makePattern_ptr(T p)
{
    return std::make_shared<T>(p);
}