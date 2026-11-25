#include "Ship.h"
#include "PhysicsConstants.h"
#include "glm/gtc/quaternion.hpp"


Ship::Ship(float mass, float thrustForce) :
	mass(mass), thrustForce(thrustForce) {}


void Ship::processEvent(const Event& event) {
	if (auto key = std::get_if<KeyEvent>(&event)) {
		switch (key->chord.code) {
			case KeyCode::Space:
				if (key->action == KeyAction::Down)
					thrusting = true;
				else if (key->action == KeyAction::Up)
					thrusting = false;
				break;
			case KeyCode::A:
				if (key->action == KeyAction::Down)
					rotating.x = std::min(rotating.x + 1, 1);
				else if (key->action == KeyAction::Up)
					rotating.x = std::max(rotating.x - 1, -1);
				break;
			case KeyCode::D:
				if (key->action == KeyAction::Down)
					rotating.x = std::max(rotating.x - 1, -1);
				else if (key->action == KeyAction::Up)
					rotating.x = std::min(rotating.x + 1, 1);
				break;
			case KeyCode::S:
				if (key->action == KeyAction::Down)
					rotating.y = std::min(rotating.y + 1, 1);
				else if (key->action == KeyAction::Up)
					rotating.y = std::max(rotating.y - 1, -1);
				break;
			case KeyCode::W:
				if (key->action == KeyAction::Down)
					rotating.y = std::max(rotating.y - 1, -1);
				else if (key->action == KeyAction::Up)
					rotating.y = std::min(rotating.y + 1, 1);
				break;
			default:;
		}
	}
}


void Ship::applyForces() {
	glm::quat orientation = glm::quat_cast(rotation);
	glm::quat qHeading = glm::angleAxis(angularVelocity * rotating.x * PHYSICS_TIMESTEP, glm::vec3(0.f, 0.f, 1.f));
	glm::quat qPitch   = glm::angleAxis(angularVelocity * rotating.y * PHYSICS_TIMESTEP, glm::vec3(0.f, 1.f, 0.f));
	rotation = glm::mat3_cast(glm::normalize(orientation * qHeading * qPitch));

	if (thrusting)
		totalForce += rotation * glm::vec3(thrustForce, 0.f, 0.f);

	auto acceleration = totalForce / mass;
	velocity += acceleration * PHYSICS_TIMESTEP;
	position += velocity * PHYSICS_TIMESTEP;

	totalForce = glm::vec3(0.f);
}
