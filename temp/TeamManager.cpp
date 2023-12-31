#include "TeamManager.h"
#include"MapScene.h"
#include"ShopLayer.h"

// 初始化静态成员变量
TeamManager* TeamManager::_instance = nullptr;

void TeamManager::addOrUpdateHeroToTeam(Hero* hero)
{
	if (hero) {
		bool heroFound = false;
		std::string* newHeroName = static_cast<std::string*>(hero->getUserData());

		for (auto& teamHero : teamHeroes) {
			std::string* teamHeroName = static_cast<std::string*>(teamHero->getUserData());
			if (teamHeroName && newHeroName && *teamHeroName == *newHeroName) {
				// 英雄已在队伍中，执行升级操作
				teamHero->upgrade();
				heroFound = true;
				break;
			}
		}

		if (!heroFound) {
			// 英雄不在队伍中，添加到队伍
			teamHeroes.push_back(hero);
			hero->setLevel(1);
			hero->updateStarLevel();
			// 获取地图场景的引用
			auto mapScene = dynamic_cast<MapScene*>(Director::getInstance()->getRunningScene());
			if (mapScene) {
				mapScene->addHeroToMap(hero);
				// 将英雄添加到地图层
				//mapScene->addHeroToMap(selectedHero);
			}
		}
	}
}

TeamManager* TeamManager::getInstance()
{
	if (_instance == nullptr) {
		_instance = new TeamManager();
		// 这里可以初始化其他属性，比如金币
	}
	return _instance;
}
