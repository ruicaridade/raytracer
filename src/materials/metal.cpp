#include "metal.h"
#include <glm\glm.hpp>
#include "..\utilities\random.h"

Metal::Metal(const Vector3& albedo, float fuzziness, TexturePtr texture)
    : albedo(albedo), fuzziness(fuzziness), texture(texture) {}

bool Metal::scatter(const Ray& ray, const Intersection& intersection,
    Vector3& attenuation, Ray& scattered) const
{
    Vector3 reflected = glm::reflect(ray.direction, glm::normalize(intersection.normal));
    scattered = Ray(intersection.point, reflected + fuzziness * Random::randomInUnitSphere());

    if (texture == nullptr)
    {
        attenuation = albedo;
    }
    else
    {
        attenuation = albedo * texture->color(0, 0, intersection.point);
    }

    return glm::dot(scattered.direction, intersection.normal) > 0;
}