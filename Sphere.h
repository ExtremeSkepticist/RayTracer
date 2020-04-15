#pragma once

#include "Vector3.h"

typedef Vector3<float> Vector3F;

class Sphere final
{
public:
	Sphere() = default;
	Sphere(const Vector3F& spherePosition
		, const float& radius
		, const Vector3F& surfaceColor
		, const float& reflection = 0.0f
		, const float& transparency = 0.0f
		, const Vector3F & emissionColor = 0.0f);
	Sphere(const Sphere& other) = default;
	Sphere(Sphere&& other) = default;
	virtual ~Sphere() = default;

	Sphere& operator=(const Sphere& other) = default;
	Sphere& operator=(Sphere&& other) = default;

	bool IsIntersect(const Vector3F& rayOrigin, const Vector3F& rayDirection, float* t0, float* t1) const;
	const Vector3F& GetSpherePosition() const;
	float GetRadius() const;
	float GetRadiusSquared() const;
	const Vector3F& GetSurfaceColor() const;
	float GetReflection() const;
	float GetTransparency() const;
	const Vector3F& GetEmissionColor() const;

	void SetSpherePosition(const Vector3F& spherePosition);
	void SetRadius(const float& radius);
	void SetSurfaceColor(const Vector3F& surfaceColor);
	void SetReflection(const float& reflection);
	void SetTransparency(const float& transparency);
	void SetEmissionColor(const Vector3F& emissionColor);

private:
	Vector3F mSpherePosition;
	float mRadius;
	float mRadiusSquared;
	Vector3F mSurfaceColor;
	float mReflection; // surface reflectivity
	float mTransparency; // surface transparency
	Vector3F mEmissionColor; // light
};