#include "AppDelegate.h"
#include "HelloWorldScene.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1400, 850);
static cocos2d::Size smallResolutionSize = cocos2d::Size(1400, 850);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}


void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}


static int register_all_packages()
{
    return 0;
}

bool AppDelegate::applicationDidFinishLaunching() {
  
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Try-1", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Try-1");
#endif
        director->setOpenGLView(glview);
    }
   
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0f / 60);


    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
 
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }
    register_all_packages();
    auto scene = HelloWorld::createScene();


    /********************************************************************************/
    scene->removeAllChildren();
    //以下为背景设置，粗糙版，仅演示用
    Size size = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create("sample.png");
    sprite->setPosition(size.width / 2, size.height / 2);
    float spx = sprite->getTextureRect().getMaxX();
    float spy = sprite->getTextureRect().getMaxY();
    sprite->setScaleX(size.width / spx); //设置精灵宽度缩放比例
    sprite->setScaleY(size.height / spy);

    // 将精灵添加到场景中
    scene->addChild(sprite,-1);
    /********************************************************************************/
    auto shopBottom = Sprite::create("shopBottom.webp");
    //待修改
    shopBottom->setPosition(size.width / 2, size.height / 2-700);
    shopBottom->setScaleX(size.width / shopBottom->getTextureRect().getMaxX()); //设置精灵宽度缩放比例
    shopBottom->setScaleY(size.height / shopBottom->getTextureRect().getMaxY());

    // 将精灵添加到场景中
    scene->addChild(shopBottom, 1);
    /********************************************************************************/
    // 创建一个卡池
    ChessPool* chessPool = new ChessPool();
    chessPool->InitChessPool();

    // 创建商店和玩家
    ChessShop* shop = new ChessShop(chessPool);
    //shop->setPosition(Vec2(240, 320));
    //scene->addChild(shop);

    vector<Player*> players;
    for (int i = 0; i < 8; ++i) {
        Player* player = new Player(shop);
        scene->addChild(player);
        players.push_back(player);
    }
    //假设玩家一是自己
    //players[0]->chessShop->getFiveChess();

    auto chessdisplay0 = Sprite::create((players[0]->chessShop)->displayFiveChess[0]->getchessImage());
    
    //chessdisplay0->setPosition(10, 100);
    //chessdisplay0->setScale(10, 20);
    if (chessdisplay0) {
        // 精灵对象不为空，可以安全地进行操作
        chessdisplay0->setPosition(10, 100);
        chessdisplay0->setScale(10, 20);
        // 将精灵对象添加到场景或父节点中
        scene->addChild(chessdisplay0);
    }
    else {
        // 精灵对象为空，处理加载失败的情况
        CCLOG("Failed to create chessdisplay0");
    }
    
    /*
    * auto chessdisplay1 = Sprite::create((players[0]->chessShop)->displayFiveChess[1]->getchessImage());
    auto chessdisplay2 = Sprite::create((players[0]->chessShop)->displayFiveChess[2]->getchessImage());
    auto chessdisplay3 = Sprite::create((players[0]->chessShop)->displayFiveChess[3]->getchessImage());
    auto chessdisplay4 = Sprite::create((players[0]->chessShop)->displayFiveChess[4]->getchessImage());
    scene->addChild(chessdisplay1, 2);
    scene->addChild(chessdisplay2, 2);
    scene->addChild(chessdisplay3, 2);
    scene->addChild(chessdisplay4, 2);
    
    */
   /********************************************************************************/
    director->runWithScene(scene);
    return true;
}


void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}


void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
