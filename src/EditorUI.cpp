#include <Geode/modify/EditorUI.hpp>
#include "Utils.hpp"

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

#define CREATE_EDITOR_PAUSE_LAYER\
	const bool noEPLBeforeFaking = !this->getParent()->getChildByType<EditorPauseLayer>(0);\
	if (noEPLBeforeFaking) this->onPause(nullptr);\
	const auto epl = this->getParent()->getChildByType<EditorPauseLayer>(0);\
	if (!epl) return;\
	if (noEPLBeforeFaking) epl->setVisible(false);

#define RETURN_IF_NOT_ACTIVE if (!LevelEditorLayer::get() || LevelEditorLayer::get()->getChildByType<FLAlertLayer>(0) || this->getChildByType<FLAlertLayer>(0) || CCScene::get()->getChildByType<FLAlertLayer>(0)) return;
#define RETURN_IF_DISABLED if (!Utils::modEnabled() || !Utils::getBool("levelEditor") || m_editorLayer->m_playbackMode != PlaybackMode::Not) return;
#define EARLY_RETURN\
	RETURN_IF_DISABLED\
	RETURN_IF_NOT_ACTIVE

using namespace geode::prelude;

class $modify(MyEditorUI, EditorUI) {
	DEFINE_KEYBIND
	bool init(LevelEditorLayer* p0) {
		if (!EditorUI::init(p0)) return false;
		this->defineKeybind("save-editor-level", [this]() {
			EARLY_RETURN
			CREATE_EDITOR_PAUSE_LAYER
			epl->saveLevel();
			if (noEPLBeforeFaking) epl->keyBackClicked();
			return FLAlertLayer::create(
				"Editor Level Saved",
				"Your <cj>level</c> has been <cg>saved</c>.",
				"OK"
			)->show();
		});
		this->defineKeybind("save-and-play-editor", [this]() {
			EARLY_RETURN
			// simulate all the button clicks! because robtop is such a genius programmer :D
			CREATE_EDITOR_PAUSE_LAYER
			CCNode* saveAndPlay = epl->querySelector("resume-menu > save-and-play-button");
			if (const auto sap = typeinfo_cast<CCMenuItemSpriteExtra*>(saveAndPlay)) return sap->activate();
		});
		this->defineKeybind("save-and-exit-editor", [this]() {
			EARLY_RETURN
			CREATE_EDITOR_PAUSE_LAYER
			return epl->onSaveAndExit(nullptr);
		});
		this->defineKeybind("exit-editor", [this]() {
			EARLY_RETURN
			CREATE_EDITOR_PAUSE_LAYER
			if (CCScene::get()->getChildByType<FLAlertLayer>(0)) return;
			CCNode* exitButton = epl->querySelector("resume-menu > exit-button");
			if (!exitButton) return;

			epl->onExitNoSave(exitButton);

			const auto alert = CCScene::get()->getChildByType<FLAlertLayer>(0);
			if (alert->getTag() != 1) return;
			if (const auto yesButton = typeinfo_cast<CCMenuItemSpriteExtra*>(alert->m_button2->getParent())) return yesButton->activate();
		});
		return true;
	}
};