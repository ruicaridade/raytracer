#include "metal.h"
#include "..\utilities\random.h"

Metal::Metal(const Vector3& albedo, float fuzziness)
    : albedo(albedo), fuzziness(fuzziness) {}

static Vector3 reflect(const Vector3& I, const Vector3& N)
{
    return I - 2 * dot(I, N) * N;
}

bool Metal::scatter(const Ray& ray, const Intersection& intersection,
    Vector3& attenuation, Ray& scattered) const
{
    Vector3 reflected = reflect(normalize(ray.direction), intersection.normal);
    scattered = Ray(intersection.point, reflected + fuzziness * Random::randomInUnitSphere());
    attenuation = albedo;
    return dot(scattered.direction, intersection.normal) > 0;
}