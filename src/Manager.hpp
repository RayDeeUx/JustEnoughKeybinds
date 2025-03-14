#pragma once

// Manager.hpp structure by acaruso
// reused with explicit permission and strong encouragement

using namespace geode::prelude;

class Manager {

protected:
	static Manager* instance;
public:

	bool calledAlready = false;

	bool isRedash = false;
	bool isGlobed = false;
	bool isLevelSize = false;
	bool isBetterInfo = false;
	bool isFineOutline = false;
	bool isGeodeInPauseMenu = false;
	bool isSeparateDualIcons = false;
	bool isGeodeTextureLoader = false;
	bool isMrmanamaOrGarageReimagined = false;

	static Manager* getSharedInstance() {
		if (!instance) {
			instance = new Manager();
		}
		return instance;
	}

};