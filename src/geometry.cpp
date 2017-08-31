#include "geometry.h"
#include <cmath>

Sphere::Sphere(const Vector3& center, float radius)
    : center(center), radius(radius), radius2(radius * radius) { }

std::unique_ptr<Intersection> intersects(const Sphere& sphere, const Ray& ray)
{
    Vector3 oc = ray.origin - sphere.center;
    float a = dot(ray.direction, ray.direction);
    float b = 2.0f * dot(oc, ray.direction);
    float c = dot(oc, oc) - sphere.radius2;
    float descriminant = b*b - 4*a*c;

    if (descriminant > 0)
    {
        float t = (-b - sqrt(descriminant)) / (2.0f * a);

        auto intersection = std::make_unique<Intersection>();
        intersection->type = ObjectType::Sphere;
        intersection->point = ray_get_point(ray, t);
        Vector3 dir = intersection->point - sphere.center;
        normalize(dir);
        intersection->normal = dir;
        return std::move(intersection);
    }

    return nullptr;
}