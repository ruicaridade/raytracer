#pragma once
#include <limits>

class Traceable;
struct Intersection
{
    Intersection()
        : hit(false), distance(std::numeric_limits<float>::max()) { }

    bool hit;
    float distance;
    Vector3 point;
    Vector3 normal;
    const Traceable* object;
};