#pragma once
#include "cocos2d.h"
class Player {
public:
    

    

    static Player* getInstance();  // 获取玩家实例的方法

    Player();

    ~Player();

    bool hasEnoughGold(int amount);

    void spendGold(int amount);
    int  getGold();
private:
    static Player* _instance; // 静态实例指针
    int gold;  // 玩家的金币数量
    // ... 其他玩家属性 ...
};