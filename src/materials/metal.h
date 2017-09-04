#pragma once
#include "..\material.h"

class Metal : public Material
{
public:
    Metal(const Vector3& albedo, float fuzziness);

    virtual bool scatter(const Ray& ray, const Intersection& intersection,
        Vector3& attenuation, Ray& scattered) const override;

private:
    Vector3 albedo;
    float fuzziness;
};