#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/modify/DemonFilterSelectLayer.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

/*

	"dependencies": {
		"geode.node-ids": ">=1.22.0"
	},
*/

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

#define BUTTON typeinfo_cast<CCMenuItemSpriteExtra*>
#define PRESS(query) Utils::activateButtonSafe(query, this);

#define PRESS_LENGTH(length) PRESS("length-filter-menu > " length "-filter-button")

#define FIND_DIFF(diff) "difficulty-filter-menu > " diff "-filter-button"
#define PRESS_DIFF(diff) if (CCNode* diffButton = this->querySelector(FIND_DIFF(diff))) return this->toggleDifficulty(diffButton);

#define FIND_QUICK(quickOption) "quick-search-menu > " quickOption "-button"
#define PRESS_QUICK(quick) PRESS(FIND_QUICK(quick))

#define RETURN_IF_DISABLED if (!Utils::modEnabled() || !Utils::getBool("levelSearchLayer")) return;
#define RETURN_IF_NOT_SEARCHING if (this->getChildByType<FLAlertLayer>(0) || CCScene::get()->getChildByType<FLAlertLayer>(0) || !CCScene::get()->getChildByID("LevelSearchLayer")) return;
#define EARLY_RETURN\
	RETURN_IF_DISABLED\
	RETURN_IF_NOT_SEARCHING

class $modify(MyLevelSearchLayer, LevelSearchLayer) {
	DEFINE_KEYBIND
	bool init(int p0) {
		if (!LevelSearchLayer::init(p0)) { return false; }
		if (CCNode* otherFilters = getChildByIDRecursive("other-filter-menu")) {
			this->defineKeybind("level-search-open-filters", [this, otherFilters]() {
				EARLY_RETURN
				const auto advanced = BUTTON(otherFilters->getChildByID("advanced-filters-button"));
				if (!advanced || advanced->getChildByType<CCSprite>(0)->getColor() != ccColor3B{255, 255, 255}) return;
				advanced->activate();
			});
		}
		this->defineKeybind("level-search-clear-filters", [this]() {
			EARLY_RETURN
			this->FLAlert_Clicked(Utils::fakeAlertLayer(0), true);
		});
		this->defineKeybind("level-search-search-mode", [this]() {
			EARLY_RETURN
			LevelSearchLayer::onSearchMode(nullptr);
		});
		this->defineKeybind("level-search-length-tiny", [this]() {
			EARLY_RETURN
			PRESS_LENGTH("tiny")
		});
		this->defineKeybind("level-search-length-short", [this]() {
			EARLY_RETURN
			PRESS_LENGTH("short")
		});
		this->defineKeybind("level-search-length-medium", [this]() {
			EARLY_RETURN
			PRESS_LENGTH("medium")
		});
		this->defineKeybind("level-search-length-long", [this]() {
			EARLY_RETURN
			PRESS_LENGTH("long")
		});
		this->defineKeybind("level-search-length-xl", [this]() {
			EARLY_RETURN
			PRESS_LENGTH("xl")
		});
		this->defineKeybind("level-search-length-plat", [this]() {
			EARLY_RETURN
			PRESS_LENGTH("plat")
		});
		this->defineKeybind("level-search-rate-filter", [this]() {
			EARLY_RETURN
			LevelSearchLayer::toggleStar(nullptr);
		});
		this->defineKeybind("level-search-difficulty-na", [this]() {
			EARLY_RETURN
			PRESS_DIFF("na")
		});
		this->defineKeybind("level-search-difficulty-easy", [this]() {
			EARLY_RETURN
			PRESS_DIFF("easy")
		});
		this->defineKeybind("level-search-difficulty-normal", [this]() {
			EARLY_RETURN
			PRESS_DIFF("normal")
		});
		this->defineKeybind("level-search-difficulty-hard", [this]() {
			EARLY_RETURN
			PRESS_DIFF("hard")
		});
		this->defineKeybind("level-search-difficulty-harder", [this]() {
			EARLY_RETURN
			PRESS_DIFF("harder")
		});
		this->defineKeybind("level-search-difficulty-insane", [this]() {
			EARLY_RETURN
			PRESS_DIFF("insane")
		});
		this->defineKeybind("level-search-difficulty-demon", [this]() {
			EARLY_RETURN
			PRESS_DIFF("demon")
		});
		this->defineKeybind("level-search-difficulty-auto", [this]() {
			EARLY_RETURN
			PRESS_DIFF("auto")
		});
		this->defineKeybind("level-search-demon-filter", [this]() {
			EARLY_RETURN
			PRESS("difficulty-filter-menu > demon-type-filter-button")
		});
		this->defineKeybind("level-search-quick-downloads", [this]() {
			EARLY_RETURN
			PRESS_QUICK("most-downloaded")
		});
		this->defineKeybind("level-search-quick-trending", [this]() {
			EARLY_RETURN
			PRESS_QUICK("trending")
		});
		this->defineKeybind("level-search-quick-awarded", [this]() {
			EARLY_RETURN
			PRESS_QUICK("awarded")
		});
		this->defineKeybind("level-search-quick-likes", [this]() {
			EARLY_RETURN
			PRESS_QUICK("most-liked")
		});
		this->defineKeybind("level-search-quick-recent", [this]() {
			EARLY_RETURN
			PRESS_QUICK("recent")
		});
		this->defineKeybind("level-search-quick-following", [this]() {
			EARLY_RETURN
			PRESS_QUICK("followed")
		});
		this->defineKeybind("level-search-quick-sent", [this]() {
			EARLY_RETURN
			PRESS_QUICK("sent")
		});
		this->defineKeybind("level-search-quick-magic", [this]() {
			EARLY_RETURN
			PRESS_QUICK("magic")
		});
		this->defineKeybind("level-search-quick-friends", [this]() {
			EARLY_RETURN
			PRESS_QUICK("friends")
		});
		return true;
	}
};

#define PRESS_FROM_MAIN_LAYER(query) Utils::activateButtonSafe(query, this->m_mainLayer);
#define PRESS_DEMON(option) PRESS_FROM_MAIN_LAYER("demon-filters > " option "-demon-filter-button")

class $modify(MyDemonFilterSelectLayer, DemonFilterSelectLayer) {
	DEFINE_KEYBIND
	bool init() {
		if (!DemonFilterSelectLayer::init()) return false;
		this->defineKeybind("level-search-all-demons", [this]() {
			RETURN_IF_DISABLED
			PRESS_DEMON("all")
		});
		this->defineKeybind("level-search-easy-demon", [this]() {
			RETURN_IF_DISABLED
			PRESS_DEMON("easy")
		});
		this->defineKeybind("level-search-medium-demon", [this]() {
			RETURN_IF_DISABLED
			PRESS_DEMON("medium")
		});
		this->defineKeybind("level-search-hard-demon", [this]() {
			RETURN_IF_DISABLED
			PRESS_DEMON("hard")
		});
		this->defineKeybind("level-search-insane-demon", [this]() {
			RETURN_IF_DISABLED
			PRESS_DEMON("insane")
		});
		this->defineKeybind("level-search-extreme-demon", [this]() {
			RETURN_IF_DISABLED
			PRESS_DEMON("extreme")
		});
		return true;
	}
};