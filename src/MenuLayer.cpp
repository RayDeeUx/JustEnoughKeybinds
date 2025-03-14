#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;
using namespace keybinds;

class $modify(IHateGarageReimaginedMenuLayer, MenuLayer) {
	bool init() {
		Loader* geode = Loader::get();
		const std::vector<Mod*> mods = geode->getAllMods();
		Manager* manager = Manager::getSharedInstance();
		if (manager->calledAlready) return true;
		manager->calledAlready = true;
		for (const Mod* mod : mods) {
			const std::string& modID = mod->getID();
			if (!Utils::isModLoaded(modID)) continue;
			if (!manager->isRedash && modID == "ninxout.redash") manager->isRedash = true;
			if (!manager->isGlobed && modID == "dankmeme.globed2") manager->isGlobed = true;
			if (!manager->isBetterInfo && modID == "cvolton.betterinfo") manager->isBetterInfo = true;
			if (!manager->isLevelSize && modID == "hiimjustin000.level_size") manager->isLevelSize = true;
			if (!manager->isFineOutline && modID == "alphalaneous.fine_outline") manager->isFineOutline = true;
			if (!manager->isSeparateDualIcons && modID == "weebify.separate_dual_icons") manager->isSeparateDualIcons = true;
			if (!manager->isGeodeInPauseMenu && modID == "hiimjustin000.geode_in_pause_menu") manager->isGeodeInPauseMenu = true;
			// split for readability, shut up CLion
			// ReSharper disable CppTooWideScopeInitStatement
			const bool cringeGarageMod = utils::string::endsWith(modID, ".garage-reimagined") || utils::string::startsWith(modID, "mrmanama.garage");
			if (!manager->isMrmanamaOrGarageReimagined && cringeGarageMod) manager->isMrmanamaOrGarageReimagined = true;
		}
		return MenuLayer::init();
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
#define RETURN_IF_DISABLED if (!Utils::modEnabled() || !Utils::getBool("menuLayer")) return;
#define RETURN_IF_NOT_ACTIVE if (CCScene::get()->getChildByType<FLAlertLayer>(0) || !CCScene::get()->getChildByID("MenuLayer")) return;
#define EARLY_RETURN\
	RETURN_IF_DISABLED\
	RETURN_IF_NOT_ACTIVE

class $modify(MyMenuLayer, MenuLayer) {
	DEFINE_KEYBIND
	bool init() {
		if (!MenuLayer::init()) return false;
		this->defineKeybind("menulayer-globed"_spr, [this]() {
			EARLY_RETURN
			PRESS("bottom-menu > dankmeme.globed2/main-menu-button")
		});
		this->defineKeybind("menulayer-garage"_spr, [this]() {
			EARLY_RETURN
			MenuLayer::onGarage(nullptr);
		});
		this->defineKeybind("menulayer-online-menus"_spr, [this]() {
			EARLY_RETURN
			MenuLayer::onCreator(nullptr);
		});
		this->defineKeybind("menulayer-my-profile"_spr, [this]() {
			EARLY_RETURN
			MenuLayer::onMyProfile(nullptr);
		});
		if (!Manager::getSharedInstance()->isRedash) return true;
		log::info("redash is installed! adding redash keybinds");
		return true;
	}
};