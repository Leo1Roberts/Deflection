#ifndef LEVEL_H
#define LEVEL_H

#include "Planet.h"

#include <vector>
#include <random>


class Level {
public:
	explicit Level(int number);

	glm::vec3 shipStartingPosition{};
	std::vector<Planet> planets;

private:
	const int number;

	std::mt19937 rng;
	static unsigned int hashSeed(unsigned int seed);
	int randomIntInRange(int min, int max);
};


#endif // LEVEL_H
