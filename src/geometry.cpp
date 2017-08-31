#include "geometry.h"
#include <cmath>
#include <limits>

Sphere::Sphere(const Vector3& center, float radius)
    : center(center), radius(radius), radius2(radius * radius) { }

Intersection::Intersection()
    : distance(std::numeric_limits<float>::max()), hit(false) { }

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
        float t0 = (-b - sqrt(descriminant)) / a;
        float t1 = (-b + sqrt(descriminant)) / a;

        if (t0 > t1)
            t0 = t1;

        if (t0 > 0)
        {
            intersection.distance = t0;
            intersection.type = ObjectType::Sphere;
            intersection.point = ray_get_point(ray, t0);
    
            Vector3 dir = intersection.point - sphere.center;
            normalize(dir);
            intersection.normal = dir;
    
            intersection.hit = true;
            return intersection;
        }
    }

    return intersection;
}