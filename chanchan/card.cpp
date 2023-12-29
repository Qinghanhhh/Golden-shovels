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
	// ��ʼ����������������
	return true;
}

//����Card����
Card* Card::createCard(const std::string& cardImage) {
    Card* card = new (std::nothrow) Card();
    if (card && card->initWithFile(cardImage)) {
        card->autorelease();//��̬����
        return card;
    }
    else {
        delete card;
        return nullptr;
    }
}
//���ÿ��Ƶ�λ�� ���̵�����ڶ�����
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

//�ع�ԭλ

void Card::setOriginalPosition(const Vec2& position) {
        originalPosition = position;
  }


 Vec2 Card::getOriginalPosition() const {
        return originalPosition;
 }



//ǰ�᣺������ƴ��������������ж�team���Ƿ�����˸ÿ��ƣ��������˾���ԭ���Ŀ�����������Ǿ��飬���û�о���team����ӿ��Ʋ�������Ǿ���
void Card::upgradeCard(Card*card)
{
    level++;
    //���ƶ�Ӧ��ɫ�ȼ������߼�
    //�ı俨����ۣ�����
    this->setStarLevel(level,card);
}

void Card::setStarLevel(int count,Card*card)
{
    if (count > 4)//��ֹԽ��
        return;
    string StarList[4] = {"star.png","2stars.png","3stars.png","4stars.png"};
   
    // ����ɵ����Ǿ���
    this->removeAllChildren();

    string starFileName = StarList[count-1];

    auto star = Sprite::create(starFileName);
    if (star) {
        float spacing = 15.0f;
        float CardWidth = card->getContentSize().width;
        float CardHeight = card->getContentSize().height;
        float posY = card->getPositionY()/10;
        float posX = card->getPositionX()/50;
        //��С
        if(count==1)
            star->setScale(0.1, 0.1);
        else
            star->setScale(0.2, 0.2);
        //λ��
        star->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        Vec2 StarPosition = card->getPosition();
        star->setPosition(posX,posY);
        card->addChild(star,0);
    }
}

//onEnter �����������ô��������Ǳ���ģ�������������ڽڵ���볡��ʱ�Զ��� Cocos2d-x ���õ�
//�������ֶ���������ʵ�ִ������ܣ�ֻҪȷ�� Card ������ȷ����ӵ��˳����С�
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

    Vec2 touchLocation = touch->getLocation();//��ȡ������ַ

     // ֱ��ʹ�ø�����ϵ�еĴ���λ�úͱ߽����бȽ�
    if (this->getBoundingBox().containsPoint(touchLocation)) {//���������ڿ�����
        this->setVisible(true);
        return true;
    }
    return false; // ����δ�����ڿ�����


}

void Card::onTouchMoved(Touch* touch, Event* event) {
    // �϶�����
    Vec2 loc = touch->getLocation();

    this->setPosition(loc);
}

void Card::onTouchEnded(Touch* touch, Event* event) {
    if (location == IN_SHOP) {//����λ���̵�
        int index = this->getCardImageIndex(); // ��ȡ���Ƶ�ͼƬ�±�
        BattleTeam::getInstance()->addCardToTeam(index, this);
        //location = IN_TEAM;//�ı俨�Ƶ�λ��
    }
    else if (location == IN_TEAM) {//����λ�ڶ���
        Vec2 loc = touch->getLocation();
        Rect battleAreaRect = BattleTeam::getBattleAreaRect();

        if (battleAreaRect.containsPoint(loc)) {
            // ���Ʊ��϶���ս��������ʵ��
            this->setVisible(false);
        }
        else {

            this->setOriginalPosition(this->getPosition());//�ع�ԭλ
            this->setPosition(getOriginalPosition());
        }
    }
}

void Card::updateTouchListener() {
    // �Ƴ��ɵĴ���������
    _eventDispatcher->removeEventListenersForTarget(this);

    // �����µĴ���������
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    // ���ô����¼��ص�
    listener->onTouchBegan = CC_CALLBACK_2(Card::onTouchBegan, this);
    if (location == IN_TEAM) {
        listener->onTouchMoved = CC_CALLBACK_2(Card::onTouchMoved, this);
    }
    listener->onTouchEnded = CC_CALLBACK_2(Card::onTouchEnded, this);

    // ע�ᴥ��������
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

