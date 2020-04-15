#include <algorithm>
#include <cassert>
#include <fstream>

#include "RayTracer.h"

Vector3F TraceRay(const Vector3F& rayOrigin
	, const Vector3F& rayDirection
	, const std::vector<Sphere>& spheres
	, const int32_t& depth)
{
	//assert(rayDirection.GetLength() != 1);

	constexpr double CUSTOM_INFINITY = 1e8;
	constexpr uint8_t MAX_RAY_DEPTH = 5U;

	float tNear = CUSTOM_INFINITY;
	const Sphere* intersectedSphere = nullptr;

	// Finds the intersection of a ray with the spheres in the scence
	for (uintmax_t i = 0u; i < spheres.size(); ++i)
	{
		float t0 = CUSTOM_INFINITY;
		float t1 = CUSTOM_INFINITY;

		if (spheres[i].IsIntersect(rayOrigin, rayDirection, &t0, &t1))
		{
			if (t0 < 0.0f)
			{
				t0 = t1;
			}
			if (t0 < tNear)
			{
				tNear = t0;
				intersectedSphere = &spheres[i];
			}
		}
	}

	// Returns Black/Background color if there's no intersection
	if (!intersectedSphere)
	{
		return Vector3F(2.0f);
	}

	Vector3F surfaceColor(0.0f);
	Vector3F pHit = rayOrigin + rayDirection * tNear; // point of intersection
	Vector3F nHit = pHit - intersectedSphere->GetSpherePosition(); // normal at the intersection point
	nHit.Normalize(); // normalize normal direction

	float bias = 1e-4;
	bool bIsInside = false;
	if (rayDirection.GetDotProduct(nHit) > 0.0f)
	{
		nHit = -nHit;
		bIsInside = true;
	}
	if ((intersectedSphere->GetTransparency() > 0.0f || intersectedSphere->GetReflection() > 0.0f)
		&& depth < MAX_RAY_DEPTH)
	{
		float facingRatio = -rayDirection.GetDotProduct(nHit);
		float fresnelEffect = 1.0 * 0.1 + pow(1 - facingRatio, 3) * (1.0 - 0.1);

		Vector3F reflectionDirection = rayDirection - nHit * 2.0f * rayDirection.GetDotProduct(nHit);
		reflectionDirection.Normalize();

		Vector3F reflection = TraceRay(pHit + nHit * bias, reflectionDirection, spheres, depth + 1);
		Vector3F refraction = 0.0f;
		if (intersectedSphere->GetTransparency())
		{
			float ior = 1.1f;
			float eta = bIsInside ? ior : 1.0f / ior;
			float cosi = -nHit.GetDotProduct(rayDirection);
			float k = 1.0f - eta * eta * (1.0f - cosi * cosi);

			Vector3F refractionDirection = rayDirection * eta + nHit * (eta * cosi - sqrt(k));
			refractionDirection.Normalize();
			refraction = TraceRay(pHit - nHit * bias, refractionDirection, spheres, depth + 1);
		}

		surfaceColor = (reflection * fresnelEffect
			+ refraction * (1.0f - fresnelEffect)
			* intersectedSphere->GetTransparency())
			* intersectedSphere->GetSurfaceColor();
	}
	else
	{
		// doesn't need to trace ray if it's diffuse object.
		for (uintmax_t i = 0u; i < spheres.size(); ++i)
		{
			if (spheres[i].GetEmissionColor().GetX() > 0.0f)
			{
				// this is a light
				Vector3F transmission = 1.0f;
				Vector3F lightDirection = spheres[i].GetSpherePosition() - pHit;
				lightDirection.Normalize();

				for (uintmax_t j = 0u; j < spheres.size(); ++j)
				{
					if (i != j)
					{
						float t0;
						float t1;
						if (spheres[j].IsIntersect(pHit + nHit * bias, lightDirection, &t0, &t1))
						{
							transmission = 0.0f;
							break;
						}
					}
				}
				surfaceColor += intersectedSphere->GetSurfaceColor()
					* transmission
					* std::max(0.0f, nHit.GetDotProduct(lightDirection))
					* spheres[i].GetEmissionColor();
			}
		}
	}

	return surfaceColor + intersectedSphere->GetEmissionColor();
}

void Render(const std::vector<Sphere>& spheres)
{
	constexpr float PI = 3.141592653589793f;
	constexpr uintmax_t IMAGE_WIDTH = 640U;
	constexpr uintmax_t IMAGE_HEIGHT = 480U;

	Vector3F* image = new Vector3F[IMAGE_WIDTH * IMAGE_HEIGHT];
	Vector3F* pixel = image;

	float invWidth = 1.0f / static_cast<float>(IMAGE_WIDTH);
	float invHeight = 1.0f / static_cast<float>(IMAGE_HEIGHT);
	float fov = 30.0f;
	float aspectRatio = IMAGE_WIDTH / static_cast<float>(IMAGE_HEIGHT);
	float angle = tan(PI * 0.5f * fov / 180.0f);

	// Trace rays
	for (uintmax_t y = 0u; y < IMAGE_HEIGHT; ++y)
	{
		for (uintmax_t x = 0u; x < IMAGE_WIDTH; ++x)
		{
			float xx = (2.0f * ((x + 0.5f) * invWidth) - 1.0f) * angle * aspectRatio;
			float yy = (1.0f - 2.0f * ((y + 0.5f) * invHeight)) * angle;

			Vector3F rayDirection(xx, yy, -1.0f);
			rayDirection.Normalize();

			*pixel = TraceRay(Vector3F(0), rayDirection, spheres, 0);
			++pixel;
		}
	}

	// Save result to a PPM extension
	std::ofstream ofs("./result.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";
	for (uintmax_t i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT; ++i)
	{
		ofs << static_cast<uint8_t>(std::min(1.0f, image[i].GetX()) * 255.0f)
			<< static_cast<uint8_t>(std::min(1.0f, image[i].GetY()) * 255.0f)
			<< static_cast<uint8_t>(std::min(1.0f, image[i].GetZ()) * 255.0f);
	}

	ofs.close();
	delete[] image;
}