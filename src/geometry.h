#pragma once
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
    Intersection();

    bool hit;
    float distance;
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

Intersection intersects(const Sphere& sphere, const Ray& ray);