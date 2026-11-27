#include "Level.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/norm.hpp"


Level::Level(int number) : number(number) {
	rng.seed(hashSeed((unsigned int)number));

	constexpr float minPlanets = 25.f, maxPlanets = 70.f;
	int numPlanets = (int)(maxPlanets - (maxPlanets - minPlanets) * std::exp(-0.04f * (float)(number - 1)));

	planets.reserve(numPlanets);

	float radius = 500.f;
	glm::vec3 position = {
		(float)randomIntInRange(8000, 12000),
		(float)randomIntInRange(-5000, 5000),
		(float)randomIntInRange(-5000, 5000)
	};
	planets.emplace_back(radius, position, true);

	for (int i = 1; i < numPlanets; i++) {
		radius = (float)randomIntInRange(300, 1000);

		bool clashing;
		do {
			clashing = false;

			position = {
				(float)randomIntInRange(-15000, 15000),
				(float)randomIntInRange(-5000, 5000),
				(float)randomIntInRange(-5000, 5000)
			};

			for (int j = 0; j < i; j++) {
				float minSeparation = radius + planets[j].radius + 300;
				if (length2(position - planets[j].position) < minSeparation * minSeparation) {
					clashing = true;
					break;
				}
			}
		} while (clashing);

		planets.emplace_back(radius, position);
	}

	bool clashing;
	do {
		clashing = false;

		shipStartingPosition = {
			(float)randomIntInRange(-14000, -12000),
			(float)randomIntInRange(-2500, 2500),
			(float)randomIntInRange(-2500, 2500)
		};

		for (const auto& p : planets) {
			float minSeparation = p.radius + 500;
			if (length2(shipStartingPosition - p.position) < minSeparation * minSeparation) {
				clashing = true;
				break;
			}
		}
	} while (clashing);
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


