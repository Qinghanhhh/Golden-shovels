#include "cocos2d.h"
#include "Test.h"
USING_NS_CC;

Scene* Test::createScene()
{
    return Test::create();
}

bool Test::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())//若初始化失败，返回0
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* battleScene = Sprite::create("battleScene.png");
    battleScene->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));//正中间
    this->addChild(battleScene);

    heroInformation* testEnemyInfo = new heroInformation;
    testEnemyInfo->HP = 550;
    testEnemyInfo->MP = 60;
    testEnemyInfo->attack = 60;
    testEnemyInfo->atkspeed = 3;
    testEnemyInfo->defence = 45;
    testEnemyInfo->atkrange = 300;
    testEnemyInfo->movespeed = 80;
    testEnemyInfo->attackSpeed = 160;

    Hero* testEnemy = Hero::create();//创建一个英雄
    testEnemy->SetBaseInfo(testEnemyInfo, "En-Taric", Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 300));//设置英雄信息
    //this->addChild(testEnemy);//加到场景
    //testEnemy->SetHeroOn();//让英雄上场
    enPlayer->SetHero(testEnemy);

    heroInformation* testEnemyInfo2 = new heroInformation;
    testEnemyInfo2->HP = 950;
    testEnemyInfo2->MP = 60;
    testEnemyInfo2->attack = 70;
    testEnemyInfo2->atkspeed = 1.2;
    testEnemyInfo2->defence = 25;
    testEnemyInfo2->atkrange = 300;
    testEnemyInfo2->movespeed = 80;
    testEnemyInfo2->attackSpeed = 160;

    Hero* testEnemy2 = Hero::create();//创建一个英雄
    testEnemy2->SetBaseInfo(testEnemyInfo2, "En-Anny", Vec2(visibleSize.width / 2 + origin.x-200, visibleSize.height / 2 + origin.y + 300));//设置英雄信息
    //this->addChild(testEnemy2);//加到场景
    //testEnemy2->SetHeroOn();//让英雄上场
    enPlayer->SetHero(testEnemy2);

    heroInformation* testInfo = new heroInformation;
    testInfo->HP = 400;
    testInfo->MP = 60;
    testInfo->attack = 50;
    testInfo->atkspeed = 0.9;
    testInfo->defence = 25;
    testInfo->atkrange = 350;
    testInfo->movespeed = 80;
    testInfo->attackSpeed = 160;

    Hero* testHero = Hero::create();//创建一个英雄
    testHero->SetBaseInfo(testInfo, "Erlius", Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y-300));//设置英雄信息
    //this->addChild(testHero);//加到场景
    //testHero->SetHeroOn();//让英雄上场
    myPlayer->SetHero(testHero);

    heroInformation* testInfo2 = new heroInformation;
    testInfo2->HP = 700;
    testInfo2->MP = 60;
    testInfo2->attack = 50;
    testInfo2->atkspeed = 2;
    testInfo2->defence = 35;
    testInfo2->atkrange = 80;
    testInfo2->movespeed = 80;
    testInfo2->attackSpeed = 160;

    Hero* testHero2 = Hero::create();//创建一个英雄
    testHero2->SetBaseInfo(testInfo2, "Kuqi", Vec2(visibleSize.width / 2 + origin.x - 100, visibleSize.height / 2 + origin.y - 100));//设置英雄信息
    myPlayer->SetHero(testHero2);
    //Hero* test = Hero::create();
    //test=testHero2;
    //this->addChild(test);//加到场景
    //test->SetHeroOn();//让英雄上场

    //testHero2->setScale(0.9);
    Sleep(300);
    /*testHero->StartBattle(testEnemy);
    testEnemy->StartBattle(testHero);
    test->StartBattle(testEnemy);
    testEnemy2->StartBattle(testHero);*/


    
   
    battleLayer->SetPlayer(myPlayer, enPlayer);

    //auto menu = Menu::create();
    //menu->setPosition(Vec2(900, 300));
    //auto startItem = MenuItemImage::create("start.png",
    //    "start2.png",CC_CALLBACK_0(Battle::Start, battleLayer));
    //
    //menu->addChild(startItem);
    //startItem->setScale(0.5);

    //this->addChild(menu,3);
    this->addChild(battleLayer, 3);
    battleLayer->Start();
    Sleep(1000);
    return true;
}

void Test::callback(Ref* data) {
    //battleLayer->Start();
}
