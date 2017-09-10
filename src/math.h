#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\type_precision.hpp>
#include <glm\vec3.hpp>
#include <glm\vec2.hpp>

typedef glm::vec3 Vector3;
typedef glm::vec2 Vector2;
typedef glm::i32vec2 Vector2i;

class Ray
{
public:
    Ray(const Vector3& origin, const Vector3& direction);
    Ray();

    Vector3 point(float distance) const;

    Vector3 origin;
    Vector3 direction;
};