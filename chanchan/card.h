#pragma once
#include"cocos2d.h"
USING_NS_CC;
#include"ChessShop.h"
#include"Chess.h"
#include "ui/CocosGUI.h"
using namespace ui;
#include<vector>
#include<string>
using namespace std;

enum CardLocation {
	IN_SHOP,
	IN_TEAM
};

class Card : public cocos2d::Sprite {
public:
	
	int level;
	
	static vector<string> cardImages;
	std::string name;
	std::string cardname;
	ChessShop chessshop;
	Chess chess;//棋类属性
	Card()
		: level(0), // 初始化 level
		cardImageIndex(0), // 初始化 cardImageIndex
		location(IN_SHOP), // 初始化 location，默认为 IN_SHOP
		originalPosition(Vec2::ZERO) {}// 初始化 originalPosition
	virtual bool init();

	static Card* createCard(const std::string& cardImage);
	
	void setLocation(CardLocation loc);//初始化位置

	void setCardImageIndex(int index);//设置图片

	int getCardImageIndex() const;//设置下标

	void upgradeCard(Card* card);//升级卡片
	void setStarLevel(int count, Card* card);//设置星级

	
	//回归原位
	void setOriginalPosition(const Vec2& position);

	Vec2 getOriginalPosition() const;
	//监听
	void onEnter();

	bool onTouchBegan(Touch* touch, Event* event);

	void onTouchMoved(Touch* touch, Event* event);

	void onTouchEnded(Touch* touch, Event* event);

	void updateTouchListener();

	CREATE_FUNC(Card);

private:

	CardLocation location;//卡牌的位置 0为商店，1为队伍中

	//Hero*hero;//指向Role类的引用
	int cardImageIndex; // 存储卡牌图片在 cardImages 中的下标
	Vec2 originalPosition; // 存储卡牌的原始位置
};
