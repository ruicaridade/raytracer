#include "math.h"

Ray::Ray(const Vector3& origin, const Vector3& direction)
    : origin(origin), direction(glm::normalize(direction)) {}

Ray::Ray() { }

Vector3 Ray::point(float distance) const
{
    return origin + direction * distance;
}