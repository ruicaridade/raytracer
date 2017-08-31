#include "math.h"
#include <math.h>

Vector3::Vector3(float x, float y, float z)
    : x(x), y(y), z(z) { }

Ray::Ray(const Vector3& origin, const Vector3& direction)
    : origin(origin), direction(direction) { }

Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
    return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
    return Vector3(v1.x + v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3 operator*(const Vector3& vector, float scalar)
{
    return Vector3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

float length(const Vector3& vector)
{
    return sqrt(vector.x * vector.x + 
        vector.y * vector.y + 
        vector.z * vector.z);
}

float dot(const Vector3& a, const Vector3& b)
{
    return a.x * b.x + 
        a.y * b.y + 
        a.z * b.z;
}

Vector3& normalize(Vector3& vector)
{
    float l = length(vector);
    vector.x /= l;
    vector.y /= l;
    vector.z /= l;
    return vector;
}

Vector3 ray_get_point(const Ray& ray, float t)
{
    return ray.origin + ray.direction * t;
}