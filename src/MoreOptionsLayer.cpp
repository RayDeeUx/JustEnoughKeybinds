#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/modify/MoreOptionsLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

#define DEFINE_KEYBIND\
	void defineKeybind(const char* id, std::function<void()> callback) {\
		this->addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {\
			if (event->isDown()) callback();\
			return ListenerResult::Propagate;\
		}, id);\
	}

#define PRESS(query) Utils::activateButtonSafe(query, this);
#define RETURN_IF_DISABLED(setting) if (!Utils::modEnabled() || !Utils::getBool(setting)) return;

class $modify(MyMoreOptionsLayer, MoreOptionsLayer) {
	DEFINE_KEYBIND
	bool init() {
		if (!MoreOptionsLayer::init()) return false;
		this->defineKeybind("previous-options-page"_spr, [this]() {
			RETURN_IF_DISABLED("moreOptionsLayer")
			PRESS("main-layer > togglers-menu > left-arrow-button")
		});
		this->defineKeybind("next-options-page"_spr, [this]() {
			RETURN_IF_DISABLED("moreOptionsLayer")
			PRESS("main-layer > togglers-menu > right-arrow-button")
		});
		return true;
	}
};