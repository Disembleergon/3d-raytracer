#pragma once

using member_t = double;

class Tuple
{
  public:
    member_t x;
    member_t y;
    member_t z;
    int w; //	0=Vector, 1=Point

    Tuple() = default;
};

inline Tuple operator+(const Tuple &tup1, const Tuple &tup2)
{
    return {tup1.x + tup2.x, tup1.y + tup2.y, tup1.z + tup2.z, tup1.w + tup2.w};
}

inline Tuple operator-(const Tuple &tup1, const Tuple &tup2)
{
    return {tup1.x - tup2.x, tup1.y - tup2.y, tup1.z - tup2.z, tup1.w - tup2.w};
}

inline Tuple operator*(const Tuple &tup, member_t scalar)
{
    return {tup.x * scalar, tup.y * scalar, tup.z * scalar, static_cast<int>(tup.w * scalar)};
}

inline Tuple operator/(const Tuple &tup, member_t scalar)
{
    return {tup.x / scalar, tup.y / scalar, tup.z / scalar, static_cast<int>(tup.w / scalar)};
}

Tuple point(member_t Px, member_t Py, member_t Pz);
Tuple vector(member_t Px, member_t Py, member_t Pz);
Tuple negate(const Tuple &);
member_t magnitude(const Tuple &);
Tuple normalize(const Tuple &);
member_t dot(const Tuple &, const Tuple &);
Tuple cross(const Tuple &, const Tuple &);
Tuple reflect(const Tuple &in, const Tuple &norm);
