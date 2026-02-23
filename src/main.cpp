#include <Geode/ui/GeodeUI.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define SCENE_HAS CCScene::get()->getChildByID

using namespace geode::prelude;

$on_mod(Loaded) {
	listenForKeybindSettingPresses("open-settings", [](Keybind const& keybind, bool down, bool repeat, double timestamp) {
        if (!Utils::modEnabled() || !down || repeat || GJBaseGameLayer::get()) return ListenerResult::Propagate;
		geode::openSettingsPopup(Mod::get());
    });
	listenForKeybindSettingPresses("geode-mods-list", [](Keybind const& keybind, bool down, bool repeat, double timestamp) {
		if (!Utils::modEnabled() || !down || repeat || SCENE_HAS("ModsLayer") || SCENE_HAS("ModsLayerWrapper")) return ListenerResult::Propagate;
		GJBaseGameLayer* gjbgl = GJBaseGameLayer::get();
		CCNode* jasminesGeodeButton = nullptr;
		if (Manager::getSharedInstance()->isGeodeInPauseMenu) {
			if (gjbgl) {
				if (const auto pauseLayer = gjbgl->getParent()->getChildByType<PauseLayer>(0)) {
					jasminesGeodeButton = pauseLayer->querySelector("right-button-menu > hiimjustin000.geode_in_pause_menu/geode-button");
				} else if (const auto editorPauseLayer = gjbgl->getChildByType<EditorPauseLayer>(0)) {
					jasminesGeodeButton = editorPauseLayer->querySelector("guidelines-menu > hiimjustin000.geode_in_pause_menu/geode-button");
				}
			} else if (const auto levelInfoLayer = CCScene::get()->getChildByType<LevelInfoLayer>(0)) {
				jasminesGeodeButton = levelInfoLayer->querySelector("left-side-menu > hiimjustin000.geode_in_pause_menu/geode-button");
			} else if (const auto editLevelLayer = CCScene::get()->getChildByType<EditLevelLayer>(0)) {
				jasminesGeodeButton = editLevelLayer->querySelector("level-actions-menu > hiimjustin000.geode_in_pause_menu/geode-button");
 			}
		}
		if (const auto jgb = typeinfo_cast<CCMenuItemSpriteExtra*>(jasminesGeodeButton); jgb) {
			jgb->activate(); // apparently it NEEDs to be typeinfo cast or else crash
		} else if (!gjbgl) {
			geode::openModsList();
		}
		return ListenerResult::Propagate;
	});
	listenForKeybindSettingPresses("open-settings", [](Keybind const& keybind, bool down, bool repeat, double timestamp) {
		if (!Utils::modEnabled() || !down || repeat || GJBaseGameLayer::get()) return ListenerResult::Propagate;
		OptionsLayer::create()->onOptions(nullptr);
		return ListenerResult::Propagate;
	});

	Mod::get()->setLoggingEnabled(Utils::getBool("logging"));
	listenForSettingChanges<bool>("logging", [](bool logging){
		Mod::get()->setLoggingEnabled(logging);
	});
}