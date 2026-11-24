#ifndef SETTINGS_H
#define SETTINGS_H

#include "io/KeyBindings.h"

#include <memory>


struct SizePreferences {
	float uiScale = 1.f;
};


namespace Settings {
	extern std::unique_ptr<KeyBindings> Bindings;
	extern SizePreferences Sizes;

	void load();
}


#endif // SETTINGS_H
