#include "rectangle.h"

Rectangle::Rectangle(const Vector2 &p0, const Vector2 &p1, float k, const std::string &materialName)
    : p0(p0), p1(p1), k(k)
{
    Traceable::setMaterial(materialName);
}

bool Rectangle::intersects(const Ray &ray, float min, float max, Intersection &intersection) const
{
    float t = (k - ray.origin.y) / ray.direction.y;

    if (t < min || t > max)
        return false;

    float x = ray.origin.x + t * ray.direction.x;
    float z = ray.origin.z + t * ray.direction.z;

    if (x < p0.x || x > p1.x || z < p0.y || z > p1.y)
        return false;

    intersection.distance = t;
    intersection.point = ray.point(t);
    intersection.normal = Vector3(0, 1, 0);
    intersection.object = this;
    intersection.hit = true;
    return true;
}