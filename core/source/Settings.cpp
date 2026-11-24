#include "Settings.h"
#include "utilities/AssetManager.h"


namespace Settings {
	std::unique_ptr<KeyBindings> Bindings;
	SizePreferences Sizes;

	void load() {
		Bindings = std::make_unique<KeyBindings>(AssetManager::loadTextFile("settings/bindings.cfg"));
	}
}