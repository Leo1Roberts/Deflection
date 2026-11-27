#ifndef PLANET_H
#define PLANET_H

#include "PhysicsConstants.h"

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"


struct Planet {
	Planet(float radius, glm::vec3 position, bool home = false)
		: radius(radius),
		  mass(4.f/3.f * glm::pi<float>() * radius*radius*radius * PLANET_DENSITY),
		  position(position),
		  home(home) {}

	float radius;
	float mass;
	glm::vec3 position;
	bool home = false;
};


#endif // PLANET_H
