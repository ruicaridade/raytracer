#include "ray.h"

Ray::Ray(const Vector3& origin, const Vector3& direction)
    : origin(origin), direction(direction) { }

Vector3 ray_get_point(const Ray& ray, float t)
{
    return ray.origin + ray.direction * t;
}