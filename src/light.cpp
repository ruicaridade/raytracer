#include "light.h"
#include <algorithm>
#include <glm\glm.hpp>

Light::Light(const Vector3& direction, const Vector3& color)
    : direction(glm::normalize(direction)), color(color) { }

Vector3 Light::process(const Ray& ray, const Intersection& intersection)
{
	float diff = std::max(glm::dot(glm::normalize(intersection.normal), direction), 0.0f);
	return diff * Vector3(1, 1, 1) * color;
}

const Vector3& Light::getDirection() const
{
    return direction;
}

const Vector3& Light::getColor() const
{
    return color;
}