#pragma once
#include "Shape.h"
#include <vector>
#include <algorithm>

struct Intersection {

	double t;
	Shape object;

	Intersection(const double& pt, const Shape& ps)
		: t{ pt }, object{ ps }{}

	Intersection() = default;

	bool operator < (const Intersection& i) {	// for sorting
		return t < i.t;
	}

	/*void operator = (Intersection& i) {
		t = i.t;
		object = i.object;
	}*/

	bool isDefined() {
		return t != NULL;
	}

};

using IntersectionList = std::vector<Intersection>;

// t ist 0 wenn alle Intersections negativ sind!
inline Intersection hit(const IntersectionList& pl) {

	IntersectionList l;

	for (int i = 0; i < pl.size(); i++) {
		if (pl[i].t >= 0)
			l.push_back(pl[i]);
	}

	if (l.size() == 0)
		return Intersection{};

	std::sort(l.begin(), l.end());
	return l[0];

}