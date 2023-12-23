#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "SingleScene.h"
#include "HelloWorldScene.h"
#include "2d/CCTMXTiledMap.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //获取导演单例，窗口大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    

    this->createMapLayer();
   
    return true;
}


void GameScene::createMapLayer()
{
    auto snowmap = TMXTiledMap::create("warmap.tmx");
    addChild(snowmap, 0, 1);
	return;
}

