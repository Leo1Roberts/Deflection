#ifndef EMPTY_SCREEN_H
#define EMPTY_SCREEN_H

#include "Level.h"
#include "Screen.h"
#include "Ship.h"
#include "utilities/CameraPerspective.h"


class GameScreen : public Screen {
public:
	GameScreen();

	void processEvent(const Event& event) override;
	void update(microseconds dt) override;
	void render() override;

private:
	void doResize() override;

	void drawObject(const Mesh<ObjectVertex>* model, const Texture* texture, glm::vec3 position, const glm::mat3& rotation, glm::vec3 scale = glm::vec3(1.f)) const;

	Level level;
	CameraPerspective camera;
	Ship ship;

	float accumulator = 0.f;

	UIText* speed;
};


#endif // EMPTY_SCREEN_H
