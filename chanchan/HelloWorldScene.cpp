#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include"SingleScene.h"
#include"SetScene.h"
#include"OnlineScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //��ȡ���ݵ��������ڴ�С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //����һ����ǩ
    auto label = Label::createWithTTF("Golden Shovel Battle", "fonts/Marker Felt.ttf", 75);
    label->enableShadow(Color4B::BLUE);
    //label->enableOutline(Color4B::BLUE, 1);
    //label->enableGlow(Color4B::BLUE);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height * 1.5));
        this->addChild(label, 1);
    }

    //����һ��sprite
    auto sprite = Sprite::create("bg1.png");
    if (sprite == nullptr)
    {
        problemLoading("'bg1.png'");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite, 0);
    }


    //�½�һ���˵�
    /*online menu*/
    Sprite* onlineSpriteNormal = Sprite::create("onlineNormal.png");
    Sprite* onlineSpriteSelected = Sprite::create("onlineSelected.png");

    MenuItemSprite* onlineMenuItem = MenuItemSprite::create(onlineSpriteNormal, onlineSpriteSelected, this, menu_selector(HelloWorld::menu_click_online));
    onlineMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 4 * 2,
        origin.y + visibleSize.height / 4 * 1.2)));

    /*single menu*/
    MenuItemImage* singleMenuItem = MenuItemImage::create("singleNormal.png", "singleSelected.png", this, menu_selector(HelloWorld::menu_click_single));
    singleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 4 * 2,
        origin.y + visibleSize.height / 4 * 1.9)));

    /*set menu*/
    MenuItemImage* setMenuItem = MenuItemImage::create("setNormal.png", "setSelected.png", this, menu_selector(HelloWorld::menu_click_set));
    setMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 4 * 2,
        origin.y + visibleSize.height / 4 * 2.6)));

    /*exit menu*/
    MenuItemImage* exitMenuItem = MenuItemImage::create("exitNormal.png", "exitSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    exitMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 4 * 2,
        origin.y + visibleSize.height / 4 * 3.3)));

    //���һ������Ϊnull,��ʾ�б����
    Menu* menu = Menu::create(onlineMenuItem, singleMenuItem, setMenuItem, exitMenuItem, NULL);

    //����˵�
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu);

    //���뱳������
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music.mp3", true);
    return true;
}

/*-------------------�˵�����˳���Ϸʱ���øú���------------------*/
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}

/*-------------------�˵��������ģʽʱ���øú���------------------*/
void HelloWorld::menu_click_single(Ref* pSender)
{
    auto scene = SingleScene::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5, scene, Color3B(215, 237, 255)));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}

/*-------------------�˵��������ģʽʱ���øú���------------------*/
void HelloWorld::menu_click_online(Ref* pSender)
{
    auto scene = OnlineScene::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5, scene, Color3B(215, 237, 255)));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}

/*-------------------�˵������Ϸ����ʱ���øú���------------------*/
void HelloWorld::menu_click_set(Ref* pSender)
{
    auto scene = SetScene::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(0.5, scene, Color3B(215, 237, 255)));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}
