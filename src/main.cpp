#include <iostream>
#include <future>
#include "raytracer.h"
#include "utilities.h"

#define IMAGE_SCALE 		0.5f
#define IMAGE_WIDTH 		int(256 * IMAGE_SCALE)
#define IMAGE_HEIGHT 		int(144 * IMAGE_SCALE)

#define SHOW_PROGRESS 		1
#define PROGRESS_INTERVAL	(IMAGE_WIDTH * IMAGE_HEIGHT * 0.05f)

int main()
{
	printf("Resolution: %i, %i\n", IMAGE_WIDTH, IMAGE_HEIGHT);
	std::vector<std::vector<Color>> output;

	printf("Drawing scene...\n");
	// Bottom left corner of the lens
	Vector3 zero(-2, -1, -1);

	// Lens size
	Vector3 horizontal(4, 0, 0);
	Vector3 vertical(0, 2, 0);

	Vector3 origin(0, 0, 0);
	for (int y = IMAGE_HEIGHT - 1; y >= 0; y--)
	{
		std::vector<Color> row;
		for (int x = 0; x < IMAGE_WIDTH; x++)
		{
			float xx = (float)x / IMAGE_WIDTH;
			float yy = (float)y / IMAGE_HEIGHT;

			Ray ray(origin, zero + horizontal * xx + vertical * yy);
			row.push_back(Color(y * 255.0f / IMAGE_HEIGHT, 0, 0, 255));

#if SHOW_PROGRESS
			static int progress = 0;
			static int interval = 0;
			progress++;
			interval++;

			if (interval >= PROGRESS_INTERVAL)
			{
				interval = 0;
				std::cout << "\r";
				std::cout << "Progress: " << float(progress) / (IMAGE_WIDTH * IMAGE_HEIGHT) * 100 << "%";
			}
#endif
		}

		output.push_back(row);
	}

#if SHOW_PROGRESS
	std::cout << std::endl;
#endif

	printf("Writing to image file...\n");
	colors_to_png("output.png", output);

	printf("Done!\n");
	return 0;
}