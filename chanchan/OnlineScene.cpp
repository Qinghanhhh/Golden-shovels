#include "OnlineScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* OnlineScene::createScene()
{
    return OnlineScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool OnlineScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //��ȡ���ݵ��������ڴ�С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //����һ����ǩ
    auto label = Label::createWithTTF("Online Type", "fonts/Marker Felt.ttf", 75);
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
    auto sprite = Sprite::create("bg2.png");
    if (sprite == nullptr)
    {
        problemLoading("'bg2.png'");
    }
    else
    {
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite, 0);
    }


    //�½�һ���˵�

    /*openroom menu*/
    MenuItemImage* openroomMenuItem = MenuItemImage::create("openroomNormal.png", "openroomSelected.png", this, menu_selector(OnlineScene::menu_click_openroom));
    openroomMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 4 * 2,
        origin.y + visibleSize.height / 4 * 1.2)));

    /*joinroom menu*/
    MenuItemImage* joinroomMenuItem = MenuItemImage::create("joinroomNormal.png", "joinroomSelected.png", this, menu_selector(OnlineScene::menu_click_joinroom));
    joinroomMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 4 * 2,
        origin.y + visibleSize.height / 4 * 1.9)));

    /*return menu*/
    MenuItemImage* returnMenuItem = MenuItemImage::create("returnmenuNormal.png", "returnmenuSelected.png", CC_CALLBACK_1(OnlineScene::menuCloseCallback, this));
    returnMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(origin.x + visibleSize.width / 4 * 2,
        origin.y + visibleSize.height / 4 * 2.6)));

    //���һ������Ϊnull,��ʾ�б����
    Menu* menu = Menu::create(openroomMenuItem, joinroomMenuItem, returnMenuItem, NULL);

    //����˵�
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu);
    return true;
}

/*-------------------�˵�������ز˵�ʱ���øú���------------------*/
void OnlineScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->popScene();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}


/*-------------------�˵������������ʱ���øú���------------------*/
void OnlineScene::menu_click_openroom(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}

/*-------------------�˵�������뷿��ʱ���øú���------------------*/
void OnlineScene::menu_click_joinroom(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}