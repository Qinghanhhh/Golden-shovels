
#include"MapScene.h"
#include "ShopLayer.h"
#include"BattleTeam.h"
#include "ui/CocosGUI.h"
using namespace ui;


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


	//-----背景-----

	// 获取屏幕尺寸
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 创建瓦片地图作为背景
	auto background = TMXTiledMap::create("warmap.tmx");

	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	// 可以选择缩放地图以适应屏幕大小
	float bgscaleX = visibleSize.width / background->getContentSize().width;
	float bgscaleY = visibleSize.height / background->getContentSize().height;
	background->setScaleX(bgscaleX);
	background->setScaleY(bgscaleY);

	// 将地图添加到场景
	this->addChild(background,0);


	//-----商店背景-------
	// 创建商店背景
	auto shopLayer = ShopLayer::create();
	if (shopLayer) {
		this->addChild(shopLayer, 2); // 可以指定一个 zOrder 来控制图层顺序
	}
	//创建队伍背景
	auto battleteam = BattleTeam::create();
	if (battleteam) {
		this->addChild(battleteam, 1); // 可以指定一个 zOrder 来控制图层顺序
	}
	/*auto battleBlockLayer = BattleBlockLayer::create();
	this->addChild(battleBlockLayer);*/

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
			this->startBattle();
		}
		});
	return true;

}

void MapScene::startBattle() {
	// 遍历所有小英雄，触发它们的战斗状态
	/*for (auto hero : heroes) {
		hero->enterBattleState();
	}*/
}

//void Hero::enterBattleState() {
//	// 更新状态、播放战斗动画等
//}