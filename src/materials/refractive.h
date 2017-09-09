#pragma once
#include "..\material.h"

class Refractive : public Material
{
public:
    Refractive(float refraction);

    virtual bool scatter(const Ray& ray, const Intersection& intersection,
        Vector3& attenuation, Ray& scattered) const override;

    float refraction;
};