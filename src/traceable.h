#pragma once
#include <memory>
#include <string>
#include "math.h"
#include "intersection.h"
#include "material.h"

class Traceable
{
public:
    virtual bool intersects(const Ray& ray, float min, float max, Intersection& intersection) const = 0;
    std::shared_ptr<Material> getMaterial() const;
    void setMaterial(const std::string& name);

private:
    std::shared_ptr<Material> material;
};