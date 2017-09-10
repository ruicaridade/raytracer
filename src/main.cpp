#include <iostream>
#include <chrono>
#include <fstream>
#include <toml/toml.h>
#include "raytracer.h"
#include "geometry\sphere.h"
#include "geometry\rectangle.h"
#include "materials\diffuse.h"
#include "materials\metal.h"
#include "materials\refractive.h"
#include "materials\emissive.h"
#include "utilities\random.h"
#include "textures\checker_texture.h"

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
	Random::reseed();

	printf("Parsing config... ");
	std::ifstream file("config.toml");
	toml::ParseResult parseResult = toml::parse(file);
	if (!parseResult.valid())
	{
		std::cout << parseResult.errorReason << std::endl;
		return 1;
	}

	const toml::Value& value = parseResult.value;
	int width = value.get<int>("width");
	int height = value.get<int>("height");
	int depth = value.get<int>("depth");
	int antiAliasingPasses = value.get<int>("aa_passes");
	int threadCount = value.get<int>("threads");

	printf("Done!\n");

	printf("Resolution: %i, %i\n", width, height);
	printf("Ray depth: %i\n", depth);
	printf("Anti-aliasing: %i\n\n", antiAliasingPasses);
	printf("Drawing scene... ");

	Raytracer raytracer(width, height, depth);

	Material::create<Diffuse>("brown", Vector3(0.55f, 0.3f, 0.1f), nullptr);
	Material::create<Diffuse>("checker", Vector3(0.75f, 0.75f, 0.75f), 
		std::make_shared<CheckerTexture>(Vector3(0.35f, 0.35f, 0.35f), Vector3(0.5f, 0.5f, 0.5f)));
	
	Material::create<Metal>("ground", Vector3(1, 1, 1), 0.2f,
		std::make_shared<CheckerTexture>(Vector3(0.35f, 0.35f, 0.35f), Vector3(0.5f, 0.5f, 0.5f)));
	Material::create<Metal>("gold", Vector3(1.0f, 0.766f, 0.336f), 0.55f, nullptr);
	Material::create<Metal>("titanium", Vector3(0.672f, 0.637f, 0.585f), 0.15f, nullptr);
	
	Material::create<Refractive>("glass", 1.5f);

	Material::create<Emissive>("light", Vector3(1, 1, 1), 7.5f);

	Scene scene;
	scene.ambient = Vector3(0.5f, 0.5f, 0.5f);

	scene.add<Sphere>(Vector3(0, -100.5f, -1), 100, "checker");
	scene.add<Sphere>(Vector3(10, 10, 0), 3.0f, "light");
	scene.add<Sphere>(Vector3(0, 10, 0), 1.0f, "light");

	scene.add<Sphere>(Vector3(-0.5f, 0.2f, 0), 0.4f, "brown");
	scene.add<Sphere>(Vector3(0.5f, 0.2f, -1), 0.4f, "titanium");
	scene.add<Sphere>(Vector3(0.5f, 0.2f, 0), 0.4f, "gold");

	scene.add<Sphere>(Vector3(-0.5f, 0.2f, -1), 0.4f, "glass");
	// scene.add<Sphere>(Vector3(-0.5f, 0, -1), -0.35f, "glass");

	Camera camera(Vector3(-1.5f, 1.2f, 1), Vector3(0, 1, 0), Vector3(0, 0, -0.5f), float(width) / float(height), 45.0f);

	elapsedSeconds();
	raytracer.render(scene, camera, antiAliasingPasses, threadCount);
	float elapsed = elapsedSeconds();
	printf("Done in %.2fms!\n", elapsed*1000);

	printf("Writing to image file... ");
	
	elapsedSeconds();
	raytracer.saveAsImageFile("output.png");
	elapsed = elapsedSeconds();
	printf("Done in %.2fms!\n", elapsed*1000);
	return 0;
}