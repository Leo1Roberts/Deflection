#ifndef EMPTY_MODE_H
#define EMPTY_MODE_H

#include "AppMode.h"
#include "GameScreen.h"


class GameMode : public AppMode {
public:
	GameMode();

private:
	void playGame();

	std::unique_ptr<GameScreen> emptyScreen;
};


#endif // EMPTY_MODE_H
