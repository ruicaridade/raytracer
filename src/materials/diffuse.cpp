#include "diffuse.h"
#include <random>

static Vector3 randomInUnitSphere()
{
	static std::random_device device;
	static std::mt19937 generator(device());
	static std::uniform_real_distribution<float> dist(-1, 1);

	Vector3 p = Vector3(dist(generator), dist(generator), dist(generator)) * 2.0f - Vector3(1, 1, 1);
	while(dot(p, p) >= 1.0f) 
	{
		p = Vector3(dist(generator), dist(generator), dist(generator)) * 2.0f - Vector3(1, 1, 1);
	}

	return p;
}

Diffuse::Diffuse(Vector3 albedo)
    : albedo(albedo) { }

bool Diffuse::scatter(const Ray& ray, const Intersection& intersection,
    Vector3& attenuation, Ray& scattered) const
{
    Vector3 target = intersection.point + intersection.normal + randomInUnitSphere();
    Vector3 direction = target - intersection.point;
    normalize(direction);
    scattered = Ray(intersection.point, direction);
    attenuation = albedo;
    return true;
}