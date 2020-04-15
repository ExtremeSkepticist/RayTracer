#include "RayTracer.h"
#include "Sphere.h"

int main()
{
	std::vector<Sphere> spheres;
	spheres.emplace_back(Sphere(Vector3F(0.0f, -10004.0f, -20.0f)
		, 10000.0f, Vector3F(0.20f, 0.20f, 0.20f), 0.0f, 0.0f));
	spheres.emplace_back(Sphere(Vector3F(0.0f, 0.0f, -20.0f)
		, 4.0f, Vector3F(1.00f, 0.32f, 0.36f), 1.0f, 0.5f));
	spheres.push_back(Sphere(Vector3F(-5.5f, 0.0f, -15.0f)
		, 3.0f, Vector3F(0.9f, 0.9f, 0.9f), 1.0f, 0.0f));

	// light
	spheres.emplace_back(Sphere(Vector3F(0.0f, 20.0f, -30.0f)
		, 3.0f, Vector3F(0.00f, 0.00f, 0.00f), 0.0f, 0.0f
		, Vector3F(3.0f)));
	
	Render(spheres);

	return 0;
}