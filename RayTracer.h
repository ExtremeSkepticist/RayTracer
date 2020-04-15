#pragma once

#include <cstdint>
#include <vector>

#include "Sphere.h"

void Render(const std::vector<Sphere>& spheres);

Vector3F TraceRay(const Vector3F& rayOrigin
	, const Vector3F& rayDirection
	, const std::vector<Sphere>& spheres
	, const int32_t& depth);