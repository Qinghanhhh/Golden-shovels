#pragma once
//这个预编译是为了防止重复，产生无限递归
//可以替代ifndef......endif.....

#include "cocos2d.h"
#include "Hero.h"  // 引入 Hero 类定义
#include"HeroData.h"
#include <algorithm> 
#include <vector> 
#include"Information.h"
USING_NS_CC;


class ShopLayer:public Layer
{
protected:
	Sprite* shopBackground;
	std::vector<Hero*> heroesInShop;  // 商店中的英雄列表
   const  std::vector<HeroData> allHeroes = {
		{"hero1","hero1.png"},
		{"hero2","hero2.png"},
		{"hero3","hero3.png"},
		{"hero4","hero4.png"}
	};

   Label* goldLabel;
public:
	CREATE_FUNC(ShopLayer);

	virtual bool init() override;  // 初始化方法
	void createShopBackground();//背景
	void createItemPlace();//角色位
	vector<int>  selectRandomHeroes(int count);//随机选择五个
	void displayCards();
	void addTouchListenerToCard(Hero* heroCard,int tag);
	void onCardSelected(int heroTag);
	void removeHeroFromShop(Hero* hero);
	void createRefreshButton();
	void refreshShopCards();
	void createGoldIcon();
	void showMessage(const std::string& message);
	//展示卡牌的方法
};