#include "geometry.h"
#include <cmath>
#include <limits>

Sphere::Sphere(const Vector3& center, float radius)
    : center(center), radius(radius), radius2(radius * radius) { }

Intersection::Intersection()
    : distance(std::numeric_limits<float>::max()) { }

Intersection intersects(const Sphere& sphere, const Ray& ray)
{
    Intersection intersection;

    Vector3 oc = ray.origin - sphere.center;
    float a = dot(ray.direction, ray.direction);
    float b = dot(oc, ray.direction);
    float c = dot(oc, oc) - sphere.radius2;
    float descriminant = b*b - a*c;

    if (descriminant > 0)
    {
        float t = (-b - sqrt(descriminant)) / a;

        intersection.distance = t;
        intersection.type = ObjectType::Sphere;
        intersection.point = ray_get_point(ray, t);

        Vector3 dir = intersection.point - sphere.center;
        normalize(dir);
        intersection.normal = dir;

        intersection.hit = true;
    }

    return intersection;
}