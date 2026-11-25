#include "GameMode.h"

GameMode::GameMode() {
	playGame();
}


void GameMode::playGame() {
	emptyScreen = std::make_unique<GameScreen>();
	resizeToMatchActiveScreen(emptyScreen.get());
	activeScreen = emptyScreen.get();
}