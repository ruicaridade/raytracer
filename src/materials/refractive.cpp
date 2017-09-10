#include "refractive.h"
#include "..\utilities\random.h"

Refractive::Refractive(float refraction)
    : refraction(refraction) { }

static bool refract(const Vector3& I, const Vector3& N, float niOverNt, Vector3& refracted)
{
    Vector3 ui = glm::normalize(I);
    Vector3 un = glm::normalize(N);

    float dt = glm::dot(ui, un);
    float discriminant = 1.0f - niOverNt * niOverNt * (1 - dt * dt);
    if (discriminant > 0)
    {
        refracted = niOverNt * (ui - N * dt) - N * glm::sqrt(discriminant);
        return true;
    }

    return false;
}

static float polyApprox(float cosine, float refraction)
{
    float r = (1.0f - refraction) / (1.0f + refraction);
    r = r * r;
    return r + (1.0f - r) * glm::pow(1.0f - cosine, 5);
}

bool Refractive::scatter(const Ray &ray, const Intersection &intersection, Vector3 &attenuation, Ray &scattered) const
{
    Vector3 outwardNormal;
    Vector3 reflected = glm::reflect(ray.direction, intersection.normal);
    
    float niOverNt;
    attenuation = Vector3(1, 1, 1);
    float cosine;

    if (glm::dot(ray.direction, intersection.normal) > 0)
    {
        outwardNormal = -intersection.normal;
        niOverNt = refraction;
        cosine = glm::dot(ray.direction, intersection.normal) / glm::length(ray.direction);
        cosine = glm::sqrt(1.0f - refraction * refraction * (1.0f - cosine * cosine));
    }
    else
    {
        outwardNormal = intersection.normal;
        niOverNt = 1.0f / refraction;
        cosine = -glm::dot(ray.direction, intersection.normal) / glm::length(ray.direction);
    }

    Vector3 refracted;
    float prob;

    if (refract(ray.direction, outwardNormal, niOverNt, refracted))
    {
        prob = polyApprox(cosine, refraction);
    }
    else
    {
        scattered = Ray(intersection.point, reflected);
        return true;
    }

    if (Random::random() < prob)
    {
        scattered = Ray(intersection.point, reflected);
    }
    else
    {
        scattered = Ray(intersection.point, refracted);
    }

    return true;
}