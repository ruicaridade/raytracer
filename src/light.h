#pragma once
#include "math.h"
#include "intersection.h"

class Light
{
public:
    Light(const Vector3& direction, const Vector3& color);

    Vector3 process(const Ray& ray, const Intersection& intersection);
    const Vector3& getDirection() const;
    const Vector3& getColor() const;

private:
    Vector3 direction;
    Vector3 color;
};