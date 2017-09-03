#pragma once
#include "..\traceable.h"

class Sphere : public Traceable
{
public:
    Sphere(const Vector3& center, float radius, const std::string& materialName);

    virtual bool intersects(const Ray& ray, Intersection& intersection) const override;

    Vector3 center;
    float radius;
    float radius2;
};