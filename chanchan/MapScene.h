#pragma once
//这个预编译是为了防止重复，产生无限递归
//可以替代ifndef......endif.....

#include "cocos2d.h"
#include"card.h"
USING_NS_CC;
#include<map>
#include<vector>
using namespace std;

class MapScene :public Scene
{

public:
	MapScene() : maxCardsInShop(5), cardGap(10.0f), cardHeight(100.0f) {
		// 其他初始化代码，如果有的话
	}
	//sSprite* shopBackground;//商店背景
	static Scene* createScene();
	virtual bool init();
	void startBattle();
	CREATE_FUNC(MapScene);//用于创建Cocos2d-x游戏引擎中的节点对象或自定义类的实例

	static MapScene* createcard();
	vector<Card*> currentCards;// 当前商店中的卡牌数组。
	void configureCard(Card* card);
	void refreshShop(Ref* pSender);
	//刷新商店
	Card* createRandomCard();//随机生成卡牌
	Vec2 getCardPosition(int cardIndex);



private:
	
	Sprite* background;// 战斗区域背景。
	vector<Sprite*> cardPlaceholders; //用于存储卡牌占位符的数组。
	const int maxCardsInShop;// 商店中最大卡牌数量。
	const float cardGap = 0;
	const float cardHeight = 0;// 卡牌之间的间隙和卡牌的高度（用于计算卡牌位置）。
};

