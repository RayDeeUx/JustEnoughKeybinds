#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/modify/LevelListLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/InfoLayer.hpp>
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

#define BETTERINFO_RETURN if (!Utils::isModLoaded(BETTERINFO)) INSTALL_BETTERINFO_YOU_BLOCKHEAD

#define PRESS(query) Utils::activateButtonSafe(query, this);
#define FIRST_BUTTON_IN(query) Utils::pressFirstButtonInMenu(query, this);
#define RETURN_IF_DISABLED(setting) if (!Utils::modEnabled() || !Utils::getBool(setting)) return;
#define RETURN_IF_NOT_ACTIVE if (CCScene::get()->getChildByType<FLAlertLayer>(0)) return;
#define EARLY_RETURN(setting)\
	RETURN_IF_DISABLED(setting)\
	RETURN_IF_NOT_ACTIVE

#define LEVEL_BROWSER_LAYER_RETURN EARLY_RETURN("levelBrowserLayer")
#define LEADERBOARDS_LAYER_RETURN EARLY_RETURN("leaderboardsLayer")
#define LEVEL_INFO_LAYER_RETURN EARLY_RETURN("levelInfoLayer")
#define LEVEL_LIST_LAYER_RETURN EARLY_RETURN("levelListLayer")

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
		if (!LevelBrowserLayer::init(searchObject)) return false;

		m_fields->isMine = this->getChildByID("new-level-menu");
		m_fields->isSaved = this->getChildByID("saved-menu");
		m_fields->isSearch = this->getChildByID("refresh-menu");

		this->defineKeybind("find"_spr, [this]() {
			SEARCHING_LEVELS_RETURN
			LEVEL_BROWSER_LAYER_RETURN
			PRESS("search-menu > search-button")
		});
		this->defineKeybind("refresh-page"_spr, [this]() {
			MY_LEVELS_RETURN
			SAVED_LEVELS_RETURN
			LEVEL_BROWSER_LAYER_RETURN
			LevelBrowserLayer::onRefresh(nullptr);
		});
		this->defineKeybind("toggle-level-lists"_spr, [this]() {
			SEARCHING_LEVELS_RETURN
			LEVEL_BROWSER_LAYER_RETURN
			IF_SAVED PRESS("saved-menu > switch-mode-button")
			IF_MY PRESS("new-level-menu > switch-mode-button")
		});
		this->defineKeybind("first-page"_spr, [this]() {
			LEVEL_BROWSER_LAYER_RETURN
			SetIDPopup* dummySetID = SetIDPopup::create(1, 1, 999999, "Go to Page", "Go", true, 1, 60, false, false);
			LevelBrowserLayer::setIDPopupClosed(dummySetID, 1);
		});
		this->defineKeybind("last-page"_spr, [this]() {
			LEVEL_BROWSER_LAYER_RETURN
			IF_SEARCHING PRESS("page-menu > cvolton.betterinfo/last-button")
			PRESS("page-menu > last-page-button")
		});
		this->defineKeybind("new-editor-level"_spr, [this]() {
			SEARCHING_LEVELS_RETURN
			SAVED_LEVELS_RETURN
			LEVEL_BROWSER_LAYER_RETURN
			PRESS("new-level-menu > new-level-button")
		});
		this->defineKeybind("view-uploaded"_spr, [this]() {
			SEARCHING_LEVELS_RETURN
			SAVED_LEVELS_RETURN
			LEVEL_BROWSER_LAYER_RETURN
			PRESS("my-levels-menu > my-levels-button")
		});
		this->defineKeybind("sort-by-size"_spr, [this]() {
			SEARCHING_LEVELS_RETURN
			LEVEL_BROWSER_LAYER_RETURN
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
		this->defineKeybind("refresh-page"_spr, [this]() {
			LEVEL_INFO_LAYER_RETURN
			LevelInfoLayer::onUpdate(nullptr);
		});
		this->defineKeybind("comments"_spr, [this]() {
			LEVEL_INFO_LAYER_RETURN
			PRESS("right-side-menu > info-button")
		});
		this->defineKeybind("leaderboard"_spr, [this]() {
			LEVEL_INFO_LAYER_RETURN
			PRESS("right-side-menu > leaderboards-button")
		});
		this->defineKeybind("favorite"_spr, [this]() {
			LEVEL_INFO_LAYER_RETURN
			PRESS("other-menu > favorite-button")
		});
		this->defineKeybind("add-to-list"_spr, [this]() {
			LEVEL_INFO_LAYER_RETURN
			LevelInfoLayer::onAddToList(nullptr);
		});
		this->defineKeybind("add-to-folder"_spr, [this]() {
			LEVEL_INFO_LAYER_RETURN
			LevelInfoLayer::onSetFolder(nullptr);
		});
		this->defineKeybind("clone"_spr, [this]() {
			LEVEL_INFO_LAYER_RETURN
			PRESS("left-side-menu > copy-button")
		});
		this->defineKeybind("info"_spr, [this]() {
			LEVEL_INFO_LAYER_RETURN
			LevelInfoLayer::onLevelInfo(nullptr);
		});
		this->defineKeybind("settings"_spr, [this]() {
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
		this->defineKeybind("refresh-page"_spr, [this]() {
			LEVEL_LIST_LAYER_RETURN
			PRESS("right-side-menu > refresh-button")
		});
		this->defineKeybind("comments"_spr, [this]() {
			LEVEL_LIST_LAYER_RETURN
			PRESS("right-side-menu > info-button")
		});
		this->defineKeybind("favorite"_spr, [this]() {
			LEVEL_LIST_LAYER_RETURN
			PRESS("right-side-menu > favorite-button")
		});
		this->defineKeybind("clone"_spr, [this]() {
			LEVEL_LIST_LAYER_RETURN
			PRESS("right-side-menu > copy-button")
		});
		this->defineKeybind("info"_spr, [this]() {
			LEVEL_LIST_LAYER_RETURN
			PRESS("button-menu > small-info-button")
		});
		return true;
	}
};

class $modify(MyLeaderboardsLayer, LeaderboardsLayer) {
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) callback();
			return ListenerResult::Propagate;
		}, id);
	}
	bool init(LeaderboardState leaderboardState) {
		if (!LeaderboardsLayer::init(leaderboardState)) return false;
		this->defineKeybind("refresh-page"_spr, [this]() {
			LEADERBOARDS_LAYER_RETURN
			BETTERINFO_RETURN
			PRESS("bottom-right-menu > cvolton.betterinfo/refresh-button")
		});
		this->defineKeybind("lb-top-100"_spr, [this]() {
			LEADERBOARDS_LAYER_RETURN
			FIRST_BUTTON_IN("top-100-menu")
		});
		this->defineKeybind("lb-friends"_spr, [this]() {
			LEADERBOARDS_LAYER_RETURN
			FIRST_BUTTON_IN("friends-menu")
		});
		this->defineKeybind("lb-global"_spr, [this]() {
			LEADERBOARDS_LAYER_RETURN
			FIRST_BUTTON_IN("global-menu")
		});
		this->defineKeybind("lb-creators"_spr, [this]() {
			LEADERBOARDS_LAYER_RETURN
			FIRST_BUTTON_IN("creators-menu")
		});
		return true;
	}
};

#define PRESS_FROM_MAIN_LAYER(query) Utils::activateButtonSafe(query, this->m_mainLayer);
#define PROFILEPAGE_UNFOCUSED_RETURN if (this->getChildByID("InfoLayer") || CCScene::get()->getChildByType<FLAlertLayer>(1)) return;
#define PROFILEPAGE_RETURN\
	RETURN_IF_DISABLED("profilePage")\
	if (Utils::getBool("checkUnfocused")) { PROFILEPAGE_UNFOCUSED_RETURN } else if (CCScene::get()->getChildByID("FLAlertLayer")) { return; }

class $modify(MyProfilePage, ProfilePage) {
	DEFINE_KEYBIND
	bool init(int profile, bool ownProfile) {
		if (!ProfilePage::init(profile, ownProfile)) return false;
		this->defineKeybind("refresh-page"_spr, [this]() {
			PROFILEPAGE_RETURN
			PRESS_FROM_MAIN_LAYER("main-menu > refresh-button")
		});
		this->defineKeybind("previous-page"_spr, [this]() {
			PROFILEPAGE_RETURN
			PRESS_FROM_MAIN_LAYER("main-menu > prev-page-button")
		});
		this->defineKeybind("next-page"_spr, [this]() {
			PROFILEPAGE_RETURN
			PRESS_FROM_MAIN_LAYER("main-menu > next-page-button")
		});
		this->defineKeybind("comments"_spr, [this]() {
			PROFILEPAGE_RETURN
			PRESS_FROM_MAIN_LAYER("main-menu > comment-history-button")
		});
		this->defineKeybind("follow-user"_spr, [this]() {
			PROFILEPAGE_RETURN
			PRESS_FROM_MAIN_LAYER("main-menu > follow-button")
		});
		this->defineKeybind("message-user"_spr, [this]() {
			PROFILEPAGE_RETURN
			PRESS_FROM_MAIN_LAYER("bottom-menu > message-button")
		});
		this->defineKeybind("friend-user"_spr, [this]() {
			PROFILEPAGE_RETURN
			PRESS_FROM_MAIN_LAYER("bottom-menu > friend-button")
		});
		this->defineKeybind("block-user"_spr, [this]() {
			PROFILEPAGE_RETURN
			PRESS_FROM_MAIN_LAYER("bottom-menu > block-button")
		});
		return true;
	}
};

#define PRESS_FROM_CCSCENE(query) Utils::activateButtonSafe(query, CCScene::get());
#define PRESS_CVOLTON(node) PRESS_FROM_CCSCENE("cvolton.betterinfo/JumpToPageLayer > cvolton.betterinfo/main-layer > cvolton.betterinfo/button-menu > " node)
#define INFOLAYER_UNFOCUSED_RETURN if (!CCScene::get()->getChildByID("ProfilePage") && CCScene::get()->getChildByType<FLAlertLayer>(1)) return;
#define INFOLAYER_RETURN\
	RETURN_IF_DISABLED("infoLayer")\
	if (Utils::getBool("checkUnfocused")) { INFOLAYER_UNFOCUSED_RETURN } else if (CCScene::get()->getChildByID("FLAlertLayer")) { return; }

class $modify(MyInfoLayer, InfoLayer) {
	DEFINE_KEYBIND
	bool init(GJGameLevel* level, GJUserScore* profile, GJLevelList* list) {
		if (!InfoLayer::init(level, profile, list)) return false;
		this->defineKeybind("refresh-page"_spr, [this]() {
			INFOLAYER_RETURN
			PRESS_FROM_MAIN_LAYER("refresh-menu > refresh-button")
		});
		this->defineKeybind("previous-page"_spr, [this]() {
			INFOLAYER_RETURN
			PRESS_FROM_MAIN_LAYER("switch-page-menu > prev-page-button")
		});
		this->defineKeybind("next-page"_spr, [this]() {
			INFOLAYER_RETURN
			PRESS_FROM_MAIN_LAYER("switch-page-menu > next-page-button")
		});
		this->defineKeybind("infolayer-sort-likes"_spr, [this]() {
			INFOLAYER_RETURN
			PRESS_FROM_MAIN_LAYER("left-side-menu > sort-likes-button")
		});
		this->defineKeybind("infolayer-sort-recent"_spr, [this]() {
			INFOLAYER_RETURN
			PRESS_FROM_MAIN_LAYER("left-side-menu > sort-recent-button")
		});
		this->defineKeybind("infolayer-extend"_spr, [this]() {
			if (m_mode == CommentKeyType::User) return;
			INFOLAYER_RETURN
			PRESS_FROM_MAIN_LAYER("left-side-menu > extend-button")
		});
		this->defineKeybind("infolayer-small-mode"_spr, [this]() {
			INFOLAYER_RETURN
			PRESS_FROM_MAIN_LAYER("left-side-menu > small-mode-button")
		});
		this->defineKeybind("first-page"_spr, [this]() {
			INFOLAYER_RETURN
			BETTERINFO_RETURN
			PRESS_FROM_MAIN_LAYER("refresh-menu > cvolton.betterinfo/comment-page-btn")
			PRESS_CVOLTON("cvolton.betterinfo/reset-button")
			PRESS_CVOLTON("cvolton.betterinfo/go-button")
		});
		this->defineKeybind("last-page"_spr, [this]() {
			INFOLAYER_RETURN
			BETTERINFO_RETURN
			PRESS_FROM_MAIN_LAYER("refresh-menu > cvolton.betterinfo/comment-page-btn")
			PRESS_CVOLTON("cvolton.betterinfo/last-button")
		});
		return true;
	}
};