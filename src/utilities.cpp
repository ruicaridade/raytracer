#include "utilities.h"

#include <stdio.h>
#include <iostream>
#include "external\TinyPngOut.h"

Color::Color(int r, int g, int b, int a)
    : r(r), g(g), b(b), a(a) { }
        
void colors_to_png(const std::string& filename, const std::vector<std::vector<Color>>& data)
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
            image.push_back(data[j][i].r);
            image.push_back(data[j][i].g);
            image.push_back(data[j][i].b);
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