#pragma once
#include "..\material.h"

class Metal : public Material
{
public:
    Metal();

    virtual bool scatter(const Ray& ray, const Intersection& intersection,
        Vector3& attenuation, Ray& scattered) const override;
};