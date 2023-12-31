#pragma once
#include "cocos2d.h"
#include"Hero.h"
class TeamManager {
public:
    std::vector<Hero*>teamHeroes;//存放英雄的队伍，一般是将商店中的英雄转移过来
    void addOrUpdateHeroToTeam(Hero* hero);

    static TeamManager* getInstance();  // 获取队伍管理器实例的方法

   // Hero* findHeroByTag(int heroTag);  // 根据标签查找英雄

    // ... 其他队伍管理方法 ...
private:
    static TeamManager* _instance; // 静态实例指针

    
};