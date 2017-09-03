#pragma once
#include <string>
#include <vector>
#include "math.h"

class Color
{
public:
    Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 0);
    
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    Vector3 toUnitVector() const;
    
    static Color fromUnitVector(const Vector3& vector);
    static void saveToPng(const std::string& filename, const std::vector<std::vector<Color>>& data); 
};

Color operator*(const Color& color, float scalar);
Color operator*(float scalar, const Color& color);