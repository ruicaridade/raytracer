#include "math.h"
#include <cmath>
#include <iostream>
#include "external\TinyPngOut.h"

Vector3::Vector3(float x, float y, float z)
    : x(x), y(y), z(z) { }

Ray::Ray(const Vector3& origin, const Vector3& direction)
    : origin(origin), direction(normalize(direction)) {}

Ray::Ray() { }

Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
    return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
    return Vector3(v1.x + v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vector3 operator*(const Vector3& v1, const Vector3& v2)
{
    return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

Vector3 operator*(const Vector3& vector, float scalar)
{
    return Vector3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

Vector3 operator*(float scalar, const Vector3& vector)
{
    return Vector3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

Vector3 operator/(const Vector3& vector, float scalar)
{
    return Vector3(vector.x / scalar, vector.y / scalar, vector.z / scalar); 
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

Vector3 normalize(const Vector3& vector)
{
    float l = length(vector);
    return vector / l;
}

Vector3 Ray::point(float distance) const
{
    return origin + direction * distance;
}

void Vector3::saveToPng(const std::string& filename, const std::vector<std::vector<Vector3>>& data)
{
    if (data.size() == 0)
        return;

    unsigned int height = data.size();
    unsigned int width = data[0].size();

    std::vector<uint8_t> image;

    for (size_t j = 0; j < height; j++)
    {
        for (size_t i = 0; i < width; i++)
        {
            image.push_back((uint8_t)(data[j][i].x * 255));
            image.push_back((uint8_t)(data[j][i].y * 255));
            image.push_back((uint8_t)(data[j][i].z * 255));
        }
    }

    FILE* file = fopen(filename.c_str(), "wb");

    if (file == nullptr)
    {
        std::cout << "Couldn't open file stream " << filename << std::endl;
        return;
    }

    struct TinyPngOut png;

    if (TinyPngOut_init(&png, file, width, height) != TINYPNGOUT_OK)
    {
        fclose(file);
        std::cout << "Couldn't load png file " << filename << std::endl;
        return;
    }

    if (TinyPngOut_write(&png, image.data(), width * height) != TINYPNGOUT_OK)
    {
        fclose(file);
        std::cout << "Couldn't write to png file " << filename << std::endl;
        return;
    }

    if (TinyPngOut_write(&png, nullptr, 0) != TINYPNGOUT_DONE)
    {
        std::cout << "File might be corrupted " << filename << std::endl;
    }

    fclose(file);
}