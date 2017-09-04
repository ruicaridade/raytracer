#pragma once
#include <string>
#include <vector>

struct Vector3
{
    Vector3(float x = 0, float y = 0, float z = 0);

    float x;
    float y;
    float z;

    static void saveToPng(const std::string& filename, const std::vector<std::vector<Vector3>>& data);
};

Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator*(const Vector3& v1, const Vector3& v2);
Vector3 operator*(const Vector3& vector, float scalar);
Vector3 operator*(float scalar, const Vector3& vector);
Vector3 operator/(const Vector3& vector, float scalar);

float length(const Vector3& vector);
float dot(const Vector3& a, const Vector3& b);
Vector3 normalize(const Vector3& vector);

class Ray
{
public:
    Ray(const Vector3& origin, const Vector3& direction);
    Ray();

    Vector3 point(float distance) const;

    Vector3 origin;
    Vector3 direction;
};