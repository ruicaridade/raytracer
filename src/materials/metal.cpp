#include "metal.h"
#include <glm\glm.hpp>
#include "..\utilities\random.h"

Metal::Metal(const Vector3& albedo, float fuzziness)
    : albedo(albedo), fuzziness(fuzziness) {}

bool Metal::scatter(const Ray& ray, const Intersection& intersection,
    Vector3& attenuation, Ray& scattered) const
{
    Vector3 reflected = glm::reflect(ray.direction, glm::normalize(intersection.normal));
    scattered = Ray(intersection.point, reflected + fuzziness * Random::randomInUnitSphere());
    attenuation = albedo;
    return glm::dot(scattered.direction, intersection.normal) > 0;
}