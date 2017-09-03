#include "sphere.h"
#include <cmath>

Sphere::Sphere(const Vector3& center, float radius, const std::string& materialName)
    : center(center), radius(radius), radius2(radius * radius) 
{ 
    Traceable::setMaterial(materialName);
}

bool Sphere::intersects(const Ray &ray, Intersection &intersection) const
{
    Vector3 oc = ray.origin - center;
    float a = dot(ray.direction, ray.direction);
    float b = dot(oc, ray.direction);
    float c = dot(oc, oc) - radius2;
    float descriminant = b * b - a * c;

    if (descriminant > 0)
    {
        float t0 = (-b - sqrt(descriminant)) / a;
        float t1 = (-b + sqrt(descriminant)) / a;

        if (t0 > t1)
            t0 = t1;

        if (t0 > 0)
        {
            intersection.distance = t0;
            intersection.point = ray.point(t0);

            Vector3 dir = intersection.point - center;
            normalize(dir);
            intersection.normal = dir;

            intersection.object = this;
            intersection.hit = true;
            return true;
        }
    }

    return false;
}