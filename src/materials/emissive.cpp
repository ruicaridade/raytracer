#include "emissive.h"

Emissive::Emissive(const Vector3 &color, float intensity)
    : color(color), intensity(intensity) {}

bool Emissive::scatter(const Ray &ray, const Intersection &intersection, Vector3 &attenuation, Ray &scattered) const
{
    return false;
}

Vector3 Emissive::emit(float u, float v, const Vector3 &point) const
{
    return color * intensity;
}