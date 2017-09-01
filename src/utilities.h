#pragma once
#include <vector>
#include <string>

struct Color
{
    Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 0);
    
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

Color operator*(const Color& color, float scalar);
Color operator*(float scalar, const Color& color);

void colors_to_png(const std::string& filename, const std::vector<std::vector<Color>>& data);

float elapsed_seconds();