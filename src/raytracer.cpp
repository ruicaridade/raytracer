#include "raytracer.h"

Ray::Ray(const Vector3& origin, const Vector3& direction)
    : origin(origin), direction(direction) { }