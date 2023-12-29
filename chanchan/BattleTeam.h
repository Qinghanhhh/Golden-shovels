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
    // ������ս��������صķ���

private:
    std::vector<int> cardCount{0,0,0,0}; // �洢�����±�
    static BattleTeam* _instance;
   std::vector<Card*> teamMembers; // �洢ս������ĳ�Ա����
    static Sprite* teamBackground;
    static const int maxTeamSize = 5; // ����ս�����������5����Ա
};
