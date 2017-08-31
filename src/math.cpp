#include "math.h"
#include <math.h>

Vector3::Vector3(float x, float y, float z)
    : x(x), y(y), z(z) { }

Vector3 Vector3::operator+(const Vector3& vector)
{
    return Vector3(vector.x + x, vector.y + y, vector.z + z);
}

Vector3 Vector3::operator-(const Vector3& vector)
{
    return Vector3(vector.x - x, vector.y - y, vector.z - z);
}

Vector3 Vector3::operator*(float scalar)
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

void Vector3::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
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

void normalize(Vector3& vector)
{
    float l = length(vector);
    vector.x /= l;
    vector.y /= l;
    vector.z /= l;
}