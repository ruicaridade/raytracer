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

    virtual Vector3 emit(float u, float v, const Vector3& point) const;

    template <typename T, typename... TArgs>
    static void create(const std::string &name, TArgs... args)
    {
        materials[name] = std::make_shared<T>(args...);
    }

    static std::shared_ptr<Material> get(const std::string& name);

private:
    static std::map<std::string, std::shared_ptr<Material>> materials;
};