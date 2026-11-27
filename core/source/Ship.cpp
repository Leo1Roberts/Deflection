#include "Ship.h"
#include "PhysicsConstants.h"
#include "glm/gtc/quaternion.hpp"


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
			case KeyCode::E:
				if (key->action == KeyAction::Down)
					rotating.z = std::min(rotating.z + 1, 1);
				else if (key->action == KeyAction::Up)
					rotating.z = std::max(rotating.z - 1, -1);
				break;
			case KeyCode::Q:
				if (key->action == KeyAction::Down)
					rotating.z = std::max(rotating.z - 1, -1);
				else if (key->action == KeyAction::Up)
					rotating.z = std::min(rotating.z + 1, 1);
				break;
			default:;
		}
	}
}


void Ship::applyForces() {
	glm::quat orientation = glm::quat_cast(rotation);
	glm::quat qHeading = glm::angleAxis(angularVelocity * (float)rotating.x * PHYSICS_TIMESTEP, glm::vec3(0.f, 0.f, 1.f));
	glm::quat qPitch   = glm::angleAxis(angularVelocity * (float)rotating.y * PHYSICS_TIMESTEP, glm::vec3(0.f, 1.f, 0.f));
	glm::quat qRoll    = glm::angleAxis(angularVelocity * (float)rotating.z * PHYSICS_TIMESTEP, glm::vec3(1.f, 0.f, 0.f));
	rotation = glm::mat3_cast(glm::normalize(orientation * qHeading * qPitch * qRoll));

	if (thrusting) {
		if (remainingFuelMass > 0.f) {
			totalForce += rotation * glm::vec3(thrustForce, 0.f, 0.f);
			remainingFuelMass -= 0.000003f;
		}
	}

	mass = dryMass + remainingFuelMass;
	auto acceleration = totalForce / mass;
	velocity += acceleration * PHYSICS_TIMESTEP;
	position += velocity * PHYSICS_TIMESTEP;

	totalForce = glm::vec3(0.f);
}
