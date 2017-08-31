#pragma once
#include <vector>
#include <string>

struct Color
{
    Color(int r = 0, int g = 0, int b = 0, int a = 0);
    
    int r;
    int g;
    int b;
    int a;
};

void colors_to_png(const std::string& filename, const std::vector<std::vector<Color>>& data);