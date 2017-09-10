#include "checker_texture.h"
#include <glm\glm.hpp>

CheckerTexture::CheckerTexture(const Vector3& odd, const Vector3& even)
    : odd(odd), even(even) { }

Vector3 CheckerTexture::color(int u, int v, const Vector3 &point)
{
    float sines = glm::sin(10.0f * point.x) * glm::sin(10.0f * point.y) * glm::sin(10.0f * point.z);

    if (sines < 0)
    {
        return odd;
    }

    return even;
}