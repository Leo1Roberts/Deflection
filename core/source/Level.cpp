#include "Level.h"


Level::Level(int number) : number(number) {
	rng.seed(hashSeed((unsigned int)number));

	float radius = 300.f;//1e23f * std::pow(10.f, (float)randomIntInRange(0, 100) * 0.05f);
	glm::vec3 position = {1500.f, 400.f, 300.f};
	planets.emplace_back(radius, position);
}


unsigned int Level::hashSeed(unsigned int seed) {
	seed ^= seed >> 16;
	seed *= 0x7feb352d;
	seed ^= seed >> 15;
	seed *= 0x846ca68b;
	seed ^= seed >> 16;
	return seed;
}

int Level::randomIntInRange(int min, int max) {
	std::uniform_int_distribution dist(min, max);
	return dist(rng);
}


