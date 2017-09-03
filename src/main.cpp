#include <iostream>
#include <chrono>
#include "raytracer.h"
#include "geometry\sphere.h"
#include "materials\diffuse.h"

#define IMAGE_SCALE 		4
#define IMAGE_WIDTH 		int(200 * IMAGE_SCALE)
#define IMAGE_HEIGHT 		int(100 * IMAGE_SCALE)

#define TRACE_MAX_DEPTH		50

#define PROGRESS_INTERVAL	(IMAGE_WIDTH * IMAGE_HEIGHT * 0.05f)

float elapsedSeconds()
{
	static auto previous = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = now - previous;
    previous = now;
    return elapsed.count();
}

int main()
{
	printf("Resolution: %i, %i\n", IMAGE_WIDTH, IMAGE_HEIGHT);
	printf("Drawing scene...\n");

	Raytracer raytracer(IMAGE_WIDTH, IMAGE_HEIGHT, TRACE_MAX_DEPTH);

	Material::registerMaterial<Diffuse>("diffuse", Vector3(0.5f, 0.8f, 0.25f));

	Scene scene;
	scene.add<Sphere>(Vector3(0.5f, 0, -1.5), 0.65f, "diffuse");
	scene.add<Sphere>(Vector3(-0.5f, 0, -1), 0.65f, "diffuse");
	scene.add<Sphere>(Vector3(0, -100.5f, -1), 100, "diffuse");

	Camera camera;

	elapsedSeconds();
	raytracer.render(scene, camera);
	float elapsed = elapsedSeconds();
	printf("Done in %.2fms!\n", elapsed*1000);

	printf("Writing to image file...\n");
	
	elapsedSeconds();
	raytracer.saveAsImageFile("output.png");
	elapsed = elapsedSeconds();
	printf("Done in %.2fms!\n", elapsed*1000);
	return 0;
}