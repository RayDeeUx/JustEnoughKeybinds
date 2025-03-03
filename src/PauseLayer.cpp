#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include "Utils.hpp"

#define EARLY_RETURN if (!Utils::modEnabled() || !Utils::getBool("pauseLayer") || CCScene::get()->getChildByType<FLAlertLayer>(0)) return;

using namespace geode::prelude;
using namespace keybinds;

class $modify(MyPauseLayer, PauseLayer) {
	void defineKeybind(const char* id, std::function<void()> callback) {
		this->addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
			if (event->isDown()) callback();
			return ListenerResult::Propagate;
		}, id);
	}
	void customSetup() {
		PauseLayer::customSetup();
		this->defineKeybind("restart-level-pause"_spr, [this]() {
			EARLY_RETURN
			PauseLayer::onRestart(nullptr);
		});
		this->defineKeybind("full-restart-level-pause"_spr, [this]() {
			EARLY_RETURN
			PauseLayer::onRestartFull(nullptr);
		});
		this->defineKeybind("editor-level-pause"_spr, [this]() {
			EARLY_RETURN
			const auto editorButton = this->querySelector("center-button-menu > edit-button");
			if (!editorButton) return;
			if (const auto editor = typeinfo_cast<CCMenuItemSpriteExtra*>(editorButton)) editor->activate();
		});
	}
};