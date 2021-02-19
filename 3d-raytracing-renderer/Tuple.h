#pragma once

using scalar_t = double;

struct Tuple {

	scalar_t x;
    scalar_t y;
	scalar_t z;
	int w; //	0=Vector, 1=Point
	
	Tuple() = default;

};

inline Tuple operator + (const Tuple& tup1, const Tuple& tup2) {
	return { tup1.x + tup2.x, tup1.y + tup2.y, tup1.z + tup2.z, tup1.w + tup2.w };
}

inline Tuple operator - (const Tuple& tup1, const Tuple& tup2) {
	return { tup1.x - tup2.x, tup1.y - tup2.y, tup1.z - tup2.z, tup1.w - tup2.w };
}

inline Tuple operator * (const Tuple& tup, scalar_t scalar) {
	return { tup.x * scalar, tup.y * scalar, tup.z * scalar, static_cast<int>(tup.w * scalar) };
}

inline Tuple operator / (const Tuple& tup, scalar_t scalar) {
	return { tup.x / scalar, tup.y / scalar, tup.z / scalar, static_cast<int>(tup.w / scalar) };
}

Tuple point(scalar_t Px, scalar_t Py, scalar_t Pz);
Tuple vector(scalar_t Px, scalar_t Py, scalar_t Pz);
Tuple negate(const Tuple&);
scalar_t magnitude(const Tuple&);
Tuple normalize(const Tuple&);
scalar_t dot(const Tuple&, const Tuple&);
Tuple cross(const Tuple&, const Tuple&);
Tuple reflect(const Tuple& in, const Tuple& norm);