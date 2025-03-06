#pragma once

#define BETTERINFO "cvolton.betterinfo"
#define INSTALL_BETTERINFO_YOU_BLOCKHEAD return FLAlertLayer::create("Hey there!", "BetterInfo is not installed!", "Close")->show();

using namespace geode::prelude;

namespace Utils {
	template<class T> T getSetting(const std::string& setting);
	bool getBool(const std::string& setting);
	int64_t getInt(const std::string& setting);
	double getDouble(const std::string& setting);
	std::string getString(const std::string& setting);
	cocos2d::ccColor3B getColor(const std::string& setting);
	cocos2d::ccColor4B getColorAlpha(const std::string& setting);
	bool modEnabled();
	
	bool isModLoaded(const std::string& modID);
	Mod* getMod(const std::string& modID);
	std::string getModVersion(Mod* mod);

	FLAlertLayer* fakeAlertLayer(const int tag);

	void activateButtonSafe(const std::string& query, CCNode* parentNode);

	CCMenu* findMenu(const std::string& query, CCNode* parentNode);
	void pressFirstButtonInMenu(const std::string &query, CCNode *parentNode);
	void pressLastButtonInMenu(const std::string &query, CCNode *parentNode);
}