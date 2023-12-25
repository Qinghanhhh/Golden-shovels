#include "SmallHero.h"

bool SmallHero::init()
{
	if (!Sprite::init())//若初始化失败，返回0
	{
		return false;
	}
    heroHP = showHPMP::create();
    this->addChild(heroHP);
    // 创建一个监听器
    auto _mouseListener = EventListenerMouse::create();

    // 设置 onMouseUp 事件回调
    _mouseListener->onMouseUp = CC_CALLBACK_1(SmallHero::onMouseUp, this);

    // 将监听器添加到事件分发器中
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

SmallHero* SmallHero::create()
{
    SmallHero* sprite = new (std::nothrow) SmallHero();
    if (sprite && sprite->init())
    {
        sprite->autorelease();
        sprite->SetBaseInfo("SmallHero.png", Vec2(0, 0));  // 设置默认初始位置和图片
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void SmallHero::SetBaseInfo(string name, Vec2 pos) 
{
	smallHeroName = name;
	smallHeroPos = pos;
    HP = 100;
    isdead = 0;
    ismove = 0;
    isupdate = 0;
    money = 10;
    Level = 1;
    needExperience = 4;
	this->setTexture(smallHeroName);
    this->setPosition(smallHeroPos);
    //血条初始化
    Vec2 posBlood;
    posBlood.x = smallHeroPos.x;
    posBlood.y = smallHeroPos.y + this->getContentSize().height / 2 + 8;
    heroHP->setPosition(posBlood);
    heroHP->setScale(2.2f);
    heroHP->setBackgroundTexture("Blood-back.png");
    heroHP->setForegroundTexture("Blood-front.png");
    heroHP->setTotalProgress(HP);
    heroHP->setCurrentProgress(HP);
    heroHP->setScale(0.8);
    this->setVisible(1);
}

Vec2 SmallHero::onMouseUp(Event* event)
{
    EventMouse* e = dynamic_cast<EventMouse*>(event);
    if (e)
    {
        // 获取鼠标点击位置
        Vec2 mouseClickPos = Vec2(e->getCursorX(), e->getCursorY());

        // 在这里调用处理点击位置的函数
        handleMouseClick(mouseClickPos);

        return mouseClickPos;
    }
    return nullptr;
}

void SmallHero::handleMouseClick(const Vec2& clickPos)
{
    // 在这里可以进行进一步的处理，例如移动英雄到点击位置
    smallHeroMoveTo(clickPos);
}

//移动到指定位置
void SmallHero::smallHeroMoveTo(const Vec2& clickPos)
{
    Vec2 pos1 = smallHeroPos;
    Vec2 pos2 = clickPos;
    double distance = sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
    double time = distance / 500;
    MoveTo* moveTo = MoveTo::create(time, pos2);
    Sequence* seq = Sequence::create(moveTo, CallFuncN::create(CC_CALLBACK_1(SmallHero::StopMove, this)), NULL);
    this->runAction(seq);
}

//停止动作
void SmallHero::StopMove(Ref* obj) 
{
    this->stopAllActions();
    this->setTexture(smallHeroName);
    ismove = 0;
}

void SmallHero::ChangeHP(float data) 
{
    heroHP->setCurrentProgress(heroHP->getCurrentProgress() - data);
    HP = heroHP->getCurrentProgress();
}

void SmallHero::update(float dt)
{
    if (HP <= 0){
        this->isdead = 1;//死亡
        this->setVisible(0);
    }
    if (isdead){
        this->unscheduleUpdate();//停止该英雄的所有定时器
    }
}

bool SmallHero::IsDead() 
{
    return isdead;
}


