#pragma once
#include <map>
#include <string>
#include <memory>
#include "math.h"
#include "intersection.h"

class Material
{
public:
    virtual bool scatter(const Ray& ray, const Intersection& intersection,
        Vector3& attenuation, Ray& scattered) const = 0;

    template <typename T, typename... TArgs>
    static void registerMaterial(const std::string& name, TArgs... args)
    {
        materials[name] = std::make_shared<T>(args...);
    }

    static std::shared_ptr<Material> getMaterial(const std::string& name);

private:
    static std::map<std::string, std::shared_ptr<Material>> materials;
};