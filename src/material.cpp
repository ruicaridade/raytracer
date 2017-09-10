#include "material.h"

std::map<std::string, std::shared_ptr<Material>> Material::materials;

std::shared_ptr<Material> Material::get(const std::string& name)
{
    return materials[name];
}

Vector3 Material::emit(float u, float v, const Vector3& point) const
{
    return Vector3(0, 0, 0);
}