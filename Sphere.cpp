#include "Sphere.h"

Sphere::Sphere(const Vector3F& spherePosition
		, const float& radius
		, const Vector3F& surfaceColor
		, const float& reflection
		, const float& transparency
		, const Vector3F& emissionColor)
	: mSpherePosition(spherePosition)
	, mRadius(radius)
	, mRadiusSquared(radius* radius)
	, mSurfaceColor(surfaceColor)
	, mReflection(reflection)
	, mTransparency(transparency)
	, mEmissionColor(emissionColor)
{
}

bool Sphere::IsIntersect(const Vector3F& rayOrigin
	, const Vector3F& rayDirection
	, float* t0
	, float* t1) const
{
	Vector3F diff = mSpherePosition - rayOrigin;
	float tca = diff.GetDotProduct(rayDirection);
	if (tca < 0)
	{
		return false;
	}

	float d2 = diff.GetDotProduct(diff) - tca * tca;
	if (d2 > mRadiusSquared)
	{
		return false;
	}

	float thc = sqrt(mRadiusSquared - d2);
	*t0 = tca - thc;
	*t1 = tca + thc;

	return true;
}

const Vector3F& Sphere::GetSpherePosition() const
{
	return mSpherePosition;
}

float Sphere::GetRadius() const
{
	return mRadius;
}

float Sphere::GetRadiusSquared() const
{
	return mRadiusSquared;
}

const Vector3F& Sphere::GetSurfaceColor() const
{
	return mSurfaceColor;
}

float Sphere::GetReflection() const
{
	return mReflection;
}

float Sphere::GetTransparency() const
{
	return mTransparency;
}

const Vector3F& Sphere::GetEmissionColor() const
{
	return mEmissionColor;
}

void Sphere::SetSpherePosition(const Vector3F& spherePosition)
{
	mSpherePosition = spherePosition;
}

void Sphere::SetRadius(const float& radius)
{
	mRadius = radius;
	mRadiusSquared = radius * radius;
}

void Sphere::SetSurfaceColor(const Vector3F& surfaceColor)
{
	mSurfaceColor = surfaceColor;
}

void Sphere::SetReflection(const float& reflection)
{
	mReflection = reflection;
}

void Sphere::SetTransparency(const float& transparency)
{
	mTransparency = transparency;
}

void Sphere::SetEmissionColor(const Vector3F& emissionColor)
{
	mEmissionColor = emissionColor;
}