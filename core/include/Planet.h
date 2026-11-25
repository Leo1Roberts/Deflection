#ifndef PLANET_H
#define PLANET_H

#include "PhysicsConstants.h"

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"


struct Planet {
	Planet(float radius, glm::vec3 position)
		: radius(radius),
		  mass(4.f/3.f * glm::pi<float>() * radius*radius*radius * PLANET_DENSITY),
		  position(position) {}

	float radius;
	float mass;
	glm::vec3 position;
};


#endif // PLANET_H
