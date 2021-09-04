
#pragma once

#include <cstdint>

class SimplexNoise
{
  public:
    using size_type = double;
    size_type Noise(size_type x, size_type y, size_type z) const;

  private:
    int32_t fastfloor(size_type fp) const
    {
        int32_t i = static_cast<int32_t>(fp);
        return (fp < i) ? (i - 1) : (i);
    }

    uint8_t hash(int32_t i) const;

    size_type grad(int32_t hash, size_type x, size_type y, size_type z) const
    {
        int h = hash & 15;
        size_type u = h < 8 ? x : y;
        size_type v = h < 4 ? y : h == 12 || h == 14 ? x : z;
        return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
    }
};
