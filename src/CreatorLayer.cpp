#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/modify/CreatorLayer.hpp>
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
		this->defineKeybind("creatorlayer-create"_spr, [this]() {
			EARLY_RETURN
			PRESS_CREATOR("create")
		});
		this->defineKeybind("creatorlayer-saved"_spr, [this]() {
			EARLY_RETURN
			PRESS_CREATOR("saved")
		});
		this->defineKeybind("creatorlayer-scores"_spr, [this]() {
			EARLY_RETURN
			PRESS_CREATOR("scores")
		});
		this->defineKeybind("creatorlayer-quests"_spr, [this]() {
			EARLY_RETURN
			PRESS_CREATOR("quests")
		});
		this->defineKeybind("creatorlayer-versus"_spr, [this]() {
			EARLY_RETURN
			PRESS_CREATOR("versus")
		});
		this->defineKeybind("creatorlayer-map"_spr, [this]() {
			EARLY_RETURN
			PRESS_CREATOR("map")
		});
		this->defineKeybind("creatorlayer-daily"_spr, [this]() {
			EARLY_RETURN
			PRESS_CREATOR("daily")
		});
		this->defineKeybind("creatorlayer-weekly"_spr, [this]() {
			EARLY_RETURN
			PRESS_CREATOR("weekly")
		});
		this->defineKeybind("creatorlayer-event"_spr, [this]() {
			EARLY_RETURN
			PRESS_CREATOR("event")
		});
		this->defineKeybind("creatorlayer-gauntlets"_spr, [this]() {
			EARLY_RETURN
			PRESS_CREATOR("gauntlets")
		});
		this->defineKeybind("creatorlayer-featured"_spr, [this]() {
			EARLY_RETURN
			PRESS_CREATOR("featured")
		});
		this->defineKeybind("creatorlayer-lists"_spr, [this]() {
			EARLY_RETURN
			PRESS_CREATOR("lists")
		});
		this->defineKeybind("creatorlayer-paths"_spr, [this]() {
			EARLY_RETURN
			PRESS_CREATOR("paths")
		});
		this->defineKeybind("creatorlayer-map-packs"_spr, [this]() {
			EARLY_RETURN
			PRESS_CREATOR("map-packs")
		});
		this->defineKeybind("creatorlayer-search"_spr, [this]() {
			EARLY_RETURN
			PRESS_CREATOR("search")
		});
		return true;
	}
};