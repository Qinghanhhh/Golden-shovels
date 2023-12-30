#include "card.h"
#include"BattleTeam.h"
#include "ui/CocosGUI.h"
#include<string>
using namespace std;
using namespace ui;
using namespace cocos2d;

vector<string>Card::cardImages= { "hero1.png", "hero2.png", "hero3.png", "hero4.png", "hero4.png" };
bool Card::init()
{
	if (!Sprite::init()) {
		return false;
	}
	// 初始化场景的其他内容
	return true;
}

//创建Card对象
Card* Card::createCard(const std::string& cardImage) {
    Card* card = new (std::nothrow) Card();
    if (card && card->initWithFile(cardImage)) {
        card->autorelease();//动态管理
        return card;
    }
    else {
        delete card;
        return nullptr;
    }
}
//设置卡牌的位置 在商店或者在队伍中
void Card::setLocation(CardLocation loc)
{
    location = loc;
}
void Card::setCardImageIndex(int index) {
    cardImageIndex = index;
}

int Card::getCardImageIndex() const {
    return cardImageIndex;
}

//回归原位

void Card::setOriginalPosition(const Vec2& position) {
        originalPosition = position;
  }


 Vec2 Card::getOriginalPosition() const {
        return originalPosition;
 }



//前提：点击卡牌触发监听器，中判断team中是否添加了该卡牌，如果添加了就在原来的卡牌上添加星星精灵，如果没有就在team中添加卡牌并添加星星精灵
void Card::upgradeCard(Card*card)
{
    level++;
    //卡牌对应角色等级提升逻辑
    //改变卡牌外观，升星
    this->setStarLevel(level,card);
}

void Card::setStarLevel(int count,Card*card)
{
    if (count > 4)//防止越界
        return;
    string StarList[4] = {"star.png","2stars.png","3stars.png","4stars.png"};
   
    // 清除旧的星星精灵
    this->removeAllChildren();

    string starFileName = StarList[count-1];

    auto star = Sprite::create(starFileName);
    if (star) {
        float spacing = 15.0f;
        float CardWidth = card->getContentSize().width;
        float CardHeight = card->getContentSize().height;
        float posY = card->getPositionY()/10;
        float posX = card->getPositionX()/50;
        //大小
        if(count==1)
            star->setScale(0.1, 0.1);
        else
            star->setScale(0.2, 0.2);
        //位置
        star->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        Vec2 StarPosition = card->getPosition();
        star->setPosition(posX,posY);
        card->addChild(star,0);
    }
}

//onEnter 方法对于设置触摸监听是必须的，而这个方法是在节点加入场景时自动被 Cocos2d-x 调用的
//你无需手动调用它来实现触摸功能，只要确保 Card 对象被正确地添加到了场景中。
void Card::onEnter() {
    Sprite::onEnter();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    if (location == IN_SHOP) {
        listener->onTouchBegan = CC_CALLBACK_2(Card::onTouchBegan, this);
        listener->onTouchEnded = CC_CALLBACK_2(Card::onTouchEnded, this);
    }
    else if (location == IN_TEAM) {
        listener->onTouchBegan = CC_CALLBACK_2(Card::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(Card::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(Card::onTouchEnded, this);
    }
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
bool Card::onTouchBegan(Touch* touch, Event* event) {

    Vec2 touchLocation = touch->getLocation();//获取触摸地址

     // 直接使用父坐标系中的触摸位置和边界框进行比较
    if (this->getBoundingBox().containsPoint(touchLocation)) {//触摸发生在卡牌上
        this->setVisible(true);
        return true;
    }
    return false; // 触摸未发生在卡牌上


}

void Card::onTouchMoved(Touch* touch, Event* event) {
    // 拖动卡牌
    Vec2 loc = touch->getLocation();

    this->setPosition(loc);
}

void Card::onTouchEnded(Touch* touch, Event* event) {
    if (location == IN_SHOP) {//卡牌位于商店
        int index = this->getCardImageIndex(); // 获取卡牌的图片下标
        BattleTeam::getInstance()->addCardToTeam(index, this);
        //location = IN_TEAM;//改变卡牌的位置
    }
    else if (location == IN_TEAM) {//卡牌位于队伍
        Vec2 loc = touch->getLocation();
        Rect battleAreaRect = BattleTeam::getBattleAreaRect();

        if (battleAreaRect.containsPoint(loc)) {
            // 卡牌被拖动到战斗区域内实现
            this->setVisible(false);
        }
        else {

            this->setOriginalPosition(this->getPosition());//回归原位
            this->setPosition(getOriginalPosition());
        }
    }
}

void Card::updateTouchListener() {
    // 移除旧的触摸监听器
    _eventDispatcher->removeEventListenersForTarget(this);

    // 创建新的触摸监听器
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    // 设置触摸事件回调
    listener->onTouchBegan = CC_CALLBACK_2(Card::onTouchBegan, this);
    if (location == IN_TEAM) {
        listener->onTouchMoved = CC_CALLBACK_2(Card::onTouchMoved, this);
    }
    listener->onTouchEnded = CC_CALLBACK_2(Card::onTouchEnded, this);

    // 注册触摸监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

