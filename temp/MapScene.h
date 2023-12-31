#pragma once
//这个预编译是为了防止重复，产生无限递归
//可以替代ifndef......endif.....

#include "cocos2d.h"
#include"Hero.h"
USING_NS_CC;
class MapScene :public Scene 
{
protected:
    cocos2d::Vec2 lastHeroPosition;  // 记录最后一个英雄的位置
public:
	//地图
	TMXTiledMap* background;

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MapScene);//用于创建Cocos2d-x游戏引擎中的节点对象或自定义类的实例

	//创建商店层实例
	void createShopLayer();

	cocos2d::Vec2 getStartPosition();  // 新方法来获取起始位置

	void addHeroToMap(Hero* hero);


};

