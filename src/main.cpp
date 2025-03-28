#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

#define SCENE_HAS CCScene::get()->getChildByID

// WINDOWS-ORIGINAL_MAC-REPLACEMENT
// alt key crashes macos
#ifdef GEODE_IS_MACOS
#define CTRL_CMD Modifier::Command
#define ALT_CTRL Modifier::Control
#define MINUS KEY_Subtract
#else
#define CTRL_CMD Modifier::Control
#define ALT_CTRL Modifier::Alt
#define MINUS KEY_OEMMinus
#endif

using namespace geode::prelude;
using namespace keybinds;

$on_mod(Loaded) {
	const auto binds = BindManager::get();
	/* ————————————————————————— LEVEL EDITOR KEYBINDS ————————————————————————— */ // DONE
	binds->registerBindable({
		"save-editor-level"_spr,
		"Save Editing Level",
		"Saves editing your level <cy>without a confirmation</c>.",
		{ Keybind::create(KEY_S, CTRL_CMD) },
		"Editor/JustEnoughKeybinds", false
	});
	binds->registerBindable({
		"save-and-play-editor"_spr,
		"Save and Play Editor Level",
		"Saves and playtests the level in the editor <cy>without a confirmation</c>.",
		{ Keybind::create(KEY_S, Modifier::Shift | ALT_CTRL | CTRL_CMD) },
		"Editor/JustEnoughKeybinds", false
	});
	binds->registerBindable({
		"save-and-exit-editor"_spr,
		"Save and Exit Editor Level",
		"Saves and exits the level in the editor <cy>without a confirmation</c>.",
		{ Keybind::create(KEY_S, Modifier::Shift | CTRL_CMD) },
		"Editor/JustEnoughKeybinds", false
	});
	binds->registerBindable({
		"exit-editor"_spr,
		"Exit Editor",
		"Exit editing a level <cy>without saving</c>.",
		{ Keybind::create(KEY_Two, Modifier::Shift) },
		"Editor/JustEnoughKeybinds", false
	});
	/* ————————————————————————— PAUSELAYER KEYBINDS ————————————————————————— */ // DONE
	binds->registerBindable({
		"restart-level-pause"_spr,
		"Restart Level From Pause",
		"Restart the level from the pause menu.",
		{ Keybind::create(KEY_R) },
		"Play/Pause", false
	});
	binds->registerBindable({
		"full-restart-level-pause"_spr,
		"Full Restart Level From Pause",
		"Restart the level from the pause menu.",
		{ Keybind::create(KEY_R, CTRL_CMD) },
		"Play/Pause", false
	});
	binds->registerBindable({
		"editor-level-pause"_spr,
		"Editor Level From Pause",
		"Enter the level editor for a level from the pause menu.",
		{ Keybind::create(KEY_E, Modifier::Shift), Keybind::create(KEY_E, CTRL_CMD) },
		"Play/Pause", false
	});
	/* ————————————————————————— LEVELBROWSER/LISTINFO/LEVELINFO KEYBINDS ————————————————————————— */ // DONE
	binds->registerBindable({
		"refresh-page"_spr,
		"Refresh Page",
		"Refresh the layer you're on.\n<cy>Use this keybind with caution; abusing/spamming this keybind can get you rate-limited or banned from RobTop's servers.</c>",
		{ Keybind::create(KEY_R, CTRL_CMD) },
		"JustEnoughKeybinds/Partially Universal Shortcuts", false
	});
	binds->registerBindable({
		"first-page"_spr,
		"Go To First Page",
		"Go to the first page.<cy>Requires BetterInfo by Cvolton if viewing comments.</c>",
		{ Keybind::create(KEY_ArrowLeft, Modifier::Shift),  Keybind::create(KEY_Left, Modifier::Shift) },
		"JustEnoughKeybinds/Partially Universal Shortcuts", false
	});
	binds->registerBindable({
		"last-page"_spr,
		"Go To Last Page",
		"Go to the last page.\n\n<cy>Requires BetterInfo by Cvolton if browsing levels/level lists or viewing comments.</c>",
		{ Keybind::create(KEY_ArrowRight, Modifier::Shift), Keybind::create(KEY_Right, Modifier::Shift) },
		"JustEnoughKeybinds/Partially Universal Shortcuts", false
	});
	binds->registerBindable({
		"comments"_spr,
		"View Comments",
		"View comments (either for a specific profile, level list, or level).",
		{ Keybind::create(KEY_C, Modifier::Shift) },
		"JustEnoughKeybinds/Partially Universal Shortcuts", false
	});
	/* ————————————————————————— MISC NAVIGATION KEYBINDS ————————————————————————— */ // DONE
	binds->registerBindable({
		"find"_spr,
		"Find Level/List",
		"Find a level/level list from your personal/saved levels/lists.",
		{ Keybind::create(KEY_F, CTRL_CMD) },
		"JustEnoughKeybinds/Levels and Level Lists", false
	});
	binds->registerBindable({
		"leaderboard"_spr,
		"View Level Leaderboard",
		"View the leaderboards for a level.",
		{ Keybind::create(KEY_F, CTRL_CMD) },
		"JustEnoughKeybinds/Levels and Level Lists", false
	});
	binds->registerBindable({
		"sort-by-size"_spr,
		"Sort Levels by Size",
		"Sort your custom levels/saved levels by size. <cy>Requires Level Size by hiimjasmine00.</c>",
		{ Keybind::create(KEY_S, CTRL_CMD | Modifier::Shift) },
		"JustEnoughKeybinds/Levels and Level Lists", false
	});
	/* ————————————————————————— LISTINFO/LEVELINFO KEYBINDS ————————————————————————— */ // DONE
	binds->registerBindable({
		"settings"_spr,
		"Level Options",
		"View the options menu for a level.",
		{ Keybind::create(KEY_U, CTRL_CMD) },
		"JustEnoughKeybinds/Levels and Level Lists", false
	});
	binds->registerBindable({
		"clone"_spr,
		"Clone Level/List",
		"Clone a level/list.",
		{ Keybind::create(KEY_C, CTRL_CMD) },
		"JustEnoughKeybinds/Levels and Level Lists", false
	});
	binds->registerBindable({
		"info"_spr,
		"View Level/List Info",
		"View the info for a level/list.",
		{ Keybind::create(KEY_I, CTRL_CMD) },
		"JustEnoughKeybinds/Levels and Level Lists", false
	});
	binds->registerBindable({
		"favorite"_spr,
		"Favorite Level/List",
		"Favorite a level/list.",
		{ Keybind::create(KEY_D, CTRL_CMD) },
		"JustEnoughKeybinds/Levels and Level Lists", false
	});
	binds->registerBindable({
		"add-to-list"_spr,
		"Add Level to List",
		"Add a level to one of your level lists.",
		{ Keybind::create(KEY_D, CTRL_CMD | Modifier::Shift) },
		"JustEnoughKeybinds/Levels and Level Lists", false
	});
	binds->registerBindable({
		"add-to-folder"_spr,
		"Add Level to Folder",
		"Add a level to one of your level folders.",
		{ Keybind::create(KEY_D, CTRL_CMD | Modifier::Shift | ALT_CTRL) },
		"JustEnoughKeybinds/Levels and Level Lists", false
	});
	/* ————————————————————————— LEVEL SEARCH KEYBINDS ————————————————————————— */ // DONE
	binds->registerBindable({
		"level-search-clear-filters"_spr,
		"Clear Search Filters",
		"Clears your search filters.",
		{ Keybind::create(KEY_Delete, Modifier::Shift) },
		"JustEnoughKeybinds/Level Search", false
	});
	binds->registerBindable({
		"level-search-open-filters"_spr,
		"Open Search Filters",
		"Open advanced search filters.",
		{ Keybind::create(MINUS, Modifier::Shift) },
		"JustEnoughKeybinds/Level Search", false
	});
	binds->registerBindable({
		"level-search-search-mode"_spr,
		"Toggle Levels/Lists Mode",
		"Switch between searching for levels and level lists.",
		{ Keybind::create(KEY_L, Modifier::Shift) },
		"JustEnoughKeybinds/Level Search", false
	});
	binds->registerBindable({
		"level-search-rate-filter"_spr,
		"Star/Moon Rate",
		"Toggle the star rate filter.",
		{ Keybind::create(KEY_Zero, ALT_CTRL) },
		"JustEnoughKeybinds/Level Search", false
	});
	binds->registerBindable({
		"level-search-quick-downloads"_spr,
		"Downloads",
		"Open the \"Downloads\" Quick Search option.",
		{ Keybind::create(KEY_D, CTRL_CMD), Keybind::create(KEY_D, ALT_CTRL) },
		"JustEnoughKeybinds/Level Search/Quick Search Shortcuts", false
	});
	binds->registerBindable({
		"level-search-quick-trending"_spr,
		"Trending",
		"Open the \"Trending\" Quick Search option.",
		{ Keybind::create(KEY_T, CTRL_CMD), Keybind::create(KEY_T, ALT_CTRL) },
		"JustEnoughKeybinds/Level Search/Quick Search Shortcuts", false
	});
	binds->registerBindable({
		"level-search-quick-awarded"_spr,
		"Awarded",
		"Open the \"Awarded\" Quick Search option.",
		{ Keybind::create(KEY_A, CTRL_CMD), Keybind::create(KEY_A, ALT_CTRL) },
		"JustEnoughKeybinds/Level Search/Quick Search Shortcuts", false
	});
	binds->registerBindable({
		"level-search-quick-likes"_spr,
		"Likes",
		"Open the \"Likes\" Quick Search option.",
		{ Keybind::create(KEY_L, CTRL_CMD), Keybind::create(KEY_L, ALT_CTRL) },
		"JustEnoughKeybinds/Level Search/Quick Search Shortcuts", false
	});
	binds->registerBindable({
		"level-search-quick-recent"_spr,
		"Recent",
		"Open the \"Recent\" Quick Search option.",
		{ Keybind::create(KEY_R, CTRL_CMD), Keybind::create(KEY_R, ALT_CTRL) },
		"JustEnoughKeybinds/Level Search/Quick Search Shortcuts", false
	});
	binds->registerBindable({
		"level-search-quick-following"_spr,
		"Followed",
		"Open the \"Followed\" Quick Search option.",
		{ Keybind::create(KEY_F, CTRL_CMD), Keybind::create(KEY_F, ALT_CTRL) },
		"JustEnoughKeybinds/Level Search/Quick Search Shortcuts", false
	});
	binds->registerBindable({
		"level-search-quick-sent"_spr,
		"Sent",
		"Open the \"Sent\" Quick Search option.",
		{ Keybind::create(KEY_S, CTRL_CMD), Keybind::create(KEY_S, ALT_CTRL) },
		"JustEnoughKeybinds/Level Search/Quick Search Shortcuts", false
	});
	binds->registerBindable({
		"level-search-quick-magic"_spr,
		"Magic",
		"Open the \"Magic\" Quick Search option.",
		{ Keybind::create(KEY_M, CTRL_CMD), Keybind::create(KEY_M, ALT_CTRL) },
		"JustEnoughKeybinds/Level Search/Quick Search Shortcuts", false
	});
	binds->registerBindable({
		"level-search-quick-friends"_spr,
		"Friends",
		"Open the \"Friends\" Quick Search option.",
		{ Keybind::create(KEY_I, CTRL_CMD), Keybind::create(KEY_I, ALT_CTRL) },
		"JustEnoughKeybinds/Level Search/Quick Search Shortcuts", false
	});
	binds->registerBindable({
		"level-search-length-tiny"_spr,
		"Tiny",
		"Toggle the \"Tiny\" level length search filter.",
		{ Keybind::create(KEY_One, ALT_CTRL) },
		"JustEnoughKeybinds/Level Search/Level Length Filters", false
	});
	binds->registerBindable({
		"level-search-length-short"_spr,
		"Short",
		"Toggle the \"Short\" level length search filter.",
		{ Keybind::create(KEY_Two, ALT_CTRL) },
		"JustEnoughKeybinds/Level Search/Level Length Filters", false
	});
	binds->registerBindable({
		"level-search-length-medium"_spr,
		"Medium",
		"Toggle the \"Medium\" level length search filter.",
		{ Keybind::create(KEY_Three, ALT_CTRL) },
		"JustEnoughKeybinds/Level Search/Level Length Filters", false
	});
	binds->registerBindable({
		"level-search-length-long"_spr,
		"Long",
		"Toggle the \"Long\" level length search filter.",
		{ Keybind::create(KEY_Four, ALT_CTRL) },
		"JustEnoughKeybinds/Level Search/Level Length Filters", false
	});
	binds->registerBindable({
		"level-search-length-xl"_spr,
		"XL",
		"Toggle the \"XL\" level length search filter.",
		{ Keybind::create(KEY_Five, ALT_CTRL) },
		"JustEnoughKeybinds/Level Search/Level Length Filters", false
	});
	binds->registerBindable({
		"level-search-length-plat"_spr,
		"Plat.",
		"Toggle the \"Plat.\" level length search filter.",
		{ Keybind::create(KEY_Six, ALT_CTRL), Keybind::create(KEY_Nine, ALT_CTRL) },
		"JustEnoughKeybinds/Level Search/Level Length Filters", false
	});
	binds->registerBindable({
		"level-search-difficulty-na"_spr,
		"NA",
		"Toggle the \"NA\" level difficulty search filter.",
		{ Keybind::create(KEY_One, CTRL_CMD) },
		"JustEnoughKeybinds/Level Search/Level Difficulty Filters", false
	});
	binds->registerBindable({
		"level-search-difficulty-easy"_spr,
		"Easy",
		"Toggle the \"Easy\" level difficulty search filter.",
		{ Keybind::create(KEY_Two, CTRL_CMD) },
		"JustEnoughKeybinds/Level Search/Level Difficulty Filters", false
	});
	binds->registerBindable({
		"level-search-difficulty-normal"_spr,
		"Normal",
		"Toggle the \"Normal\" level difficulty search filter.",
		{ Keybind::create(KEY_Three, CTRL_CMD) },
		"JustEnoughKeybinds/Level Search/Level Difficulty Filters", false
	});
	binds->registerBindable({
		"level-search-difficulty-hard"_spr,
		"Hard",
		"Toggle the \"Hard\" level difficulty search filter.",
		{ Keybind::create(KEY_Four, CTRL_CMD) },
		"JustEnoughKeybinds/Level Search/Level Difficulty Filters", false
	});
	binds->registerBindable({
		"level-search-difficulty-harder"_spr,
		"Harder",
		"Toggle the \"Harder\" level difficulty search filter.",
		{ Keybind::create(KEY_Five, CTRL_CMD) },
		"JustEnoughKeybinds/Level Search/Level Difficulty Filters", false
	});
	binds->registerBindable({
		"level-search-difficulty-insane"_spr,
		"Insane",
		"Toggle the \"Insane\" level difficulty search filter.",
		{ Keybind::create(KEY_Six, CTRL_CMD) },
		"JustEnoughKeybinds/Level Search/Level Difficulty Filters", false
	});
	binds->registerBindable({
		"level-search-difficulty-demon"_spr,
		"Demon",
		"Toggle the \"Demon\" level difficulty search filter.",
		{ Keybind::create(KEY_Seven, CTRL_CMD) },
		"JustEnoughKeybinds/Level Search/Level Difficulty Filters", false
	});
	binds->registerBindable({
		"level-search-difficulty-auto"_spr,
		"Auto",
		"Toggle the \"Auto\" level difficulty search filter.",
		{ Keybind::create(KEY_Eight, CTRL_CMD) },
		"JustEnoughKeybinds/Level Search/Level Difficulty Filters", false
	});
	binds->registerBindable({
		"level-search-demon-filter"_spr,
		"Open Demon Filter",
		"Toggle the \"Demon\" level difficulty search filter.",
		{ Keybind::create(KEY_Nine, CTRL_CMD), Keybind::create(KEY_Zero, CTRL_CMD) },
		"JustEnoughKeybinds/Level Search/Level Difficulty Filters", false
	});
	/* ————————————————————————— "DEMON FILTERS" KEYBINDS ————————————————————————— */ // DONE
	binds->registerBindable({
		"level-search-all-demons"_spr,
		"Demon",
		"Toggle the \"Demon\" filter.",
		{ Keybind::create(KEY_One, Modifier::Shift | Modifier::Control) },
		"JustEnoughKeybinds/Level Search/Demon Filters", false
	});
	binds->registerBindable({
		"level-search-easy-demon"_spr,
		"Easy Demon",
		"Toggle the \"Easy Demon\" filter.",
		{ Keybind::create(KEY_Two, Modifier::Shift | Modifier::Control) },
		"JustEnoughKeybinds/Level Search/Demon Filters", false
	});
	binds->registerBindable({
		"level-search-medium-demon"_spr,
		"Medium Demon",
		"Toggle the \"Medium Demon\" filter.",
		{ Keybind::create(KEY_Three, Modifier::Shift | Modifier::Control) },
		"JustEnoughKeybinds/Level Search/Demon Filters", false
	});
	binds->registerBindable({
		"level-search-hard-demon"_spr,
		"Hard Demon",
		"Toggle the \"Hard Demon\" filter.",
		{ Keybind::create(KEY_Four, Modifier::Shift | Modifier::Control) },
		"JustEnoughKeybinds/Level Search/Demon Filters", false
	});
	binds->registerBindable({
		"level-search-insane-demon"_spr,
		"Insane Demon",
		"Toggle the \"Insane Demon\" filter.",
		{ Keybind::create(KEY_Five, Modifier::Shift | Modifier::Control) },
		"JustEnoughKeybinds/Level Search/Demon Filters", false
	});
	binds->registerBindable({
		"level-search-extreme-demon"_spr,
		"Extreme Demon",
		"Toggle the \"Extreme Demon\" filter.",
		{ Keybind::create(KEY_Six, Modifier::Shift | Modifier::Control) },
		"JustEnoughKeybinds/Level Search/Demon Filters", false
	});
	/* ————————————————————————— "MY LEVELS" KEYBINDS ————————————————————————— */ // DONE
	binds->registerBindable({
		"new-editor-level"_spr,
		"Create New Level/List",
		"Create a new level/list.",
		{ Keybind::create(KEY_N, CTRL_CMD) },
		"JustEnoughKeybinds/\"My Levels\" Navigation", false
	});
	binds->registerBindable({
		"toggle-level-lists"_spr,
		"Toggle Levels/Lists Mode",
		"Toggle between viewing local editor levels and local level lists.",
		{ Keybind::create(KEY_L, CTRL_CMD | Modifier::Shift), Keybind::create(KEY_L, Modifier::Shift) },
		"JustEnoughKeybinds/\"My Levels\" Navigation", false
	});
	binds->registerBindable({
		"view-uploaded"_spr,
		"View Uploaded Levels/Lists",
		"View uploaded levels/level lists.",
		{ Keybind::create(KEY_L, CTRL_CMD | Modifier::Shift | ALT_CTRL) },
		"JustEnoughKeybinds/\"My Levels\" Navigation", false
	});
	/* ————————————————————————— "MORE OPTIONS" KEYBINDS ————————————————————————— */ // DONE
	binds->registerBindable({
		"more-options-layer"_spr,
		"More Options Shortcuts",
		"Open your GD settings.",
		{ Keybind::create(KEY_O, CTRL_CMD) },
		"JustEnoughKeybinds/More Options Navigation", false
	});
	binds->registerBindable({
		"previous-options-page"_spr,
		"Previous Options Page",
		"View the previous Options page.",
		{ Keybind::create(KEY_ArrowLeft), Keybind::create(KEY_Left) },
		"JustEnoughKeybinds/More Options Navigation", false
	});
	binds->registerBindable({
		"next-options-page"_spr,
		"Next Options Page",
		"View the next Options page.",
		{ Keybind::create(KEY_ArrowRight), Keybind::create(KEY_Right) },
		"JustEnoughKeybinds/More Options Navigation", false
	});
	/* ————————————————————————— GJGARAGELAYER KEYBINDS ————————————————————————— */ // DONE
	binds->registerBindable({
		"garage-cube"_spr,
		"Cube Tab",
		"View cubes of the icon kit.",
		{ Keybind::create(KEY_One) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-ship"_spr,
		"Ship Tab",
		"View ships of the icon kit.",
		{ Keybind::create(KEY_Two) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-jetpack"_spr,
		"Jetpack Tab",
		"View jetpacks of the icon kit.",
		{ Keybind::create(KEY_Two, Modifier::Shift) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-ball"_spr,
		"Ball Tab",
		"View balls of the icon kit.",
		{ Keybind::create(KEY_Three) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-ufo"_spr,
		"UFO Tab",
		"View UFOs of the icon kit.",
		{ Keybind::create(KEY_Four) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-wave"_spr,
		"Wave Tab",
		"View waves of the icon kit.",
		{ Keybind::create(KEY_Five) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-robot"_spr,
		"Robot Tab",
		"View robots of the icon kit.",
		{ Keybind::create(KEY_Six) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-spider"_spr,
		"Spider Tab",
		"View spiders of the icon kit.",
		{ Keybind::create(KEY_Seven) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-swing"_spr,
		"Swing Tab",
		"View swings of the icon kit.",
		{ Keybind::create(KEY_Eight) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-trail"_spr,
		"Trail + Special Animations Tab",
		"View trails and special animations of the icon kit.",
		{ Keybind::create(KEY_Nine) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-death-effect"_spr,
		"Death Effect Tab",
		"View death effects of the icon kit.",
		{ Keybind::create(KEY_Zero) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-select-p1"_spr,
		"Select Player 1",
		"Select Player 1 in the icon kit.\n\n<cy>Requires Separate Dual Icons by Weebify.</c>",
		{ Keybind::create(KEY_One, CTRL_CMD) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-select-p2"_spr,
		"Select Player 2",
		"Select Player 2 in the icon kit.\n\n<cy>Requires Separate Dual Icons by Weebify.</c>",
		{ Keybind::create(KEY_Two, CTRL_CMD) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-shards-page"_spr,
		"Shards of Power Shortcut",
		"View your Shards of Power progression.",
		{ Keybind::create(KEY_S, ALT_CTRL) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-colors-page"_spr,
		"Color Customization Shortcut",
		"Open the colors page of the icon kit.",
		{ Keybind::create(KEY_C, ALT_CTRL) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-previous-page"_spr,
		"Previous Page",
		"View the next page of your current category in the icon kit (or the Shards of Power page).",
		{ Keybind::create(KEY_ArrowLeft), Keybind::create(KEY_Left) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-next-page"_spr,
		"Next Page",
		"View the next page of your current category in the icon kit (or the Shards of Power page).",
		{ Keybind::create(KEY_ArrowRight), Keybind::create(KEY_Right) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-first-page"_spr,
		"First Page",
		"View the first page of your current category in the icon kit.",
		{ Keybind::create(KEY_ArrowLeft, Modifier::Shift), Keybind::create(KEY_Left, Modifier::Shift) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-last-page"_spr,
		"Last Page",
		"View the last page of your current category in the icon kit.",
		{ Keybind::create(KEY_ArrowRight, Modifier::Shift), Keybind::create(KEY_Right, Modifier::Shift) },
		"JustEnoughKeybinds/Icon Kit", false
	});
	binds->registerBindable({
		"garage-col1"_spr,
		"Primary Color Tab",
		"Switch to the Primary Color/Col1 Tab.",
		{ Keybind::create(KEY_One, Modifier::Shift) },
		"JustEnoughKeybinds/Icon Kit/Colors", false
	});
	binds->registerBindable({
		"garage-col2"_spr,
		"Secondary Color Tab",
		"Switch to the Secondary Color/Col2 Tab.",
		{ Keybind::create(KEY_Two, Modifier::Shift) },
		"JustEnoughKeybinds/Icon Kit/Colors", false
	});
	binds->registerBindable({
		"garage-glow"_spr,
		"Glow Color Tab",
		"Switch to the Glow Color Tab.",
		{ Keybind::create(KEY_Three, Modifier::Shift) },
		"JustEnoughKeybinds/Icon Kit/Colors", false
	});
	binds->registerBindable({
		"garage-outline"_spr,
		"Outline Color Tab",
		"Switch to the Outline Color Tab.\n\n<cy>Requires Fine Outline by Alphalaneous.</c>",
		{ Keybind::create(KEY_Four, Modifier::Shift) },
		"JustEnoughKeybinds/Icon Kit/Colors", false
	});
	/* ————————————————————————— LEADERBOARDS KEYBINDS ————————————————————————— */ // DONE
	binds->registerBindable({
		"lb-top-100"_spr,
		"Top 100",
		"View the Top 100 Leaderboards.",
		{ Keybind::create(KEY_One) },
		"JustEnoughKeybinds/Leaderboards Shortcuts", false
	});
	binds->registerBindable({
		"lb-friends"_spr,
		"Friends",
		"View the Friends Leaderboards.",
		{ Keybind::create(KEY_Two) },
		"JustEnoughKeybinds/Leaderboards Shortcuts", false
	});
	binds->registerBindable({
		"lb-global"_spr,
		"Global",
		"View the Global Leaderboards.",
		{ Keybind::create(KEY_Three) },
		"JustEnoughKeybinds/Leaderboards Shortcuts", false
	});
	binds->registerBindable({
		"lb-creators"_spr,
		"Creators",
		"View the Creators Leaderboards.",
		{ Keybind::create(KEY_Four) },
		"JustEnoughKeybinds/Leaderboards Shortcuts", false
	});
	/* ————————————————————————— PROFILEPAGE KEYBINDS ————————————————————————— */ // DONE
	binds->registerBindable({
		"follow-user"_spr,
		"Follow User",
		"Follow a user.",
		{ Keybind::create(KEY_D, CTRL_CMD) },
		"JustEnoughKeybinds/Profile Page Shortcuts", false
	});
	binds->registerBindable({
		"message-user"_spr,
		"Message User",
		"Message a user, or view your messages.",
		{ Keybind::create(KEY_M, ALT_CTRL) },
		"JustEnoughKeybinds/Profile Page Shortcuts", false
	});
	binds->registerBindable({
		"friend-user"_spr,
		"Friend User",
		"Friend a user, or view your friends list.",
		{ Keybind::create(KEY_F, CTRL_CMD) },
		"JustEnoughKeybinds/Profile Page Shortcuts", false
	});
	binds->registerBindable({
		"block-user"_spr,
		"Block User",
		"Block a user.",
		{ Keybind::create(KEY_B, CTRL_CMD | Modifier::Shift | ALT_CTRL) },
		"JustEnoughKeybinds/Profile Page Shortcuts", false
	});
	/* ————————————————————————— INFOLAYER COMMENTS KEYBINDS ————————————————————————— */ // DONE
	binds->registerBindable({
		"previous-page"_spr,
		"Go To Previous Page",
		"Go to the previous page.",
		{ Keybind::create(KEY_ArrowLeft), Keybind::create(KEY_Left) },
		"JustEnoughKeybinds/Comment Viewing Shortcuts", false
	});
	binds->registerBindable({
		"next-page"_spr,
		"Go To Next Page",
		"Go to the next page.",
		{ Keybind::create(KEY_ArrowRight), Keybind::create(KEY_Right) },
		"JustEnoughKeybinds/Comment Viewing Shortcuts", false
	});
	binds->registerBindable({
		"infolayer-sort-likes"_spr,
		"Sort by Likes",
		"Sort comments by like count.",
		{ Keybind::create(KEY_One) },
		"JustEnoughKeybinds/Comment Viewing Shortcuts", false
	});
	binds->registerBindable({
		"infolayer-sort-recent"_spr,
		"Sort by Recent",
		"Sort comments by date posted.",
		{ Keybind::create(KEY_Two) },
		"JustEnoughKeybinds/Comment Viewing Shortcuts", false
	});
	binds->registerBindable({
		"infolayer-extend"_spr,
		"Show/Hide Level Description",
		"Show/hide the level description <cy>(if applicable)</c>.",
		{ Keybind::create(KEY_Three) },
		"JustEnoughKeybinds/Comment Viewing Shortcuts", false
	});
	binds->registerBindable({
		"infolayer-small-mode"_spr,
		"Compact Comments",
		"Toggle compact mode when viewing comments.",
		{ Keybind::create(KEY_Four) },
		"JustEnoughKeybinds/Comment Viewing Shortcuts", false
	});
	/* ————————————————————————— MENULAYER KEYBINDS —————————————————————— */
	binds->registerBindable({
		"menulayer-globed"_spr,
		"Globed",
		"Enter Globed from the main menu.\n\n<cy>Requires Globed by dankmeme01. No, this does not automatically join Globed servers/lobbies/rooms for you.</c>",
		{ Keybind::create(KEY_G, CTRL_CMD) },
		"JustEnoughKeybinds/Main Menu Shortcuts", false
	});
	binds->registerBindable({
		"menulayer-garage"_spr,
		"Garage (Icon Kit)",
		"Enter the garage/icon kit from the main menu.",
		{ Keybind::create(KEY_G, ALT_CTRL) },
		"JustEnoughKeybinds/Main Menu Shortcuts", false
	});
	binds->registerBindable({
		"menulayer-online-menus"_spr,
		"Online Levels",
		"Enter the online levels menu from the main menu.",
		{ Keybind::create(KEY_E, CTRL_CMD) },
		"JustEnoughKeybinds/Main Menu Shortcuts", false
	});
	binds->registerBindable({
		"menulayer-my-profile"_spr,
		"My Profile",
		"Open your own profile page from the main menu.",
		{ Keybind::create(KEY_P, ALT_CTRL) },
		"JustEnoughKeybinds/Main Menu Shortcuts", false
	});
	binds->registerBindable({
		"menulayer-daily-chests"_spr,
		"Daily Chests",
		"Open the daily chests menu.",
		{ Keybind::create(KEY_D, CTRL_CMD) },
		"JustEnoughKeybinds/Main Menu Shortcuts", false
	});
	binds->registerBindable({
		"menulayer-texture-packs"_spr,
		"Texture Packs",
		"Open your texture packs from the main menu.\n\n<cy>Requires Texture Loader by Geode Team.</c>",
		{ Keybind::create(KEY_T, CTRL_CMD) },
		"JustEnoughKeybinds/Main Menu Shortcuts", false
	});
	/* —————————————————————————— CREATORLAYER KEYBINDS ———————————————————————— */
	binds->registerBindable({
		"creatorlayer-create"_spr,
		"Create",
		"Self-explanatory.",
		{ Keybind::create(KEY_C, Modifier::Shift) },
		"JustEnoughKeybinds/Creator Menu (CreatorLayer) Shortcuts", false
	});
	binds->registerBindable({
		"creatorlayer-saved"_spr,
		"Saved",
		"Self-explanatory.",
		{ Keybind::create(KEY_S, Modifier::Shift) },
		"JustEnoughKeybinds/Creator Menu (CreatorLayer) Shortcuts", false
	});
	binds->registerBindable({
		"creatorlayer-scores"_spr,
		"Scores",
		"Self-explanatory.",
		{ Keybind::create(KEY_O, Modifier::Shift) },
		"JustEnoughKeybinds/Creator Menu (CreatorLayer) Shortcuts", false
	});
	binds->registerBindable({
		"creatorlayer-quests"_spr,
		"Quests",
		"Self-explanatory.",
		{ Keybind::create(KEY_Q, Modifier::Shift) },
		"JustEnoughKeybinds/Creator Menu (CreatorLayer) Shortcuts", false
	});
	binds->registerBindable({
		"creatorlayer-versus"_spr,
		"Versus",
		"Self-explanatory.",
		{ Keybind::create(KEY_V, Modifier::Shift) },
		"JustEnoughKeybinds/Creator Menu (CreatorLayer) Shortcuts", false
	});
	binds->registerBindable({
		"creatorlayer-map"_spr,
		"The Map",
		"Self-explanatory.",
		{ Keybind::create(KEY_T, Modifier::Shift) },
		"JustEnoughKeybinds/Creator Menu (CreatorLayer) Shortcuts", false
	});
	binds->registerBindable({
		"creatorlayer-daily"_spr,
		"Daily Level",
		"Self-explanatory.",
		{ Keybind::create(KEY_D, Modifier::Shift) },
		"JustEnoughKeybinds/Creator Menu (CreatorLayer) Shortcuts", false
	});
	binds->registerBindable({
		"creatorlayer-weekly"_spr,
		"Weekly Level",
		"Self-explanatory.",
		{ Keybind::create(KEY_W, Modifier::Shift) },
		"JustEnoughKeybinds/Creator Menu (CreatorLayer) Shortcuts", false
	});
	binds->registerBindable({
		"creatorlayer-event"_spr,
		"Event Level",
		"Self-explanatory.",
		{ Keybind::create(KEY_E, Modifier::Shift) },
		"JustEnoughKeybinds/Creator Menu (CreatorLayer) Shortcuts", false
	});
	binds->registerBindable({
		"creatorlayer-gauntlets"_spr,
		"Gauntlets",
		"Self-explanatory.",
		{ Keybind::create(KEY_G, Modifier::Shift) },
		"JustEnoughKeybinds/Creator Menu (CreatorLayer) Shortcuts", false
	});
	binds->registerBindable({
		"creatorlayer-featured"_spr,
		"Featured",
		"Self-explanatory.",
		{ Keybind::create(KEY_F, Modifier::Shift) },
		"JustEnoughKeybinds/Creator Menu (CreatorLayer) Shortcuts", false
	});
	binds->registerBindable({
		"creatorlayer-lists"_spr,
		"Lists",
		"Self-explanatory.",
		{ Keybind::create(KEY_L, Modifier::Shift) },
		"JustEnoughKeybinds/Creator Menu (CreatorLayer) Shortcuts", false
	});
	binds->registerBindable({
		"creatorlayer-paths"_spr,
		"Paths",
		"Self-explanatory.",
		{ Keybind::create(KEY_P, Modifier::Shift) },
		"JustEnoughKeybinds/Creator Menu (CreatorLayer) Shortcuts", false
	});
	binds->registerBindable({
		"creatorlayer-map-packs"_spr,
		"Map Packs",
		"Self-explanatory.",
		{ Keybind::create(KEY_M, Modifier::Shift) },
		"JustEnoughKeybinds/Creator Menu (CreatorLayer) Shortcuts", false
	});
	binds->registerBindable({
		"creatorlayer-search"_spr,
		"Search",
		"Self-explanatory.",
		{ Keybind::create(KEY_A, Modifier::Shift) },
		"JustEnoughKeybinds/Creator Menu (CreatorLayer) Shortcuts", false
	});
	/* —————————————————————————— REDASH KEYBINDS ———————————————————————— */ // DONE
	binds->registerBindable({
		"menulayer-redash-daily"_spr,
		"Daily Level",
		"<cy>Requires Overcharged Main Menu by Weebify and ninXout.</c>",
		{ Keybind::create(KEY_D, CTRL_CMD | Modifier::Shift) },
		"JustEnoughKeybinds/Main Menu Shortcuts/Overcharged Main Menu", false
	});
	binds->registerBindable({
		"menulayer-redash-weekly"_spr,
		"Weekly Level",
		"<cy>Requires Overcharged Main Menu by Weebify and ninXout.</c>",
		{ Keybind::create(KEY_W, CTRL_CMD | Modifier::Shift) },
		"JustEnoughKeybinds/Main Menu Shortcuts/Overcharged Main Menu", false
	});
	binds->registerBindable({
		"menulayer-redash-event"_spr,
		"Event Level",
		"<cy>Requires Overcharged Main Menu by Weebify and ninXout.</c>",
		{ Keybind::create(KEY_E, CTRL_CMD | Modifier::Shift) },
		"JustEnoughKeybinds/Main Menu Shortcuts/Overcharged Main Menu", false
	});
	binds->registerBindable({
		"menulayer-redash-create"_spr,
		"Create",
		"<cy>Requires Overcharged Main Menu by Weebify and ninXout.</c>",
		{ Keybind::create(KEY_C, ALT_CTRL | Modifier::Shift) },
		"JustEnoughKeybinds/Main Menu Shortcuts", false
	});
	binds->registerBindable({
		"menulayer-redash-saved"_spr,
		"Saved",
		"<cy>Requires Overcharged Main Menu by Weebify and ninXout.</c>",
		{ Keybind::create(KEY_S, ALT_CTRL | Modifier::Shift) },
		"JustEnoughKeybinds/Main Menu Shortcuts/Overcharged Main Menu", false
	});
	binds->registerBindable({
		"menulayer-redash-paths"_spr,
		"Paths",
		"<cy>Requires Overcharged Main Menu by Weebify and ninXout.</c>",
		{ Keybind::create(KEY_P, ALT_CTRL | Modifier::Shift) },
		"JustEnoughKeybinds/Main Menu Shortcuts/Overcharged Main Menu", false
	});
	binds->registerBindable({
		"menulayer-redash-leaderboards"_spr,
		"Scores (Leaderboards)",
		"<cy>Requires Overcharged Main Menu by Weebify and ninXout.</c>",
		{ Keybind::create(KEY_O, ALT_CTRL | Modifier::Shift) },
		"JustEnoughKeybinds/Main Menu Shortcuts/Overcharged Main Menu", false
	});
	binds->registerBindable({
		"menulayer-redash-gauntlets"_spr,
		"Gauntlets",
		"<cy>Requires Overcharged Main Menu by Weebify and ninXout.</c>",
		{ Keybind::create(KEY_G, ALT_CTRL | Modifier::Shift) },
		"JustEnoughKeybinds/Main Menu Shortcuts/Overcharged Main Menu", false
	});
	binds->registerBindable({
		"menulayer-redash-featured"_spr,
		"Featured",
		"<cy>Requires Overcharged Main Menu by Weebify and ninXout.</c>",
		{ Keybind::create(KEY_F, ALT_CTRL | Modifier::Shift) },
		"JustEnoughKeybinds/Main Menu Shortcuts/Overcharged Main Menu", false
	});
	binds->registerBindable({
		"menulayer-redash-lists"_spr,
		"Lists",
		"<cy>Requires Overcharged Main Menu by Weebify and ninXout.</c>",
		{ Keybind::create(KEY_L, ALT_CTRL | Modifier::Shift) },
		"JustEnoughKeybinds/Main Menu Shortcuts/Overcharged Main Menu", false
	});
	binds->registerBindable({
		"menulayer-redash-search"_spr,
		"Search",
		"<cy>Requires Overcharged Main Menu by Weebify and ninXout.</c>",
		{ Keybind::create(KEY_E, ALT_CTRL | Modifier::Shift) },
		"JustEnoughKeybinds/Main Menu Shortcuts/Overcharged Main Menu", false
	});
	// check BOTH right-side-menu AND ninxout.redash/redash-menu > ninxout.redash/main-menu
	binds->registerBindable({
		"menulayer-redash-mappacks"_spr,
		"Map Packs",
		"<cy>Requires Overcharged Main Menu by Weebify and ninXout.</c>",
		{ Keybind::create(KEY_M, ALT_CTRL | Modifier::Shift) },
		"JustEnoughKeybinds/Main Menu Shortcuts/Overcharged Main Menu", false
	});
	binds->registerBindable({
		"menulayer-redash-quests"_spr,
		"Quests",
		"<cy>Requires Overcharged Main Menu by Weebify and ninXout.</c>",
		{ Keybind::create(KEY_Q, ALT_CTRL | Modifier::Shift) },
		"JustEnoughKeybinds/Main Menu Shortcuts/Overcharged Main Menu", false
	});
	binds->registerBindable({
		"menulayer-redash-the-map"_spr,
		"The Map",
		"<cy>Requires Overcharged Main Menu by Weebify and ninXout.</c>",
		{ Keybind::create(KEY_T, ALT_CTRL | Modifier::Shift) },
		"JustEnoughKeybinds/Main Menu Shortcuts/Overcharged Main Menu", false
	});
	binds->registerBindable({
		"menulayer-redash-versus"_spr,
		"Versus",
		"<cy>Requires Overcharged Main Menu by Weebify and ninXout.</c>",
		{ Keybind::create(KEY_V, ALT_CTRL | Modifier::Shift) },
		"JustEnoughKeybinds/Main Menu Shortcuts/Overcharged Main Menu", false
	});
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
	binds->registerBindable({
		"custom-keybinds"_spr,
		"Custom Keybinds",
		"Open your custom keybinds.",
		{ Keybind::create(KEY_K, Modifier::Shift | ALT_CTRL | CTRL_CMD) },
		"JustEnoughKeybinds/Misc. Navigation", false
	});
	
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
	new EventListener([=](InvokeBindEvent* event) {
		if (GJBaseGameLayer::get() || !event->isDown() || !Utils::modEnabled()) return ListenerResult::Propagate;
		MoreOptionsLayer::create()->onKeybindings(nullptr); // normally this would just open the vanilla keybinds menu. however since customkeybinds is a required dependency it'll open the one from customkeybinds instead. win-win!
		return ListenerResult::Propagate;
	}, InvokeBindFilter(nullptr, "custom-keybinds"_spr));
	new EventListener([=](InvokeBindEvent* event) {
		if (GJBaseGameLayer::get() || !event->isDown() || !Utils::modEnabled()) return ListenerResult::Propagate;
		OptionsLayer::create()->onOptions(nullptr);
		return ListenerResult::Propagate;
	}, InvokeBindFilter(nullptr, "more-options-layer"_spr));

	Mod::get()->setLoggingEnabled(Utils::getBool("logging"));
	listenForSettingChanges("logging", [](bool logging){
		Mod::get()->setLoggingEnabled(logging);
	});
}