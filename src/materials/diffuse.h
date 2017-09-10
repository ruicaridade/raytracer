#pragma once
#include <memory>
#include "..\material.h"
#include "..\texture.h"

typedef std::shared_ptr<Texture> TexturePtr;

class Diffuse : public Material
{
public:
    Diffuse(const Vector3& albedo, TexturePtr texture);

    virtual bool scatter(const Ray& ray, const Intersection& intersection,
        Vector3& attenuation, Ray& scattered) const override;

    Vector3 albedo;
    TexturePtr texture;
};