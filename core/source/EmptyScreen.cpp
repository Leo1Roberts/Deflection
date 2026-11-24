#include "EmptyScreen.h"
#include "opengl/Shader.h"
#include "utilities/MatrixUtilities.h"


EmptyScreen::EmptyScreen() = default;

glm::vec2 p = {0, 0};
void EmptyScreen::processEvent(const Event& event) {
	if (uiManager.processEvent(event))
		return;

	if (auto pointer = std::get_if<PointerEvent>(&event)) {
		float radPerPix = 6.f / (float)width;
		auto diff = pointer->position - p;
		camera.rotateHeading(-diff.x * radPerPix); // positive for on-spot rotation
		camera.rotatePitch(diff.y * radPerPix); // negative for on-spot rotation
		p = pointer->position;
	}
}

void EmptyScreen::update(microseconds dt) {
	uiManager.update(dt);
}

void EmptyScreen::render() {
	camera.update((float)width, (float)height);

#if defined(PLATFORM_DESKTOP)
	glEnable(GL_FRAMEBUFFER_SRGB);
#endif

	Shaders::object->use();

	Shaders::object->setVec3("uGroundColor", colorToLinear({76, 76, 76}));
	Shaders::object->setVec3("uSkyColor", colorToLinear({85, 110, 128}));
	Shaders::object->setVec3("uSunColor", colorToLinear({255, 255, 230}));
	Shaders::object->setMat4("uProjection", camera.getProjectionMatrix());
	Shaders::object->setVec3("uUpDirection", camera.getWorldToViewRotationMatrix() * glm::vec3(0, 0, 1));
	Shaders::object->setVec3("uSunDirection", camera.getWorldToViewRotationMatrix() * normalize(glm::vec3(2, 2, 3)));

	auto worldMatrix = buildScaledWorldMatrix(glm::mat3(1), glm::vec3(0));

	auto bodyToView = camera.getViewMatrix() * worldMatrix;
	Shaders::object->setMat4("uBodyToView", bodyToView);

	auto bodyToViewRotation = camera.getWorldToViewRotationMatrix() * glm::mat3(1);
	Shaders::object->setMat3("uBodyToViewRot", bodyToViewRotation, false);

	Textures::white->bind(0);
	Meshes::ball->draw();

#if defined(PLATFORM_DESKTOP)
	glDisable(GL_FRAMEBUFFER_SRGB);
#endif

	uiManager.render();
}


void EmptyScreen::doResize() {
	uiManager.resize(width, height, dpiScale);

	camera.update((float)width, (float)height);
}