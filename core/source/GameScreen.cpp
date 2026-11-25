#include "GameScreen.h"

#include "PhysicsConstants.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/norm.hpp"
#include "opengl/Shader.h"
#include "ui/UIList.h"
#include "utilities/MatrixUtilities.h"


GameScreen::GameScreen() : level(1), ship(2.f, 20.f) {
	auto list = uiManager.addNode<UIVerticalList>(5.f, 0.f);
	list->setLayout({
		.anchor = Anchor::TopRight,
		.widthMode = SizingMode::Wrap,
		.heightMode = SizingMode::Wrap,
		.margin = glm::vec2(5.f)
	});
	
	speed = list->addChild<UIText>("", TextStyle{.color = Color::SoftGreen});
}


glm::vec2 p = {0, 0};
void GameScreen::processEvent(const Event& event) {
	if (uiManager.processEvent(event))
		return;

	if (auto pointer = std::get_if<PointerEvent>(&event)) {
		if (pointer->action == PointerAction::StartDrag)
			p = pointer->position;
		else if (pointer->action == PointerAction::Drag) {
			float radPerPix = 6.f / (float)width;
			auto diff = pointer->position - p;
			camera.rotateHeading(-diff.x * radPerPix);
			camera.rotatePitch(diff.y * radPerPix);
			p = pointer->position;
		}
	}

	ship.processEvent(event);
}

void GameScreen::update(microseconds dt) {
	accumulator += toSeconds(dt);

	while (accumulator >= PHYSICS_TIMESTEP) {
		for (const auto& planet : level.planets) {
			auto diff = planet.position - ship.position;
			float r2 = length2(diff);
			ship.totalForce += diff * (G * ship.mass * planet.mass / (r2 * std::sqrt(r2)));
		}

		ship.applyForces();

		for (const auto& planet : level.planets) {
			if (length2(planet.position - ship.position) <= planet.radius * planet.radius) {
				ship.velocity = glm::vec3(0.f);
			}
		}

		accumulator -= PHYSICS_TIMESTEP;
	}

	speed->setText("Speed: " + std::to_string((int)length(ship.velocity)) + "m/s");

	uiManager.update(dt);
}

void GameScreen::render() {
	camera.setOrigin(ship.position);
	camera.update((float)width, (float)height);

#if defined(PLATFORM_DESKTOP)
	glEnable(GL_FRAMEBUFFER_SRGB);
#endif
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	Shaders::object->use();

	Shaders::object->setVec3("uGroundColor", colorToLinear({76, 76, 76}));
	Shaders::object->setVec3("uSkyColor", colorToLinear({85, 110, 128}));
	Shaders::object->setVec3("uSunColor", colorToLinear({255, 255, 230}));
	Shaders::object->setMat4("uProjection", camera.getProjectionMatrix());
	Shaders::object->setVec3("uUpDirection", camera.getWorldToViewRotationMatrix() * glm::vec3(0, 0, 1));
	Shaders::object->setVec3("uSunDirection", camera.getWorldToViewRotationMatrix() * normalize(glm::vec3(2, 2, 3)));

	drawObject(Meshes::ship.get(), Textures::white.get(),
		ship.position, ship.rotation);

	for (const Planet& planet : level.planets)
		drawObject(Meshes::planet.get(), Textures::white.get(),
			planet.position, glm::mat3(1), glm::vec3(planet.radius));

	glDisable(GL_DEPTH_TEST);
#if defined(PLATFORM_DESKTOP)
	glDisable(GL_FRAMEBUFFER_SRGB);
#endif

	uiManager.render();
}


void GameScreen::doResize() {
	uiManager.resize(width, height, dpiScale);

	camera.update((float)width, (float)height);
}


void GameScreen::drawObject(const Mesh<ObjectVertex> *model, const Texture *texture, glm::vec3 position, const glm::mat3 &rotation, glm::vec3 scale) const {
	auto worldMatrix = buildScaledWorldMatrix(rotation, position, scale);

	auto bodyToView = camera.getViewMatrix() * worldMatrix;
	Shaders::object->setMat4("uBodyToView", bodyToView);

	auto bodyToViewRotation = camera.getWorldToViewRotationMatrix() * rotation;
	Shaders::object->setMat3("uBodyToViewRot", bodyToViewRotation, false);

	texture->bind(0);
	model->draw();
}
