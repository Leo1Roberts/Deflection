#ifndef SHIP_H
#define SHIP_H

#include "io/Event.h"


struct Ship {
	Ship() = default;

	void processEvent(const Event& event);

	void applyForces();

	glm::vec3 position{0.f};
	glm::mat3 rotation{1.f};
	glm::vec3 velocity{0.f};
	glm::vec3 totalForce{0.f};

	bool thrusting = false;
	glm::ivec3 rotating{0};

	static constexpr float dryMass = 1.5f, fullFuelMass = 0.5f, thrustForce = 20.f;

	float mass = dryMass + fullFuelMass;

	static constexpr float angularVelocity = glm::radians(45.f);
};


#endif // SHIP_H
