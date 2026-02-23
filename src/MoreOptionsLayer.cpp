#include <Geode/modify/MoreOptionsLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

#define DEFINE_KEYBIND\
	void defineKeybind(std::string id, std::function<void()> callback) {\
		this->addEventListener(\
            KeybindSettingPressedEventV3(Mod::get(), id),\
            [this, callback](Keybind const& keybind, bool down, bool repeat, double timestamp) {\
				if (!down || repeat) return;\
				callback();\
            }\
        );\
	}

#define PRESS(query) Utils::activateButtonSafe(query, this);
#define RETURN_IF_DISABLED(setting) if (!Utils::modEnabled() || !Utils::getBool(setting)) return;

class $modify(MyMoreOptionsLayer, MoreOptionsLayer) {
	DEFINE_KEYBIND
	bool init() {
		if (!MoreOptionsLayer::init()) return false;
		this->defineKeybind("previous-options-page", [this]() {
			RETURN_IF_DISABLED("moreOptionsLayer")
			PRESS("main-layer > togglers-menu > left-arrow-button")
		});
		this->defineKeybind("next-options-page", [this]() {
			RETURN_IF_DISABLED("moreOptionsLayer")
			PRESS("main-layer > togglers-menu > right-arrow-button")
		});
		return true;
	}
};