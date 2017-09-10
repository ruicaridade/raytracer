#pragma once
#include "..\material.h"

class Emissive : public Material
{
  public:
    Emissive(const Vector3& color, float intensity);

    virtual bool scatter(const Ray &ray, const Intersection &intersection,
                         Vector3 &attenuation, Ray &scattered) const override;

    virtual Vector3 emit(float u, float v, const Vector3 &point) const override;

    Vector3 color;
    float intensity;
};