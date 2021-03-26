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