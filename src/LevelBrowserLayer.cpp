#include <Geode/modify/LeaderboardsLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/modify/LevelListLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/InfoLayer.hpp>
#include "Manager.hpp"
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

#define BETTERINFO_RETURN if (!Manager::getSharedInstance()->isBetterInfo) INSTALL_BETTERINFO_YOU_BLOCKHEAD

#define PRESS(query) Utils::activateButtonSafe(query, this);
#define FIRST_BUTTON_IN(query) Utils::pressFirstButtonInMenu(query, this);
#define RETURN_IF_DISABLED(setting) if (!Utils::modEnabled() || !Utils::getBool(setting)) return;
#define RETURN_IF_NOT_ACTIVE if (CCScene::get()->getChildByType<FLAlertLayer>(0) || GJBaseGameLayer::get()) return;
#define EARLY_RETURN(setting)\
	RETURN_IF_DISABLED(setting)\
	RETURN_IF_NOT_ACTIVE

#define LEADERBOARDS_LAYER_RETURN\
	EARLY_RETURN("leaderboardsLayer")\
	if (!CCScene::get()->getChildByType<LeaderboardsLayer>(0)) return;

#define LEVEL_BROWSER_LAYER_RETURN\
	EARLY_RETURN("levelBrowserLayer")\
	if (!CCScene::get()->getChildByType<LevelBrowserLayer>(0) || CCScene::get()->getChildByType<LevelInfoLayer>(0) || CCScene::get()->getChildByType<LevelListLayer>(0)) return;

#define LEVEL_INFO_LAYER_RETURN\
	EARLY_RETURN("levelInfoLayer")\
	if (!CCScene::get()->getChildByType<LevelInfoLayer>(0) || CCScene::get()->getChildByType<LevelBrowserLayer>(0) || CCScene::get()->getChildByType<LevelListLayer>(0)) return;

#define LEVEL_LIST_LAYER_RETURN\
	EARLY_RETURN("levelListLayer")\
	if (!CCScene::get()->getChildByType<LevelListLayer>(0) || CCScene::get()->getChildByType<LevelBrowserLayer>(0) || CCScene::get()->getChildByType<LevelInfoLayer>(0) || !this->m_levelList || this->m_levelList->m_isEditable) return;\


using namespace geode::prelude;

#define SEARCHING_LEVELS_RETURN if (m_fields->isSearch) return;
#define IF_SEARCHING if (m_fields->isSearch) return
#define SAVED_LEVELS_RETURN if (m_fields->isSaved) return;
#define IF_SAVED if (m_fields->isSaved) return
#define MY_LEVELS_RETURN if (m_fields->isMine) return;
#define IF_MY if (m_fields->isMine) return

class $modify(MyLevelBrowserLayer, LevelBrowserLayer) {
	struct Fields {
		bool isMine = false;
		bool isSaved = false;
		bool isSearch = false;
	};
	DEFINE_KEYBIND
	bool init(GJSearchObject* searchObject) {
		if (!LevelBrowserLayer::init(searchObject) || this->m_isOverlay) return false;

		m_fields->isMine = this->getChildByID("new-level-menu");
		m_fields->isSaved = this->getChildByID("saved-menu");
		m_fields->isSearch = this->getChildByID("refresh-menu");

		this->defineKeybind("find", [this]() {
			SEARCHING_LEVELS_RETURN
			LEVEL_BROWSER_LAYER_RETURN
			PRESS("search-menu > search-button")
		});
		this->defineKeybind("refresh-page", [this]() {
			MY_LEVELS_RETURN
			SAVED_LEVELS_RETURN
			LEVEL_BROWSER_LAYER_RETURN
			LevelBrowserLayer::onRefresh(nullptr);
		});
		this->defineKeybind("toggle-level-lists", [this]() {
			SEARCHING_LEVELS_RETURN
			LEVEL_BROWSER_LAYER_RETURN
			IF_SAVED PRESS("saved-menu > switch-mode-button")
			IF_MY PRESS("new-level-menu > switch-mode-button")
		});
		this->defineKeybind("first-page", [this]() {
			LEVEL_BROWSER_LAYER_RETURN
			SetIDPopup* dummySetID = SetIDPopup::create(1, 1, 999999, "Go to Page", "Go", true, 1, 60, false, false);
			LevelBrowserLayer::setIDPopupClosed(dummySetID, 1);
		});
		this->defineKeybind("last-page", [this]() {
			LEVEL_BROWSER_LAYER_RETURN
			IF_SEARCHING PRESS("page-menu > cvolton.betterinfo/last-button")
			PRESS("page-menu > last-page-button")
		});
		this->defineKeybind("new-editor-level", [this]() {
			SEARCHING_LEVELS_RETURN
			SAVED_LEVELS_RETURN
			LEVEL_BROWSER_LAYER_RETURN
			PRESS("new-level-menu > new-level-button")
		});
		this->defineKeybind("view-uploaded", [this]() {
			SEARCHING_LEVELS_RETURN
			SAVED_LEVELS_RETURN
			LEVEL_BROWSER_LAYER_RETURN
			PRESS("my-levels-menu > my-levels-button")
		});
		this->defineKeybind("sort-by-size", [this]() {
			SEARCHING_LEVELS_RETURN
			LEVEL_BROWSER_LAYER_RETURN
			if (!Manager::getSharedInstance()->isLevelSize) return;
			PRESS("hiimjustin000.level_size/size-sort-menu > hiimjustin000.level_size/size-sort-toggler")
		});
		return true;
	}
};

#undef SEARCHING_LEVELS_RETURN
#undef IF_SEARCHING
#undef SAVED_LEVELS_RETURN
#undef IF_SAVED
#undef MY_LEVELS_RETURN
#undef IF_MY

class $modify(MyLevelInfoLayer, LevelInfoLayer) {
	DEFINE_KEYBIND
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelInfoLayer::init(p0, p1)) return false;
		this->defineKeybind("refresh-page", [this]() {
			LEVEL_INFO_LAYER_RETURN
			LevelInfoLayer::onUpdate(nullptr);
		});
		this->defineKeybind("comments", [this]() {
			LEVEL_INFO_LAYER_RETURN
			PRESS("right-side-menu > info-button")
		});
		this->defineKeybind("leaderboard", [this]() {
			LEVEL_INFO_LAYER_RETURN
			PRESS("right-side-menu > leaderboards-button")
		});
		this->defineKeybind("favorite", [this]() {
			LEVEL_INFO_LAYER_RETURN
			PRESS("other-menu > favorite-button")
		});
		this->defineKeybind("add-to-list", [this]() {
			LEVEL_INFO_LAYER_RETURN
			LevelInfoLayer::onAddToList(nullptr);
		});
		this->defineKeybind("add-to-folder", [this]() {
			LEVEL_INFO_LAYER_RETURN
			LevelInfoLayer::onSetFolder(nullptr);
		});
		this->defineKeybind("clone", [this]() {
			LEVEL_INFO_LAYER_RETURN
			PRESS("left-side-menu > copy-button")
		});
		this->defineKeybind("info", [this]() {
			LEVEL_INFO_LAYER_RETURN
			LevelInfoLayer::onLevelInfo(nullptr);
		});
		this->defineKeybind("level-settings", [this]() {
			LEVEL_INFO_LAYER_RETURN
			PRESS("settings-menu > settings-button")
		});
		return true;
	}
};

class $modify(MyLevelListLayer, LevelListLayer) {
	DEFINE_KEYBIND
	bool init(GJLevelList* list) {
		if (!LevelListLayer::init(list)) return false;
		this->defineKeybind("refresh-page", [this]() {
			LEVEL_LIST_LAYER_RETURN
			PRESS("right-side-menu > refresh-button")
		});
		this->defineKeybind("comments", [this]() {
			LEVEL_LIST_LAYER_RETURN
			PRESS("right-side-menu > info-button")
		});
		this->defineKeybind("favorite", [this]() {
			LEVEL_LIST_LAYER_RETURN
			PRESS("right-side-menu > favorite-button")
		});
		this->defineKeybind("clone", [this]() {
			LEVEL_LIST_LAYER_RETURN
			PRESS("right-side-menu > copy-button")
		});
		this->defineKeybind("info", [this]() {
			LEVEL_LIST_LAYER_RETURN
			PRESS("button-menu > small-info-button")
		});
		return true;
	}
};

class $modify(MyLeaderboardsLayer, LeaderboardsLayer) {
	DEFINE_KEYBIND
	bool init(LeaderboardType type, LeaderboardStat stat) {
		if (!LeaderboardsLayer::init(type, stat)) return false;
		this->defineKeybind("refresh-page", [this]() {
			LEADERBOARDS_LAYER_RETURN
			BETTERINFO_RETURN
			PRESS("bottom-right-menu > cvolton.betterinfo/refresh-button")
		});
		this->defineKeybind("lb-top-100", [this]() {
			LEADERBOARDS_LAYER_RETURN
			FIRST_BUTTON_IN("top-100-menu")
		});
		this->defineKeybind("lb-friends", [this]() {
			LEADERBOARDS_LAYER_RETURN
			FIRST_BUTTON_IN("friends-menu")
		});
		this->defineKeybind("lb-global", [this]() {
			LEADERBOARDS_LAYER_RETURN
			FIRST_BUTTON_IN("global-menu")
		});
		this->defineKeybind("lb-creators", [this]() {
			LEADERBOARDS_LAYER_RETURN
			FIRST_BUTTON_IN("creators-menu")
		});
		return true;
	}
};

#define PRESS_FROM_MAIN_LAYER(query) Utils::activateButtonSafe(query, this->m_mainLayer);
#define PROFILEPAGE_RETURN\
	RETURN_IF_DISABLED("profilePage")\
	if (GJBaseGameLayer::get() || Manager::getSharedInstance()->profilePages.top() && Manager::getSharedInstance()->profilePages.top() != this) { return; }

class $modify(MyProfilePage, ProfilePage) {
	struct Fields {
		~Fields() {
			if (!Manager::getSharedInstance()->profilePages.empty()) { Manager::getSharedInstance()->profilePages.pop(); }
		}
	};
	DEFINE_KEYBIND
	bool init(int profile, bool ownProfile) {
		if (!ProfilePage::init(profile, ownProfile)) return false;
		Manager::getSharedInstance()->profilePages.push(this);
		this->defineKeybind("refresh-page", [this]() {
			PROFILEPAGE_RETURN
			PRESS_FROM_MAIN_LAYER("main-menu > refresh-button")
		});
		this->defineKeybind("previous-page", [this]() {
			PROFILEPAGE_RETURN
			PRESS_FROM_MAIN_LAYER("main-menu > prev-page-button")
		});
		this->defineKeybind("next-page", [this]() {
			PROFILEPAGE_RETURN
			PRESS_FROM_MAIN_LAYER("main-menu > next-page-button")
		});
		this->defineKeybind("comments", [this]() {
			PROFILEPAGE_RETURN
			PRESS_FROM_MAIN_LAYER("main-menu > comment-history-button")
		});
		this->defineKeybind("follow-user", [this]() {
			PROFILEPAGE_RETURN
			PRESS_FROM_MAIN_LAYER("main-menu > follow-button")
		});
		this->defineKeybind("message-user", [this]() {
			PROFILEPAGE_RETURN
			PRESS_FROM_MAIN_LAYER("bottom-menu > message-button")
		});
		this->defineKeybind("friend-user", [this]() {
			PROFILEPAGE_RETURN
			PRESS_FROM_MAIN_LAYER("bottom-menu > friend-button")
		});
		this->defineKeybind("block-user", [this]() {
			PROFILEPAGE_RETURN
			PRESS_FROM_MAIN_LAYER("bottom-menu > block-button")
		});
		return true;
	}
};

#define PRESS_FROM_CCSCENE(query) Utils::activateButtonSafe(query, CCScene::get());
#define PRESS_CVOLTON(node) PRESS_FROM_CCSCENE("cvolton.betterinfo/JumpToPageLayer > cvolton.betterinfo/main-layer > cvolton.betterinfo/button-menu > " node)
#define INFOLAYER_RETURN\
	RETURN_IF_DISABLED("infoLayer")\
	if (GJBaseGameLayer::get() || Manager::getSharedInstance()->infoLayers.top() && Manager::getSharedInstance()->infoLayers.top() != this) return;

class $modify(MyInfoLayer, InfoLayer) {
	struct Fields {
		~Fields() {
			if (!Manager::getSharedInstance()->infoLayers.empty()) { Manager::getSharedInstance()->infoLayers.pop(); }
		}
	};
	DEFINE_KEYBIND
	bool init(GJGameLevel* level, GJUserScore* profile, GJLevelList* list) {
		if (!InfoLayer::init(level, profile, list)) return false;
		Manager::getSharedInstance()->infoLayers.push(this);
		this->defineKeybind("refresh-page", [this]() {
			INFOLAYER_RETURN
			PRESS_FROM_MAIN_LAYER("refresh-menu > refresh-button")
		});
		this->defineKeybind("previous-page", [this]() {
			INFOLAYER_RETURN
			PRESS_FROM_MAIN_LAYER("switch-page-menu > prev-page-button")
		});
		this->defineKeybind("next-page", [this]() {
			INFOLAYER_RETURN
			PRESS_FROM_MAIN_LAYER("switch-page-menu > next-page-button")
		});
		this->defineKeybind("infolayer-sort-likes", [this]() {
			INFOLAYER_RETURN
			PRESS_FROM_MAIN_LAYER("left-side-menu > sort-likes-button")
		});
		this->defineKeybind("infolayer-sort-recent", [this]() {
			INFOLAYER_RETURN
			PRESS_FROM_MAIN_LAYER("left-side-menu > sort-recent-button")
		});
		this->defineKeybind("infolayer-extend", [this]() {
			if (m_mode == CommentKeyType::User) return;
			INFOLAYER_RETURN
			PRESS_FROM_MAIN_LAYER("left-side-menu > extend-button")
		});
		this->defineKeybind("infolayer-small-mode", [this]() {
			INFOLAYER_RETURN
			PRESS_FROM_MAIN_LAYER("left-side-menu > small-mode-button")
		});
		this->defineKeybind("first-page", [this]() {
			INFOLAYER_RETURN
			BETTERINFO_RETURN
			PRESS_FROM_MAIN_LAYER("refresh-menu > cvolton.betterinfo/comment-page-btn")
			PRESS_CVOLTON("cvolton.betterinfo/reset-button")
			PRESS_CVOLTON("cvolton.betterinfo/go-button")
		});
		this->defineKeybind("last-page", [this]() {
			INFOLAYER_RETURN
			BETTERINFO_RETURN
			PRESS_FROM_MAIN_LAYER("refresh-menu > cvolton.betterinfo/comment-page-btn")
			PRESS_CVOLTON("cvolton.betterinfo/last-button")
		});
		return true;
	}
};