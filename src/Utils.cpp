#include "Utils.hpp"

namespace Utils {
	template<class T> T getSetting(const std::string& setting) { return Mod::get()->getSettingValue<T>(setting); }

	bool getBool(const std::string& setting) { return getSetting<bool>(setting); }
	
	int64_t getInt(const std::string& setting) { return getSetting<int64_t>(setting); }
	
	double getDouble(const std::string& setting) { return getSetting<double>(setting); }

	std::string getString(const std::string& setting) { return getSetting<std::string>(setting); }

	ccColor3B getColor(const std::string& setting) { return getSetting<ccColor3B>(setting); }

	ccColor4B getColorAlpha(const std::string& setting) { return getSetting<ccColor4B>(setting); }

	bool modEnabled() { return getBool("enabled"); }
	
	bool isModLoaded(const std::string& modID) { return Loader::get()->isModLoaded(modID); }

	Mod* getMod(const std::string& modID) { return Loader::get()->getLoadedMod(modID); }

	std::string getModVersion(Mod* mod) { return mod->getVersion().toNonVString(); }

	FLAlertLayer* fakeAlertLayer(const int tag) {
		FLAlertLayer* lfny = FLAlertLayer::create("live from new york", "it's saturday night", "");
		lfny->setTag(tag);
		return lfny;
	}

	void activateButtonSafe(const std::string& query, CCNode* parentNode) {
		if (!Utils::modEnabled()) return;
		if (query.empty() || !parentNode) return log::info("query is empty OR parentNode is nullptr");
		if (utils::string::contains(query, BETTERINFO) && !isModLoaded(BETTERINFO)) INSTALL_BETTERINFO_YOU_BLOCKHEAD
		CCNode* clickableNode = parentNode->querySelector(query);
		if (!clickableNode) return log::info("couldn't find button {} in layer {}", query, parentNode->getID());
		if (const auto button = typeinfo_cast<CCMenuItemSpriteExtra*>(clickableNode); button && button->isVisible()) return button->activate();
		if (const auto toggler = typeinfo_cast<CCMenuItemToggler*>(clickableNode); toggler && toggler->isVisible()) return toggler->activate();
		log::info("couldn't find button {} in layer {}", query, parentNode->getID());
	}

	CCMenu* findMenu(const std::string& query, CCNode *parentNode) {
		if (!Utils::modEnabled()) return nullptr;
		if (query.empty() || !parentNode) {
			log::info("query is empty OR parentNode is nullptr");
			return nullptr;
		}
		if (utils::string::contains(query, BETTERINFO) && !isModLoaded(BETTERINFO)) {
			FLAlertLayer::create("Hey there!", "BetterInfo is not installed!", "Close")->show();
			return nullptr;
		}
		if (const auto menu = typeinfo_cast<CCMenu*>(parentNode->querySelector(query)); menu->isVisible()) return menu;
		log::info("couldn't find button {} in layer {}", query, parentNode->getID());
		return nullptr;
	}

	void pressFirstButtonInMenu(const std::string& query, CCNode *parentNode) {
		CCMenu* menu = Utils::findMenu(query, parentNode);
		if (!menu) return log::info("couldn't find {}", query);
		if (const auto button = menu->getChildByType<CCMenuItemSpriteExtra>(0); button && button->isVisible()) return button->activate();
		if (const auto toggler = menu->getChildByType<CCMenuItemToggler>(0); toggler && toggler->isVisible()) return toggler->activate();
		log::info("couldn't find toggler {} in {}", query, parentNode->getID());
	}

	void pressLastButtonInMenu(const std::string& query, CCNode *parentNode) {
		CCMenu* menu = Utils::findMenu(query, parentNode);
		if (!menu) return log::info("couldn't find {}", query);
		if (const auto button = menu->getChildByType<CCMenuItemSpriteExtra>(-1); button && button->isVisible()) return button->activate();
		if (const auto toggler = menu->getChildByType<CCMenuItemToggler>(-1); toggler && toggler->isVisible()) return toggler->activate();
		log::info("couldn't find toggler {} in {}", query, parentNode->getID());
	}
}