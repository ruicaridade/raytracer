#pragma once
#include "..\material.h"

class Diffuse : public Material
{
public:
    virtual bool scatter(const Ray& ray, const Intersection& intersection,
        Vector3 attenuation, Ray& scattered) const override;
};