#pragma once
#include "Color.h"
#include "Pattern.h"

class StripePattern : public Pattern
{
  private:
    const Color a;
    const Color b;

  public:
    StripePattern(const Color pA, const Color pB) : a{pA}, b{pB}
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
    const Color a;
    const Color b;

  public:
    RingPattern(const Color pA, const Color pB) : a{pA}, b{pB}
    {
        // empty
    }

    Color pattern_at(Tuple) override;
};

class CheckersPattern : public Pattern
{
  private:
    const Color a;
    const Color b;

  public:
    CheckersPattern(const Color pA, const Color pB) : a{pA}, b{pB}
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
    BlendPattern(Pattern *pA, Pattern *pB) : a{pA}, b{pB}
    {
        // empty
    }

    Color pattern_at(Tuple) override;
};
