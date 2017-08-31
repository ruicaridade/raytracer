#include <iostream>
#include "raytracer.h"
#include "utilities.h"

int main()
{
	std::vector<std::vector<Color>> colors
	{
		{ Color(255, 0, 0, 255), Color(0, 255, 0, 255), Color(0, 0, 255, 255) },
		{ Color(0, 0, 255, 255), Color(0, 255, 0, 255), Color(255, 0, 0, 255) }
	};

	colors_to_png("test.ppm", colors);
	return 0;
}