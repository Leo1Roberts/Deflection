#include "EmptyMode.h"

EmptyMode::EmptyMode() {
	doNothing();
}


void EmptyMode::doNothing() {
	emptyScreen = std::make_unique<EmptyScreen>();
	resizeToMatchActiveScreen(emptyScreen.get());
	activeScreen = emptyScreen.get();
}