#pragma once
#include "Matrix.h"
#include "Material.h"
#include "Tuple.h"

struct Shape {

	Matrix transform = IDENTITY_MATRIX();
	Material material{};

	void operator = (const Shape& sp) {
		transform = sp.transform;
	}

	Tuple normal_at(const Tuple& p) {
		// world space to object space
		Tuple obj_point = transform.inverse() * p;
		// compute normal
		Tuple obj_normal = p - point(0, 0, 0);
		// object space to world space
		Tuple world_normal = transform.inverse().transpose() * obj_normal;
		// has to be Vector
		world_normal.w = 0;
		return normalize(world_normal);
	}

};