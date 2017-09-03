#include <iostream>
#include <random>
#include <chrono>
#include "scene.h"
#include "camera.h"
#include "color.h"
#include "geometry\sphere.h"
#include "math.h"

#include "materials\diffuse.h"

#define IMAGE_SCALE 		4
#define IMAGE_WIDTH 		int(200 * IMAGE_SCALE)
#define IMAGE_HEIGHT 		int(100 * IMAGE_SCALE)

#define TRACE_MAX_DEPTH		3

#define SHOW_PROGRESS 		0
#define PROGRESS_INTERVAL	(IMAGE_WIDTH * IMAGE_HEIGHT * 0.05f)

#define GAMMA				2.2f

float elapsedSeconds()
{
	static auto previous = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = now - previous;
    previous = now;
    return elapsed.count();
}

Color linearToGamma(const Color& color, float value)
{
	Vector3 c = color.toUnitVector();
	float gamma = 1.0f / value;
	Vector3 result = Vector3(pow(c.x, gamma), pow(c.y, gamma), pow(c.z, gamma));
	return Color::fromUnitVector(result);
}

Vector3 randomInUnitSphere()
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

Color trace(Scene& scene, const Ray& ray, int depth)
{
	Intersection intersection;
	scene.forEach([&intersection, ray](const std::unique_ptr<Traceable>& traceable) 
	{
		Intersection temp;
		traceable->intersects(ray, temp);
		if (temp.distance < intersection.distance)
		{
			intersection = temp;
		}
	});

	if (intersection.hit)
	{
		Vector3 target = intersection.point + intersection.normal + randomInUnitSphere();
		Vector3 direction = target - intersection.point;
		normalize(direction);
		return 0.5f * trace(scene, Ray(intersection.point, direction), depth+1);
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
	
	printf("Resolution: %i, %i\n", IMAGE_WIDTH, IMAGE_HEIGHT);
	printf("Drawing scene...\n");
	
	Material::registerMaterial<Diffuse>("diffuse");

	Scene scene;
	scene.add<Sphere>(Vector3(0.5f, 0, -1.5), 0.65f, "diffuse");
	scene.add<Sphere>(Vector3(-0.5f, 0, -1), 0.65f, "diffuse");
	scene.add<Sphere>(Vector3(0, -100.5f, -1), 100, "diffuse");

	Camera camera;
	elapsedSeconds();
	for (int y = IMAGE_HEIGHT - 1; y >= 0; y--)
	{
		std::vector<Color> row;
		for (int x = 0; x < IMAGE_WIDTH; x++)
		{
			float xx = (float)x / IMAGE_WIDTH;
			float yy = (float)y / IMAGE_HEIGHT;

			row.push_back(linearToGamma(trace(scene, camera.cast(xx, yy), 0), GAMMA));
		}

		output.push_back(row);
	}

	float elapsed = elapsedSeconds();
	printf("Done in %.2fms!\n", elapsed*1000);

	printf("Writing to image file...\n");
	elapsedSeconds();
	Color::saveToPng("output.png", output);
	elapsed = elapsedSeconds();

	printf("Done in %.2fms!\n", elapsed*1000);
	return 0;
}