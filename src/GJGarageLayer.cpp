#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/modify/CharacterColorPage.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/ShardsPage.hpp>
#include "Manager.hpp"
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

#define BUTTON typeinfo_cast<CCMenuItemSpriteExtra*>
#define PRESS(query) Utils::activateButtonSafe(query, this);
#define FIRST_BUTTON_IN(query) Utils::pressFirstButtonInMenu(query, this);
#define LAST_BUTTON_IN(query) Utils::pressLastButtonInMenu(query, this);
#define FIND_TAB(tab) "category-menu > " tab "-button"
#define SELECT_TAB(tab) if (const auto tabButton = this->querySelector(FIND_TAB(tab)); tabButton) return GJGarageLayer::onSelectTab(tabButton);
#define RETURN_IF_DISABLED if (!Utils::modEnabled() || !Utils::getBool("gjGarageLayer")) return;
#define RETURN_IF_COLOR_PAGE if (this->getChildByType<CharacterColorPage>(0)) return;
#define RETURN_IF_SHARDS_PAGE if (CCScene::get()->getChildByType<ShardsPage>(0)) return;
#define RETURN_IF_UNFOCUSED if (CCScene::get()->getChildByType<FLAlertLayer>(0)) return;
#define EARLY_RETURN\
	RETURN_IF_DISABLED\
	RETURN_IF_COLOR_PAGE\
	RETURN_IF_SHARDS_PAGE\
	RETURN_IF_UNFOCUSED

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyGJGarageLayer, GJGarageLayer) {
    DEFINE_KEYBIND
	bool init() {
    	if (!GJGarageLayer::init()) return false;
    	if (Manager::getSharedInstance()->isMrmanamaOrGarageReimagined && Utils::getBool("gjGarageLayer")) {
    		FLAlertLayer::create("Heads up!", "Things might crash.\n<c_>Be careful out there.</c>\n--JustEnoughKeybinds", "I understand")->show();
    	}
    	this->defineKeybind("garage-cube"_spr, [this]() {
			EARLY_RETURN
			SELECT_TAB("cube")
    	});
    	this->defineKeybind("garage-ship"_spr, [this]() {
			EARLY_RETURN
			SELECT_TAB("ship")
    	});
    	this->defineKeybind("garage-jetpack"_spr, [this]() {
			EARLY_RETURN
			SELECT_TAB("jetpack")
    	});
    	this->defineKeybind("garage-ball"_spr, [this]() {
			EARLY_RETURN
			SELECT_TAB("ball")
    	});
    	this->defineKeybind("garage-ufo"_spr, [this]() {
			EARLY_RETURN
			SELECT_TAB("ufo")
    	});
    	this->defineKeybind("garage-wave"_spr, [this]() {
			EARLY_RETURN
			SELECT_TAB("wave")
    	});
    	this->defineKeybind("garage-robot"_spr, [this]() {
			EARLY_RETURN
			SELECT_TAB("robot")
    	});
    	this->defineKeybind("garage-spider"_spr, [this]() {
			EARLY_RETURN
			SELECT_TAB("spider")
		});
    	this->defineKeybind("garage-swing"_spr, [this]() {
			EARLY_RETURN
			SELECT_TAB("swing")
    	});
    	this->defineKeybind("garage-trail"_spr, [this]() {
			EARLY_RETURN
			SELECT_TAB("trail")
		});
    	this->defineKeybind("garage-death-effect"_spr, [this]() {
			EARLY_RETURN
			SELECT_TAB("death-effect")
    	});
    	this->defineKeybind("garage-shards-page"_spr, [this]() {
			EARLY_RETURN
			PRESS("shards-menu > shards-button")
		});
    	this->defineKeybind("garage-colors-page"_spr, [this]() {
			EARLY_RETURN
			PRESS("shards-menu > color-button")
		});
    	this->defineKeybind("garage-previous-page"_spr, [this]() {
			EARLY_RETURN
			PRESS("prev-page-menu > prev-button")
    	});
    	this->defineKeybind("garage-next-page"_spr, [this]() {
			EARLY_RETURN
			PRESS("next-page-menu > next-button")
    	});
    	this->defineKeybind("garage-first-page"_spr, [this]() {
			EARLY_RETURN
			FIRST_BUTTON_IN("navdot-menu")
    	});
    	this->defineKeybind("garage-last-page"_spr, [this]() {
			EARLY_RETURN
			if (getChildByID("hiimjustin000.more_icons/navdot-menu")->isVisible()) LAST_BUTTON_IN("hiimjustin000.more_icons/navdot-menu")
    		else LAST_BUTTON_IN("navdot-menu")
		});
    	this->defineKeybind("garage-select-p1"_spr, [this]() {
			EARLY_RETURN
			if (!Manager::getSharedInstance()->isSeparateDualIcons) return;
			PRESS("player-buttons-menu > player1-button")
		});
    	this->defineKeybind("garage-select-p2"_spr, [this]() {
			EARLY_RETURN
			if (!Manager::getSharedInstance()->isSeparateDualIcons) return;
			PRESS("player-buttons-menu > player2-button")
		});
    	return true;
    }
};

#undef EARLY_RETURN
#define RETURN_IF_PARENT_IS_SCENE if (CCScene::get() == this->getParent()) return; // goddammit rooot why wont you add node IDs to your buttons :sob:
#define EARLY_RETURN\
	RETURN_IF_PARENT_IS_SCENE\
	RETURN_IF_DISABLED\
	RETURN_IF_SHARDS_PAGE\
	RETURN_IF_UNFOCUSED

#define FINE_OUTLINE Manager::getSharedInstance()->isFineOutline
#define OUTLINE_ID "alphalaneous.fine_outline"
#define FIND_COLOR(color) "buttons-menu > " color "-button"
#define FIND_OTHER_COLOR(color) OUTLINE_ID "/color-tabs-menu > " color "-button"
#define PRESS_COLOR(color)\
	if (!FINE_OUTLINE) return PRESS(FIND_COLOR(color));\
	return PRESS(FIND_OTHER_COLOR(color))

class $modify(MyCharacterColorPage, CharacterColorPage) {
	DEFINE_KEYBIND
	bool init() {
		if (!CharacterColorPage::init()) return false;
		this->defineKeybind("garage-col1"_spr, [this]() {
			EARLY_RETURN
			PRESS_COLOR("col1")
		});
		this->defineKeybind("garage-col2"_spr, [this]() {
			EARLY_RETURN
			PRESS_COLOR("col2")
		});
		this->defineKeybind("garage-glow"_spr, [this]() {
			EARLY_RETURN
			PRESS_COLOR("glow")
		});
		this->defineKeybind("garage-outline"_spr, [this]() {
			EARLY_RETURN
			if (!FINE_OUTLINE) return;
			PRESS("alphalaneous.fine_outline/color-tabs-menu > alphalaneous.fine_outline/outline-button")
		});
		return true;
	}
};

#undef RETURN_IF_UNFOCUSED
#define RETURN_IF_UNFOCUSED if (CCScene::get()->getChildByType<FLAlertLayer>(1)) return;
#undef EARLY_RETURN
#define EARLY_RETURN\
	RETURN_IF_DISABLED\
	RETURN_IF_COLOR_PAGE\
	RETURN_IF_UNFOCUSED

#define PRESS_FROM_MAIN_LAYER(query) Utils::activateButtonSafe(query, this->m_mainLayer);

class $modify(MyShardsPage, ShardsPage) {
	DEFINE_KEYBIND
	bool init() {
		if (!ShardsPage::init()) return false;
		this->defineKeybind("garage-previous-page"_spr, [this]() {
			EARLY_RETURN
			PRESS_FROM_MAIN_LAYER("arrow-buttons-menu > prev-button")
		});
		this->defineKeybind("garage-next-page"_spr, [this]() {
			EARLY_RETURN
			PRESS_FROM_MAIN_LAYER("arrow-buttons-menu > next-button")
		});
		return true;
	}
};