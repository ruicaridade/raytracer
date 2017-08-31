#pragma once
#include <memory>
#include "math.h"
#include "ray.h"

namespace ObjectType { 
enum ObjectType
{
    Sphere,
    Plane
};}

struct Intersection
{
    Vector3 point;
    Vector3 normal;
    ObjectType::ObjectType type;
};

struct Sphere
{
    Sphere(const Vector3& center, float radius);

    Vector3 center;
    float radius;
    float radius2;
};

std::unique_ptr<Intersection> intersects(const Sphere& sphere, const Ray& ray);