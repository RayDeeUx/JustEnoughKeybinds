#include <Geode/modify/MenuLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(IHateGarageReimaginedMenuLayer, MenuLayer) {
	static void onModify(auto& self) {
		(void) self.setHookPriority("MenuLayer::init", Priority::Early);
	}
	bool init() {
		if (!MenuLayer::init()) return false;
		Manager* manager = Manager::getSharedInstance();
		if (manager->calledAlready) return true;
		manager->calledAlready = true;
		for (const Mod* mod : Loader::get()->getAllMods()) {
			const std::string& modID = mod->getID();
			if (!Utils::isModLoaded(modID)) continue;
			if (!manager->isRedash && modID == "ninxout.redash") manager->isRedash = true;
			if (!manager->isGlobed && modID == "dankmeme.globed2") manager->isGlobed = true;
			if (!manager->isBetterInfo && modID == "cvolton.betterinfo") manager->isBetterInfo = true;
			if (!manager->isLevelSize && modID == "hiimjustin000.level_size") manager->isLevelSize = true;
			if (!manager->isFineOutline && modID == "alphalaneous.fine_outline") manager->isFineOutline = true;
			if (!manager->isGeodeTextureLoader && modID == "geode.texture-loader") manager->isGeodeTextureLoader = true;
			if (!manager->isSeparateDualIcons && modID == "weebify.separate_dual_icons") manager->isSeparateDualIcons = true;
			if (!manager->isGeodeInPauseMenu && modID == "hiimjustin000.geode_in_pause_menu") manager->isGeodeInPauseMenu = true;
		}
		log::info("manager->isRedash: {}", manager->isRedash);
		log::info("manager->isGlobed: {}", manager->isGlobed);
		log::info("manager->isBetterInfo: {}", manager->isBetterInfo);
		log::info("manager->isLevelSize: {}", manager->isLevelSize);
		log::info("manager->isFineOutline: {}", manager->isFineOutline);
		log::info("manager->isSeparateDualIcons: {}", manager->isSeparateDualIcons);
		log::info("manager->isGeodeInPauseMenu: {}", manager->isGeodeInPauseMenu);
		return true;
	}
};

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
#define RETURN_IF_DISABLED if (!Utils::modEnabled() || !Utils::getBool("menuLayer")) return;
#define RETURN_IF_NOT_ACTIVE if (this->getChildByType<FLAlertLayer>(0) || this->getChildByType<DialogLayer>(0) || CCScene::get()->getChildByType<FLAlertLayer>(0) || !CCScene::get()->getChildByID("MenuLayer")) return;
#define EARLY_RETURN\
	RETURN_IF_DISABLED\
	RETURN_IF_NOT_ACTIVE

#define PUSH_BUTTON_IN_TYPE(type)\
	CCNode* levelMenu = this->querySelector("ninxout.redash/redash-menu > ninxout.redash/dailies-menu > " type "-node > main-node > level-menu");\
	if (!levelMenu) return;\
	if (const auto skipButton = levelMenu->getChildByID("skip-button")) {\
		if (const auto skip = typeinfo_cast<CCMenuItemSpriteExtra*>(skipButton); skip && skip->isVisible()) return skip->activate();\
	}\
	if (const auto viewButton = levelMenu->getChildByID("view-button")) {\
		if (const auto view = typeinfo_cast<CCMenuItemSpriteExtra*>(viewButton); view && view->isVisible()) return view->activate();\
	}

#define REDASH_PRESS(buttonID)\
	CCNode* theButton = this->querySelector("ninxout.redash/redash-menu > ninxout.redash/main-menu > " buttonID "-button");\
	if (!theButton) theButton = this->querySelector("right-side-menu > " buttonID "-button");\
	if (!theButton) return;\
	if (const auto button = typeinfo_cast<CCMenuItemSpriteExtra*>(theButton); theButton && theButton->isVisible()) return button->activate();

class $modify(MyMenuLayer, MenuLayer) {
	static void onModify(auto& self) {
		if (Manager::getSharedInstance()->isRedash) (void) self.setHookPriorityAfterPost("MenuLayer::init", "ninxout.redash");
		else (void) self.setHookPriority("MenuLayer::init", Priority::First);
	}
	DEFINE_KEYBIND
	bool init() {
		if (!MenuLayer::init()) return false;
		Manager* manager = Manager::getSharedInstance();
		this->defineKeybind("menulayer-globed", [this]() {
			EARLY_RETURN
			PRESS("bottom-menu > dankmeme.globed2/main-menu-button")
		});
		this->defineKeybind("menulayer-garage", [this]() {
			EARLY_RETURN
			MenuLayer::onGarage(nullptr);
		});
		this->defineKeybind("menulayer-online-menus", [this]() {
			EARLY_RETURN
			MenuLayer::onCreator(nullptr);
		});
		this->defineKeybind("menulayer-my-profile", [this]() {
			EARLY_RETURN
			MenuLayer::onMyProfile(nullptr);
		});
		this->defineKeybind("menulayer-daily-chests", [this]() {
			EARLY_RETURN
			MenuLayer::onDaily(nullptr);
		});
		this->defineKeybind("menulayer-texture-packs"_spr, [this, manager]() {
			EARLY_RETURN
			if (!manager->isGeodeTextureLoader) return;
			PRESS("right-side-menu > geode.texture-loader/texture-loader-button")
		});
		log::info("is redash installed?");
		if (!manager->isRedash) return true;
		log::info("redash is installed! adding redash keybinds");
		this->defineKeybind("menulayer-redash-daily", [this]() {
			EARLY_RETURN
			PUSH_BUTTON_IN_TYPE("daily")
		});
		this->defineKeybind("menulayer-redash-weekly", [this]() {
			EARLY_RETURN
			PUSH_BUTTON_IN_TYPE("weekly")
		});
		this->defineKeybind("menulayer-redash-event", [this]() {
			EARLY_RETURN
			PUSH_BUTTON_IN_TYPE("event")
		});
		this->defineKeybind("menulayer-redash-create", [this]() {
			EARLY_RETURN
			REDASH_PRESS("create")
		});
		this->defineKeybind("menulayer-redash-saved", [this]() {
			EARLY_RETURN
			REDASH_PRESS("saved")
		});
		this->defineKeybind("menulayer-redash-paths", [this]() {
			EARLY_RETURN
			REDASH_PRESS("paths")
		});
		this->defineKeybind("menulayer-redash-leaderboards", [this]() {
			EARLY_RETURN
			REDASH_PRESS("leaderboards")
		});
		this->defineKeybind("menulayer-redash-gauntlets", [this]() {
			EARLY_RETURN
			REDASH_PRESS("gauntlets")
		});
		this->defineKeybind("menulayer-redash-featured", [this]() {
			EARLY_RETURN
			REDASH_PRESS("featured")
		});
		this->defineKeybind("menulayer-redash-lists", [this]() {
			EARLY_RETURN
			REDASH_PRESS("lists")
		});
		this->defineKeybind("menulayer-redash-search", [this]() {
			EARLY_RETURN
			REDASH_PRESS("search")
		});
		this->defineKeybind("menulayer-redash-mappacks", [this]() {
			EARLY_RETURN
			REDASH_PRESS("mappacks")
		});
		this->defineKeybind("menulayer-redash-quests", [this]() {
			EARLY_RETURN
			REDASH_PRESS("quests")
		});
		this->defineKeybind("menulayer-redash-the-map", [this]() {
			EARLY_RETURN
			REDASH_PRESS("the-map")
		});
		this->defineKeybind("menulayer-redash-versus", [this]() {
			EARLY_RETURN
			REDASH_PRESS("versus")
		});
		return true;
	}
};