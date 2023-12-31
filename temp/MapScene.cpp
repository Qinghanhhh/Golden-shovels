#include<iostream>
#include"MapScene.h"
#include"ShopLayer.h"
#include"Hero.h"
#include "ui/CocosGUI.h"
using namespace ui;

using namespace std;

Scene* MapScene::createScene()
{
	return MapScene::create();
}

bool MapScene::init()
{
	//父类初始化失败
	if (!Scene::init())
		return false;

	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();

	/*---------背景-----------*/
	// 获取屏幕尺寸
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// 创建瓦片地图作为背景
	this->background = TMXTiledMap::create("warmap.tmx");
	if (!this->background) {
		return false; // 如果创建失败，则返回 false
	}

	// 将地图添加到场景
	this->addChild(background);

	/*---------背景-----------*/
	lastHeroPosition= getStartPosition();

	auto spriteFrameCache = cocos2d::SpriteFrameCache::getInstance();
	for (int i = 1; i < 5; ++i) {
		std::string frameName = "star" + std::to_string(i) + ".png";
		spriteFrameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 50, 50)), frameName);
	}

	//添加商店
	this->createShopLayer();

	//----开始战斗按钮-----
	//创建按钮
	auto startBattleButton = cocos2d::ui::Button::create("play.png", "play1.png", "play2.png");

	// 设置按钮的位置、大小等属性
	startBattleButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	startBattleButton->setPosition(cocos2d::Vec2(origin.x, visibleSize.height));

	// 添加按钮到场景或层
	this->addChild(startBattleButton);

	startBattleButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
			// 按钮点击事件
			//this->startBattle();
		}
		});



	return true;
}

void MapScene::createShopLayer()
{
	auto shopLayer = ShopLayer::create();
	this->addChild(shopLayer);
}

cocos2d::Vec2 MapScene::getStartPosition()
{

	auto objectGroup = background->getObjectGroup("startpoint");  // 获取名为 "start" 的对象层
	if (objectGroup) {
		auto startObject = objectGroup->getObject("startpoint");  // 获取名为 "start" 的对象
		if (!startObject.empty()) {
			float x = startObject["x"].asFloat();
			float y = startObject["y"].asFloat();
			return cocos2d::Vec2(x, y);
		}
	}
	return cocos2d::Vec2::ZERO;  // 如果找不到对象，返回零向量
}

void MapScene::addHeroToMap(Hero* hero)
{
	// 计算新英雄的位置
	const float offset = 200.0f;  // 假设英雄间的水平间距为50
	cocos2d::Vec2 newPosition = lastHeroPosition + cocos2d::Vec2(offset, 0);
	hero->setPosition(newPosition);

	// 更新最后一个英雄的位置
	lastHeroPosition = newPosition;

}
