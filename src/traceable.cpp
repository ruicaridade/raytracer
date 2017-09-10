#include "traceable.h"

void Traceable::setMaterial(const std::string& name)
{
    material = Material::get(name);
}

std::shared_ptr<Material> Traceable::getMaterial() const 
{ 
    return material;
}