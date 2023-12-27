#pragma once
#include"card.h"
#include"cocos2d.h"
using namespace cocos2d;

class BattleTeam :public::Layer
{
public:
    static BattleTeam* createLayer();
    virtual bool init()override;
  
    CREATE_FUNC(BattleTeam);
    void createTeamBackground();
    static Rect getBattleAreaRect();
    static BattleTeam* getInstance();
    void addCard(Card* card);
    void removeCard(Card* card);
    Vec2 calculateCardPosition(int index);
    void addCardToTeam(int cardIndex,Card*card);
    // 其他与战斗队伍相关的方法

private:
    std::vector<int> cardCount{0,0,0,0}; // 存储卡牌下标
    static BattleTeam* _instance;
   std::vector<Card*> teamMembers; // 存储战斗队伍的成员卡牌
    static Sprite* teamBackground;
    static const int maxTeamSize = 5; // 假设战斗队伍最多有5个成员
};
