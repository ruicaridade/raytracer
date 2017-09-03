#include "diffuse.h"
#include "..\utilities\random.h"

Diffuse::Diffuse(Vector3 albedo)
    : albedo(albedo) { }

bool Diffuse::scatter(const Ray& ray, const Intersection& intersection,
    Vector3& attenuation, Ray& scattered) const
{
    Vector3 target = intersection.point + intersection.normal + Random::randomInUnitSphere();
    Vector3 direction = target - intersection.point;
    normalize(direction);
    scattered = Ray(intersection.point, direction);
    attenuation = albedo;
    return true;
}