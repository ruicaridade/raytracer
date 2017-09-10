#pragma once
#include <memory>
#include "..\material.h"
#include "..\texture.h"

typedef std::shared_ptr<Texture> TexturePtr;

class Metal : public Material
{
public:
    Metal(const Vector3& albedo, float fuzziness, TexturePtr texture);

    virtual bool scatter(const Ray& ray, const Intersection& intersection,
        Vector3& attenuation, Ray& scattered) const override;

private:
    Vector3 albedo;
    TexturePtr texture;
    float fuzziness;
};