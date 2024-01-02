#include<iostream>
#include"MapScene.h"
#include"ShopLayer.h"
#include"Hero.h"
#include"Player.h"
#include"TeamManager.h"
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
    //红色边框
    this->addBorder(background);
    /*---------背景-----------*/

    lastHeroPosition = getStartPosition();

    auto spriteFrameCache = cocos2d::SpriteFrameCache::getInstance();
    for (int i = 1; i < 5; ++i) {
        std::string frameName = "star" + std::to_string(i) + ".png";
        spriteFrameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 50, 50)), frameName);
    }
    //添加玩家
    //player = new Player(100);
    //this->addChild(player->getSmallHero(), 10);
    Playerinit();//初始化玩家及血条
    isStartBattle = 0;
    //添加商店
    this->createShopLayer(this->player, this->background);

    ////----开始战斗按钮-----
    ////创建按钮
    //auto startBattleButton = cocos2d::ui::Button::create("play.png", "play1.png", "play2.png");

    //// 设置按钮的位置、大小等属性
    //startBattleButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    //startBattleButton->setPosition(cocos2d::Vec2(origin.x, visibleSize.height));

    //// 添加按钮到场景或层
    //this->addChild(startBattleButton);

    //startBattleButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    //    if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
    //        // 按钮点击事件
    //        TeamManager* teamManager = TeamManager::getInstance();
    //        teamManager->addHeroToPlayer(this->player);
    //        isStartBattle = 1;

    //    }
    //    });
    this->CreateBattle(0);//创建战斗层
    teamManager = TeamManager::getInstance();
    this->scheduleUpdate();

    return true;
}

void MapScene::createShopLayer(Player*player, TMXTiledMap* background)
{
	shopLayer = ShopLayer::createWithPlayer(player,background);
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
	const float offset = 150.0f;  // 英雄间的水平间距
	cocos2d::Vec2 newPosition = lastHeroPosition + cocos2d::Vec2(offset, 0);
	hero->setPosition(newPosition);

	// 更新最后一个英雄的位置
	lastHeroPosition = newPosition;

}

void MapScene::addBorder(TMXTiledMap* background)
{
	auto movableLayer = background->getLayer("move");
	movableLayer->setVisible(1);
	if (!movableLayer)//判断是否存在该图层
		return;
	Size mapSize = background->getMapSize();
	Size tileSize = background->getTileSize();

	// 创建一个新的图层用于添加红色边框
	auto borderLayer = Layer::create();
	this->addChild(borderLayer);

	for (int x = 0; x < mapSize.width; x++) {
		for (int y = 0; y < mapSize.height; y++) {
			int tileGid = movableLayer->getTileGIDAt(Vec2(x, y));
			if (tileGid > 0) {
				// 获取图块的位置
					Vec2 tilePos = movableLayer->getPositionAt(Vec2(x, y));
				// 创建一个红色边框的精灵
				Sprite* redBorder = Sprite::create("border.png");
				redBorder->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
				redBorder->setScale(0.12);
				// 设置红色边框的位置为图块的中心
				redBorder->setPosition(tilePos);
				// 将红色边框添加到图层中
				borderLayer->addChild(redBorder,1);
			}
		}
	}
}

void MapScene::Playerinit()
{
	player = new Player(100);
	this->addChild(player);
	player->SetSmallHero(Vec2(400, 400),true);
    //player->changeplayerBlood(50);
	enPlayer = new Player(100);
	this->addChild(enPlayer);
	enPlayer->SetSmallHero(Vec2(1200, 700),false);
}

Player* MapScene::getCurrentPlayer() {
	return  player;
}

void MapScene::CreateBattle(float t) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    heroInformation* testEnemyInfo = new heroInformation;
    testEnemyInfo->HP = 550;
    testEnemyInfo->MP = 60;
    testEnemyInfo->attack = 60;
    testEnemyInfo->atkspeed = 3;
    testEnemyInfo->defence = 45;
    testEnemyInfo->atkrange = 300;
    testEnemyInfo->movespeed = 80;
    testEnemyInfo->attackSpeed = 160;

    Hero *testEnemy = Hero::create();//创建一个英雄
    testEnemy->SetBaseInfo(testEnemyInfo, "En-Taric", Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 300));//设置英雄信息
    //this->addChild(testEnemy);//加到场景
    //testEnemy->SetHeroOn();//让英雄上场
    enPlayer->SetHero(testEnemy);

    heroInformation* testEnemyInfo2 = new heroInformation;
    testEnemyInfo2->HP = 550;
    testEnemyInfo2->MP = 60;
    testEnemyInfo2->attack = 70;
    testEnemyInfo2->atkspeed = 1.2;
    testEnemyInfo2->defence = 25;
    testEnemyInfo2->atkrange = 300;
    testEnemyInfo2->movespeed = 80;
    testEnemyInfo2->attackSpeed = 160;

    Hero* testEnemy2 = Hero::create();//创建一个英雄
    testEnemy2->SetBaseInfo(testEnemyInfo2, "En-Anny", Vec2(visibleSize.width / 2 + origin.x - 200, visibleSize.height / 2 + origin.y + 300));//设置英雄信息
    //this->addChild(testEnemy2);//加到场景
    //testEnemy2->SetHeroOn();//让英雄上场
    enPlayer->SetHero(testEnemy2);

    heroInformation* testEnemyInfo3 = new heroInformation;
    testEnemyInfo3->HP = 550;
    testEnemyInfo3->MP = 60;
    testEnemyInfo3->attack = 70;
    testEnemyInfo3->atkspeed = 1.2;
    testEnemyInfo3->defence = 25;
    testEnemyInfo3->atkrange = 300;
    testEnemyInfo3->movespeed = 80;
    testEnemyInfo3->attackSpeed = 160;

    Hero* testEnemy3 = Hero::create();//创建一个英雄
    testEnemy3->SetBaseInfo(testEnemyInfo3, "En-Alice", Vec2(visibleSize.width / 2 + origin.x + 200, visibleSize.height / 2 + origin.y + 180));//设置英雄信息
    enPlayer->SetHero(testEnemy3);

    heroInformation* testEnemyInfo4 = new heroInformation;
    testEnemyInfo4->HP = 850;
    testEnemyInfo4->MP = 60;
    testEnemyInfo4->attack = 70;
    testEnemyInfo4->atkspeed = 1.2;
    testEnemyInfo4->defence = 25;
    testEnemyInfo4->atkrange = 80;
    testEnemyInfo4->movespeed = 80;
    testEnemyInfo4->attackSpeed = 160;

    Hero* testEnemy4 = Hero::create();//创建一个英雄
    testEnemy4->SetBaseInfo(testEnemyInfo4, "En-Kennen", Vec2(visibleSize.width / 2 + origin.x + 100, visibleSize.height / 2 + origin.y + 80));//设置英雄信息
    enPlayer->SetHero(testEnemy4);

    heroInformation* testEnemyInfo5 = new heroInformation;
    testEnemyInfo5->HP = 850;
    testEnemyInfo5->MP = 60;
    testEnemyInfo5->attack = 70;
    testEnemyInfo5->atkspeed = 1.2;
    testEnemyInfo5->defence = 25;
    testEnemyInfo5->atkrange = 80;
    testEnemyInfo5->movespeed = 80;
    testEnemyInfo5->attackSpeed = 160;

    Hero* testEnemy5 = Hero::create();//创建一个英雄
    testEnemy5->SetBaseInfo(testEnemyInfo5, "En-Ali", Vec2(visibleSize.width / 2 + origin.x - 100, visibleSize.height / 2 + origin.y + 80));//设置英雄信息
    enPlayer->SetHero(testEnemy5);

    heroInformation* testEnemyInfo6 = new heroInformation;
    testEnemyInfo6->HP = 850;
    testEnemyInfo6->MP = 60;
    testEnemyInfo6->attack = 70;
    testEnemyInfo6->atkspeed = 1.2;
    testEnemyInfo6->defence = 25;
    testEnemyInfo6->atkrange = 80;
    testEnemyInfo6->movespeed = 80;
    testEnemyInfo6->attackSpeed = 160;

    Hero* testEnemy6 = Hero::create();//创建一个英雄
    testEnemy6->SetBaseInfo(testEnemyInfo6, "En-Chuishi", Vec2(visibleSize.width / 2 + origin.x + 50, visibleSize.height / 2 + origin.y +60));//设置英雄信息
    enPlayer->SetHero(testEnemy6);



    //heroInformation* testInfo = new heroInformation;
    //testInfo->HP = 400;
    //testInfo->MP = 60;
    //testInfo->attack = 65;
    //testInfo->atkspeed = 0.9;
    //testInfo->defence = 25;
    //testInfo->atkrange = 350;
    //testInfo->movespeed = 80;
    //testInfo->attackSpeed = 160;

    //Hero* testHero = Hero::create();//创建一个英雄
    //testHero->SetBaseInfo(testInfo, "Erlius", Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 300));//设置英雄信息
    ////this->addChild(testHero);//加到场景
    ////testHero->SetHeroOn();//让英雄上场
    //Player->SetHero(testHero);

    //heroInformation* testInfo2 = new heroInformation;
    //testInfo2->HP = 850;
    //testInfo2->MP = 60;
    //testInfo2->attack = 50;
    //testInfo2->atkspeed = 2;
    //testInfo2->defence = 35;
    //testInfo2->atkrange = 80;
    //testInfo2->movespeed = 80;
    //testInfo2->attackSpeed = 160;

    //Hero* testHero2 = Hero::create();//创建一个英雄
    //testHero2->SetBaseInfo(testInfo2, "Kuqi", Vec2(visibleSize.width / 2 + origin.x - 100, visibleSize.height / 2 + origin.y - 100));//设置英雄信息
    //myPlayer->SetHero(testHero2);

    //heroInformation* testInfo3 = new heroInformation;
    //testInfo3->HP = 400;
    //testInfo3->MP = 60;
    //testInfo3->attack = 80;
    //testInfo3->atkspeed = 0.8;
    //testInfo3->defence = 35;
    //testInfo3->atkrange = 280;
    //testInfo3->movespeed = 80;
    //testInfo3->attackSpeed = 160;

    //Hero* testHero3 = Hero::create();//创建一个英雄
    //testHero3->SetBaseInfo(testInfo3, "Kasia", Vec2(visibleSize.width / 2 + origin.x - 200, visibleSize.height / 2 + origin.y - 300));//设置英雄信息
    //myPlayer->SetHero(testHero3);

    //heroInformation* testInfo4 = new heroInformation;
    //testInfo4->HP = 700;
    //testInfo4->MP = 60;
    //testInfo4->attack = 60;
    //testInfo4->atkspeed = 1.5;
    //testInfo4->defence = 35;
    //testInfo4->atkrange = 200;
    //testInfo4->movespeed = 80;
    //testInfo4->attackSpeed = 160;

    //Hero* testHero4 = Hero::create();//创建一个英雄
    //testHero4->SetBaseInfo(testInfo4, "Lilia", Vec2(visibleSize.width / 2 + origin.x + 100, visibleSize.height / 2 + origin.y - 200));//设置英雄信息
    //myPlayer->SetHero(testHero4);


    /////////////
    // 以上是测试英雄的数据
    ////////////

    battlelayer = Battle::create();
    this->addChild(battlelayer);
    battlelayer->SetPlayer(player, enPlayer);//设置双方玩家

    /*auto startItem = MenuItemImage::create("start.png",
        "start2.png", CC_CALLBACK_0(Battle::Start, battlelayer));
    startItem->setScale(0.8);
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Vec2(visibleSize.width / 2 + origin.x, 80));
    this->addChild(menu, 5);*/

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
            teamManager->addHeroToPlayer(this->player);
            isStartBattle = 1;
            battlelayer->Start();
        }
        });

    //this->scheduleOnce(schedule_selector(Round::callback), 3);
  //this->addChild(battlelayer, 3);
  //battlelayer->Start();
}

void MapScene::update(float dt) {
    if (battlelayer->IsEnd()) {
        //this->unscheduleUpdate();
        shopLayer->showAllHero(1);
        //player->Restart();
    }
    else {
        if(isStartBattle)
        shopLayer->showAllHero(0);
    }
    if (player->IsDead()) {
        auto lose = Scene::create();
        auto label1 = Label::createWithTTF("LOSE", "fonts/Marker Felt.ttf", 140);
        label1->setPosition(Vec2(960, 540));
        lose->addChild(label1);
        Director::getInstance()->pushScene(lose);

        this->unscheduleUpdate();
    }
    else if (enPlayer->IsDead()) {
        auto win = Scene::create();
        auto label1 = Label::createWithTTF("WIN", "fonts/Marker Felt.ttf", 140);
        label1->setPosition(Vec2(960, 540));
        win->addChild(label1);
        Director::getInstance()->pushScene(win);

        this->unscheduleUpdate();
    }

}


