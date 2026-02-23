#include <Geode/modify/CreatorLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

// highkey this macro better work or else
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
#define PRESS_CREATOR(name) PRESS("creator-buttons-menu > " name "-button")
#define RETURN_IF_DISABLED if (!Utils::modEnabled() || !Utils::getBool("creatorLayer")) return;
#define RETURN_IF_NOT_ACTIVE if (this->getChildByType<FLAlertLayer>(0) || this->getChildByType<DialogLayer>(0) || CCScene::get()->getChildByType<FLAlertLayer>(0) || !CCScene::get()->getChildByID("CreatorLayer")) return;
#define EARLY_RETURN\
	RETURN_IF_DISABLED\
	RETURN_IF_NOT_ACTIVE

class $modify(MyCreatorLayer, CreatorLayer) {
	DEFINE_KEYBIND
	bool init() {
		if (!CreatorLayer::init()) return false;
		this->defineKeybind("creatorlayer-create", [this]() {
			EARLY_RETURN
			PRESS_CREATOR("create")
		});
		this->defineKeybind("creatorlayer-saved", [this]() {
			EARLY_RETURN
			PRESS_CREATOR("saved")
		});
		this->defineKeybind("creatorlayer-scores", [this]() {
			EARLY_RETURN
			PRESS_CREATOR("scores")
		});
		this->defineKeybind("creatorlayer-quests", [this]() {
			EARLY_RETURN
			PRESS_CREATOR("quests")
		});
		this->defineKeybind("creatorlayer-versus", [this]() {
			EARLY_RETURN
			PRESS_CREATOR("versus")
		});
		this->defineKeybind("creatorlayer-map", [this]() {
			EARLY_RETURN
			PRESS_CREATOR("map")
		});
		this->defineKeybind("creatorlayer-daily", [this]() {
			EARLY_RETURN
			PRESS_CREATOR("daily")
		});
		this->defineKeybind("creatorlayer-weekly", [this]() {
			EARLY_RETURN
			PRESS_CREATOR("weekly")
		});
		this->defineKeybind("creatorlayer-event", [this]() {
			EARLY_RETURN
			PRESS_CREATOR("event")
		});
		this->defineKeybind("creatorlayer-gauntlets", [this]() {
			EARLY_RETURN
			PRESS_CREATOR("gauntlets")
		});
		this->defineKeybind("creatorlayer-featured", [this]() {
			EARLY_RETURN
			PRESS_CREATOR("featured")
		});
		this->defineKeybind("creatorlayer-lists", [this]() {
			EARLY_RETURN
			PRESS_CREATOR("lists")
		});
		this->defineKeybind("creatorlayer-paths", [this]() {
			EARLY_RETURN
			PRESS_CREATOR("paths")
		});
		this->defineKeybind("creatorlayer-map-packs", [this]() {
			EARLY_RETURN
			PRESS_CREATOR("map-packs")
		});
		this->defineKeybind("creatorlayer-search", [this]() {
			EARLY_RETURN
			PRESS_CREATOR("search")
		});
		return true;
	}
};