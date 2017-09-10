#include "material.h"

std::map<std::string, std::shared_ptr<Material>> Material::materials;

std::shared_ptr<Material> Material::get(const std::string& name)
{
    return materials[name];
}