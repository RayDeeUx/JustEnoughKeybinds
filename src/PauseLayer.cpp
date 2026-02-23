#include <Geode/modify/PauseLayer.hpp>
#include "Utils.hpp"

#define EARLY_RETURN if (!Utils::modEnabled() || !Utils::getBool("pauseLayer") || CCScene::get()->getChildByType<FLAlertLayer>(0)) return;

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {
	void defineKeybind(std::string id, std::function<void()> callback) {
		this->addEventListener(
            KeybindSettingPressedEventV3(Mod::get(), id),
            [this, callback](Keybind const& keybind, bool down, bool repeat, double timestamp) {
				if (!down || repeat) return;
				callback();
            }
        );
	}
	void customSetup() {
		PauseLayer::customSetup();
		this->defineKeybind("restart-level-pause", [this]() {
			EARLY_RETURN
			PauseLayer::onRestart(nullptr);
		});
		this->defineKeybind("full-restart-level-pause", [this]() {
			EARLY_RETURN
			PauseLayer::onRestartFull(nullptr);
		});
		this->defineKeybind("editor-level-pause", [this]() {
			EARLY_RETURN
			const auto editorButton = this->querySelector("center-button-menu > edit-button");
			if (!editorButton) return;
			if (const auto editor = typeinfo_cast<CCMenuItemSpriteExtra*>(editorButton)) editor->activate();
		});
	}
};