#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/modify/EditorUI.hpp>
#include "Utils.hpp"

#define EDITOR_PAUSE_LAYER_CREATED EditorPauseLayer* epl = EditorPauseLayer::create(this->m_editorLayer)

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyEditorUI, EditorUI) {
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) callback();
			return ListenerResult::Propagate;
		}, id);
	}
	bool init(LevelEditorLayer* p0) {
		if (!EditorUI::init(p0)) return false;
		this->defineKeybind("save-editor-level"_spr, [this]() {
			if (!Utils::modEnabled() || !Utils::getBool("levelEditor")) return;
			if (EDITOR_PAUSE_LAYER_CREATED) {
				epl->saveLevel();
				epl->keyBackClicked();
				return FLAlertLayer::create(
					"Editor Level Saved",
					"Your <cj>level</c> has been <cg>saved</c>.",
					"OK"
				)->show();
			}
		});
		this->defineKeybind("save-and-play-editor"_spr, [this]() {
			if (!Utils::modEnabled() || !Utils::getBool("levelEditor")) return;
			// simulate all the button clicks! because robtop is such a genius programmer :D
			const bool noEPLBeforeFaking = !this->getParent()->getChildByType<EditorPauseLayer>(0);
			if (noEPLBeforeFaking) this->onPause(nullptr);

			const auto epl = this->getParent()->getChildByType<EditorPauseLayer>(0);
			if (!epl) return;

			if (noEPLBeforeFaking) epl->setVisible(false); // illusions! yay :D
			CCNode* saveAndPlay = epl->querySelector("resume-menu > save-and-play-button");
			if (const auto sap = typeinfo_cast<CCMenuItemSpriteExtra*>(saveAndPlay)) return sap->activate();
		});
		this->defineKeybind("save-and-exit-editor"_spr, [this]() {
			if (!Utils::modEnabled() || !Utils::getBool("levelEditor")) return;
			if (EDITOR_PAUSE_LAYER_CREATED) return epl->onSaveAndExit(nullptr);
		});
		this->defineKeybind("exit-editor"_spr, [this]() {
			if (!Utils::modEnabled() || !Utils::getBool("levelEditor")) return;
			const bool noEPLBeforeFaking = !this->getParent()->getChildByType<EditorPauseLayer>(0);
			if (noEPLBeforeFaking) this->onPause(nullptr);

			const auto epl = this->getParent()->getChildByType<EditorPauseLayer>(0);
			if (!epl || CCScene::get()->getChildByType<FLAlertLayer>(0)) return;

			if (noEPLBeforeFaking) epl->setVisible(false); // illusions! yay :D
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