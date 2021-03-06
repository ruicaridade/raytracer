#include "diffuse.h"
#include "..\utilities\random.h"

Diffuse::Diffuse(const Vector3 &albedo, TexturePtr texture)
    : albedo(albedo), texture(texture) {}

bool Diffuse::scatter(const Ray &ray, const Intersection &intersection,
                      Vector3 &attenuation, Ray &scattered) const
{
    Vector3 target = intersection.point + intersection.normal + Random::randomInUnitSphere();
    Vector3 direction = target - intersection.point;
    scattered = Ray(intersection.point, glm::normalize(direction));

    if (texture == nullptr)
    {
        attenuation = albedo;
    }
    else
    {
        attenuation = albedo * texture->color(0, 0, intersection.point);
    }

    return true;
}