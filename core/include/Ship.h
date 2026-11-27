#ifndef SHIP_H
#define SHIP_H

#include "io/Event.h"


struct Ship {
	Ship(float mass, float thrustForce);

	void processEvent(const Event& event);

	void applyForces();

	glm::vec3 position{0.f};
	glm::mat3 rotation{1.f};
	glm::vec3 velocity{0.f};
	glm::vec3 totalForce{0.f};

	bool thrusting = false;
	glm::ivec3 rotating{0};

	const float mass, thrustForce;

	static constexpr float angularVelocity = glm::radians(45.f);
};


#endif // SHIP_H
