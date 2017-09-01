#include <iostream>
#include <random>
#include "utilities.h"
#include "geometry.h"
#include "camera.h"

#define IMAGE_SCALE 		4
#define IMAGE_WIDTH 		int(200 * IMAGE_SCALE)
#define IMAGE_HEIGHT 		int(100 * IMAGE_SCALE)

#define TRACE_MAX_DEPTH		3

#define SHOW_PROGRESS 		0
#define PROGRESS_INTERVAL	(IMAGE_WIDTH * IMAGE_HEIGHT * 0.05f)

Vector3 random_in_unit_sphere()
{
	static std::random_device device;
	static std::mt19937 generator(device());
	static std::uniform_real_distribution<float> dist(-1, 1);

	Vector3 p = Vector3(dist(generator), dist(generator), dist(generator)) * 2.0f - Vector3(1, 1, 1);
	while(dot(p, p) >= 1.0f) 
	{
		p = Vector3(dist(generator), dist(generator), dist(generator)) * 2.0f - Vector3(1, 1, 1);
	}

	return p;
}

Color trace(const std::vector<Sphere>& spheres, const Ray& ray, int depth)
{
	Intersection intersection;
	for (size_t i = 0; i < spheres.size(); i++)
	{
		Intersection temp = intersects(spheres[i], ray);
		
		if (temp.distance < intersection.distance)
		{
			intersection = temp;
		}
	}

	if (intersection.hit)
	{
		Vector3 target = intersection.point + intersection.normal + random_in_unit_sphere();
		Vector3 direction = target - intersection.point;
		normalize(direction);
		return 0.5f * trace(spheres, Ray(intersection.point, direction), depth+1);
	}
	else
	{
		float t = 0.5f * (ray.direction.y + 1);
		return Color((1 - t) * 255 + t * 128, (1 - t) * 255 + t * 179, (1 - t) * 255 + t * 255, 255);
	}
}

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

			row.push_back(trace(spheres, camera_cast_ray(camera, xx, yy), 0));
		}

		output.push_back(row);
	}

	float elapsed = elapsed_seconds();

	printf("Writing to image file...\n");
	colors_to_png("output.png", output);

	printf("Done in %.2fms!\n", elapsed*1000);
	return 0;
}