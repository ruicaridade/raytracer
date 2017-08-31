#include <iostream>
#include "utilities.h"
#include "geometry.h"
#include "camera.h"

#define IMAGE_SCALE 		4
#define IMAGE_WIDTH 		int(200 * IMAGE_SCALE)
#define IMAGE_HEIGHT 		int(100 * IMAGE_SCALE)

#define SHOW_PROGRESS 		0
#define PROGRESS_INTERVAL	(IMAGE_WIDTH * IMAGE_HEIGHT * 0.05f)

int main()
{
	std::vector<std::vector<Color>> output;
	std::vector<Sphere> spheres
	{
		Sphere(Vector3(0.5f, 0, -1.5), 0.65f),
		Sphere(Vector3(-0.5f, 0, -1), 0.65f),
		Sphere(Vector3(0, -100.5f, -1), 100)
	};
	
	printf("Resolution: %i, %i\n", IMAGE_WIDTH, IMAGE_HEIGHT);
	printf("Drawing scene...\n");
	
	Camera camera;
	elapsed_seconds();
	for (int y = IMAGE_HEIGHT - 1; y >= 0; y--)
	{
		std::vector<Color> row;
		for (int x = 0; x < IMAGE_WIDTH; x++)
		{
			float xx = (float)x / IMAGE_WIDTH;
			float yy = (float)y / IMAGE_HEIGHT;

			Intersection intersection;
			for (size_t i = 0; i < spheres.size(); i++)
			{
				Intersection temp = intersects(spheres[i], camera_cast_ray(camera, xx, yy));
				
				if (temp.distance < intersection.distance)
				{
					intersection = temp;
				}
			}

			if (intersection.hit)
			{
				Vector3 n = intersection.normal;
				row.push_back(Color(0.5f * ((n.x + 1) * 255), 
					0.5f * ((n.y + 1) * 255), 
					0.5f * ((n.z + 1) * 255), 
					255));
			}
			else
			{
				row.push_back(Color(0, 0, 0));
			}
		}

		output.push_back(row);
	}

	float elapsed = elapsed_seconds();

	printf("Writing to image file...\n");
	colors_to_png("output.png", output);

	printf("Done in %.2fms!\n", elapsed*1000);
	return 0;
}