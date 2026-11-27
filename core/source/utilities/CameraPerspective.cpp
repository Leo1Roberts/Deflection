#include "utilities/CameraPerspective.h"

#include <algorithm>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "utilities/MatrixUtilities.h"
#include "utilities/Utilities.h"


CameraPerspective::CameraPerspective() {
	reset();
}

void CameraPerspective::reset() {
	origin = glm::vec3(0.f);
	distance = 10.f;
	heading = 0.f;
	pitch = glm::radians(30.f);
	fieldOfView = glm::radians(45.f);
}

void CameraPerspective::update(float screenWidth, float screenHeight) {
	projectionMatrix = glm::perspectiveFov(fieldOfView, screenWidth, screenHeight, 0.01f, 1e6f);

	float ch = cosf(heading);
	float sh = sinf(heading);
	float cp = cosf(pitch);
	float sp = sinf(pitch);

	glm::vec3 eye = {
		origin.x - distance * cp * ch,
		origin.y - distance * cp * sh,
		origin.z + distance * sp
	};

	viewMatrix = glm::lookAt(eye, origin, {0.f, 0.f, 1.f});
}

void CameraPerspective::rotateHeading(float radians) {
	heading = wrapAngle(heading + radians);
}
void CameraPerspective::rotatePitch(float radians) {
	constexpr float limit = glm::half_pi<float>() - 0.1f;
	pitch = std::clamp(pitch + radians, -limit, limit);
}
