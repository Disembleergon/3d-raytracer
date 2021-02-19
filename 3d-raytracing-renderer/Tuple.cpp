#include "Tuple.h"
#include <math.h>

Tuple vector(scalar_t Px, scalar_t Py, scalar_t Pz) {
	return{ Px, Py, Pz, 0 };
}

Tuple point(scalar_t Px, scalar_t Py, scalar_t Pz) {
	return { Px, Py, Pz, 1 };
}

Tuple negate(const Tuple& tup) {
	return { -tup.x, -tup.y, -tup.z, -tup.w };
}

scalar_t magnitude(const Tuple& vect) {
	
	scalar_t px = pow(vect.x, 2);
	scalar_t py = pow(vect.y, 2);
	scalar_t pz = pow(vect.z, 2);
	scalar_t pw = pow(vect.w, 2);

	return sqrt(px + py + pz + pw);

}

Tuple normalize(const Tuple& vect) {

	return {

		vect.x / magnitude(vect),
		vect.y / magnitude(vect),
		vect.z / magnitude(vect),
		vect.w

	};

}

scalar_t dot(const Tuple& vect1, const Tuple& vect2) {

	return vect1.x * vect2.x +
		vect1.y * vect2.y +
		vect1.z * vect2.z +
		static_cast<scalar_t>(vect1.w) * vect2.w;	// sonst: Arithmetischer Überlauf

}

Tuple cross(const Tuple& tup1, const Tuple& tup2) {
	return{

		tup1.y * tup2.z - tup1.z * tup2.y,
		tup1.z * tup2.x - tup1.x * tup2.z,
		tup1.x * tup2.y - tup1.y * tup2.x,
		0

	};

}

Tuple reflect(const Tuple& in, const Tuple& norm) {
	return in - norm * 2 * dot(in, norm);
}