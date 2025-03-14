#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(IHateGarageReimaginedMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		const auto mods = Loader::get()->getAllMods();
		Manager* manager = Manager::getSharedInstance();
		if (manager->calledAlready) return true;
		manager->calledAlready = true;
		for (const Mod* mod : mods) {
			const std::string& modID = mod->getID();
			if (!utils::string::endsWith(modID, ".garage-reimagined") && !utils::string::startsWith(modID, "mrmanama.garage")) continue;
			if (!mod->isEnabled()) break;
			manager->isMrmanamaOrGarageReimagined = true;
			break;
		}
		return true;
	}
};

#define DEFINE_KEYBIND\
	void defineKeybind(const char* id, std::function<void()> callback) {\
		this->addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {\
			if (event->isDown()) callback();\
			return ListenerResult::Propagate;\
		}, id);\
	}

#define PRESS(query) Utils::activateButtonSafe(query, this);
#define FIRST_BUTTON_IN(query) Utils::pressFirstButtonInMenu(query, this);
#define RETURN_IF_DISABLED(setting) if (!Utils::modEnabled() || !Utils::getBool(setting)) return;
#define RETURN_IF_NOT_ACTIVE if (CCScene::get()->getChildByType<FLAlertLayer>(0) || !CCScene::get()->getChildByID("MenuLayer")) return;
#define EARLY_RETURN(setting)\
	RETURN_IF_DISABLED(setting)\
	RETURN_IF_NOT_ACTIVE

class $modify(MyMenuLayer, MenuLayer) {
	DEFINE_KEYBIND
	bool init() {
		if (!MenuLayer::init()) return false;
		/*
		"menulayer-globed"_spr,
		"menulayer-garage"_spr,
		"menulayer-online-menus"_spr,
		"menulayer-my-profile"_spr,
		*/
		return true;
	}
};