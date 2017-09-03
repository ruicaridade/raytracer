#pragma once
#include "..\material.h"

class Diffuse : public Material
{
public:
    Diffuse(Vector3 albedo);

    virtual bool scatter(const Ray& ray, const Intersection& intersection,
        Vector3& attenuation, Ray& scattered) const override;

    Vector3 albedo;
};