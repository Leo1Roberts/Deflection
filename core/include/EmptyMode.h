#ifndef EMPTY_MODE_H
#define EMPTY_MODE_H

#include "AppMode.h"
#include "EmptyScreen.h"


class EmptyMode : public AppMode {
public:
	EmptyMode();

private:
	void doNothing();

	std::unique_ptr<EmptyScreen> emptyScreen;
};


#endif // EMPTY_MODE_H
