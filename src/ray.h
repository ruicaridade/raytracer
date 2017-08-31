#pragma once
#include "math.h"

struct Ray
{
    Ray(const Vector3& origin, const Vector3& direction);

    Vector3 origin;
    Vector3 direction;
};

Vector3 ray_get_point(const Ray& ray, float t);