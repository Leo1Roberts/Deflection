#ifndef EMPTY_SCREEN_H
#define EMPTY_SCREEN_H

#include "Screen.h"
#include "utilities/CameraPerspective.h"


class EmptyScreen : public Screen {
public:
	EmptyScreen();

	void processEvent(const Event& event) override;
	void update(microseconds dt) override;
	void render() override;

private:
	void doResize() override;

	CameraPerspective camera;
};


#endif // EMPTY_SCREEN_H
