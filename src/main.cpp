#include <Geode/ui/GeodeUI.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define SCENE_HAS CCScene::get()->getChildByID

using namespace geode::prelude;

$on_mod(Loaded) {
	/* ————————————————————————— GLOBAL KEYBINDS ————————————————————————— */ // DONE
	binds->registerBindable({
		"open-settings"_spr,
		"JustEnoughKeybinds Settings",
		"Open the settings menu for JustEnoughKeybinds.",
		{ Keybind::create(KEY_E, Modifier::Shift | ALT_CTRL | CTRL_CMD) },
		"JustEnoughKeybinds/Misc. Navigation", false
	});
	binds->registerBindable({
		"geode-mods-list"_spr,
		"Geode Mods List",
		"Open the Geode mods list.",
		{ Keybind::create(KEY_G, Modifier::Shift | ALT_CTRL | CTRL_CMD) },
		"JustEnoughKeybinds/Misc. Navigation", false
	});
	// binds->registerBindable({
	// 	"custom-keybinds"_spr,
	// 	"Custom Keybinds",
	// 	"Open your custom keybinds.",
	// 	{ Keybind::create(KEY_K, Modifier::Shift | ALT_CTRL | CTRL_CMD) },
	// 	"JustEnoughKeybinds/Misc. Navigation", false
	// });
	
	new EventListener([=](InvokeBindEvent* event) {
		if (GJBaseGameLayer::get() || !event->isDown() || !Utils::modEnabled()) return ListenerResult::Propagate;
		geode::openSettingsPopup(Mod::get());
		return ListenerResult::Propagate;
	}, InvokeBindFilter(nullptr, "open-settings"_spr));
	new EventListener([=](InvokeBindEvent* event) {
		if (SCENE_HAS("ModsLayer") || SCENE_HAS("ModsLayerWrapper") || !event->isDown() || !Utils::modEnabled()) return ListenerResult::Propagate;
		if (GJBaseGameLayer* gjbgl = GJBaseGameLayer::get(); !gjbgl) geode::openModsList();
		else if (Manager::getSharedInstance()->isGeodeInPauseMenu) {
			CCNode* jasminesGeodeButton = nullptr;
			if (const auto pauseLayer = gjbgl->getParent()->getChildByType<PauseLayer>(0))
				jasminesGeodeButton = pauseLayer->querySelector("right-button-menu > hiimjustin000.geode_in_pause_menu/geode-button");
			else if (const auto editorPauseLayer = gjbgl->getChildByType<EditorPauseLayer>(0))
				jasminesGeodeButton = editorPauseLayer->querySelector("guidelines-menu > hiimjustin000.geode_in_pause_menu/geode-button");
			if (const auto jgb = typeinfo_cast<CCMenuItemSpriteExtra*>(jasminesGeodeButton); jgb) jgb->activate(); // apparently it NEEDs to be typeinfo cast or else crash
			return ListenerResult::Propagate;
		}
		return ListenerResult::Propagate;
	}, InvokeBindFilter(nullptr, "geode-mods-list"_spr));
	// new EventListener([=](InvokeBindEvent* event) {
	// 	if (GJBaseGameLayer::get() || !event->isDown() || !Utils::modEnabled()) return ListenerResult::Propagate;
	// 	MoreOptionsLayer::create()->onKeybindings(nullptr); // normally this would just open the vanilla keybinds menu. however since customkeybinds is a required dependency it'll open the one from customkeybinds instead. win-win!
	// 	return ListenerResult::Propagate;
	// }, InvokeBindFilter(nullptr, "custom-keybinds"_spr));
	new EventListener([=](InvokeBindEvent* event) {
		if (GJBaseGameLayer::get() || !event->isDown() || !Utils::modEnabled()) return ListenerResult::Propagate;
		OptionsLayer::create()->onOptions(nullptr);
		return ListenerResult::Propagate;
	}, InvokeBindFilter(nullptr, "more-options-layer"_spr));

	Mod::get()->setLoggingEnabled(Utils::getBool("logging"));
	listenForSettingChanges<bool>("logging", [](bool logging){
		Mod::get()->setLoggingEnabled(logging);
	});
}