#include <iostream>
#include <future>
#include "utilities.h"
#include "geometry.h"

#define IMAGE_SCALE 		1
#define IMAGE_WIDTH 		int(200 * IMAGE_SCALE)
#define IMAGE_HEIGHT 		int(100 * IMAGE_SCALE)

#define SHOW_PROGRESS 		0
#define PROGRESS_INTERVAL	(IMAGE_WIDTH * IMAGE_HEIGHT * 0.05f)

int main()
{
	std::vector<std::vector<Color>> output;
	std::vector<Sphere> spheres
	{
		Sphere(Vector3(0, 0, -1), 0.5f)
	};
	
	printf("Resolution: %i, %i\n", IMAGE_WIDTH, IMAGE_HEIGHT);
	printf("Drawing scene...\n");
	// Bottom left corner of the lens
	Vector3 zero(-2, -1, -1);

	// Lens size
	Vector3 horizontal(4, 0, 0);
	Vector3 vertical(0, 2, 0);

	Vector3 origin(0, 0, 0);
	elapsed_seconds();
	for (int y = IMAGE_HEIGHT - 1; y >= 0; y--)
	{
		std::vector<Color> row;
		for (int x = 0; x < IMAGE_WIDTH; x++)
		{
			float xx = (float)x / IMAGE_WIDTH;
			float yy = (float)y / IMAGE_HEIGHT;

			Ray ray(origin, zero + horizontal * xx + vertical * yy);
			for (size_t i = 0; i < spheres.size(); i++)
			{
				auto intersection = intersects(spheres[i], ray);
				if (intersection == nullptr)
				{
					row.push_back(Color(0, 0, 0));
					continue;
				}

				Vector3 n = intersection->normal;
				row.push_back(Color(0.5f * ((n.x + 1) * 255), 
					0.5f * ((n.y + 1) * 255), 
					0.5f * ((n.z + 1) * 255), 
					255));
			}

#if SHOW_PROGRESS
			static int progress = 0;
			static int interval = 0;
			progress++;
			interval++;

			if (interval >= PROGRESS_INTERVAL && progress < IMAGE_WIDTH * IMAGE_HEIGHT)
			{
				interval = 0;
				std::cout << "\r";
				std::cout << "Progress: " << float(progress) / (IMAGE_WIDTH * IMAGE_HEIGHT) * 100 << "%";
			}
			else if (progress >= IMAGE_WIDTH * IMAGE_HEIGHT)
			{
				std::cout << "\r";
				std::cout << "Progress: " << "100%       ";
				std::cout << std::endl;
			}
#endif
		}

		output.push_back(row);
	}

	float elapsed = elapsed_seconds();

	printf("Writing to image file...\n");
	colors_to_png("output.png", output);

	printf("Done in %.2fms!\n", elapsed*1000);
	return 0;
}