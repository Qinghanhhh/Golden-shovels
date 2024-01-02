
#pragma once
#include"cocos2d.h"
#include"MapScene.h"
USING_NS_CC;

#include "ui/CocosGUI.h"
using namespace ui;

#include<string>
using std::string;

#include<vector>
using std::vector;

enum CardList
{
	Hero1,
	Hero2,
	Hero3,
	Hero4,
	Hero5
};

class Card :public Scene
{
public:
	CardList hero;
	string name;
	string cardname;
	Card() : hero(CardList::Hero1) { // 默认构造函数，可以选择一个默认的英雄
		// 默认初始化代码
	}
	Card(CardList hero) :hero(hero) {
		switch (hero) {
			case CardList::Hero1:
				name = "Hero1";
				cardname = "hero1.jpg";
				//属性
				break;
			case CardList::Hero2:
				name = "Hero2";
				cardname = "hero2.jpg";
				//属性
				break;
			case CardList::Hero3:
				name = "Hero3";
				cardname = "hero3.jpg";
				//属性
				break;
			case CardList::Hero4:
				name = "Hero4";
				cardname = "hero4.jpg";
				//属性
				break;
			case CardList::Hero5:
				name = "Hero5";
				cardname = "hero4.jpg";
				//属性
				break;
			default:
				name = "Unknown";
		}
	}
	virtual bool init();
	CREATE_FUNC(Card);



private:
	Sprite* shopBackground;//商店背景
	vector<Sprite*> cardPlaceholders; //用于存储卡牌占位符的数组。
};
