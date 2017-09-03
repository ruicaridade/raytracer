#include "material.h"

std::map<std::string, std::shared_ptr<Material>> Material::materials;

std::shared_ptr<Material> Material::getMaterial(const std::string& name)
{
    return materials[name];
}