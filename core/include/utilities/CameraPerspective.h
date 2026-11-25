#ifndef CAMERA_PERSPECTIVE_H
#define CAMERA_PERSPECTIVE_H

#include <glm/glm.hpp>


class CameraPerspective {
public:
	CameraPerspective();

	void reset();
	void update(float screenWidth, float screenHeight);

	void rotateHeading(float radians);
	void rotatePitch(float radians);
	void setOrigin(glm::vec3 o) { origin = o; }

	[[nodiscard]] const glm::mat4& getViewMatrix() const { return viewMatrix; }
	[[nodiscard]] const glm::mat4& getProjectionMatrix() const { return projectionMatrix; }
	[[nodiscard]] glm::mat3 getViewRotationMatrix() const { return glm::mat3(viewMatrix); }
	[[nodiscard]] glm::mat3 getWorldToViewRotationMatrix() const { return transpose(getViewRotationMatrix()); }

private:
	glm::vec3 origin{};
	float distance{};
	float heading{}, pitch{};
	float fieldOfView{};

	glm::mat4 viewMatrix{}, projectionMatrix{};
};


#endif // CAMERA_PERSPECTIVE_H