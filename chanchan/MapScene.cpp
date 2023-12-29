
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

	//�����ʼ��ʧ��
	if (!Scene::init())
		return false;
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();


	//-----����-----

	// ��ȡ��Ļ�ߴ�
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ������Ƭ��ͼ��Ϊ����
	auto background = TMXTiledMap::create("warmap.tmx");

	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	// ����ѡ�����ŵ�ͼ����Ӧ��Ļ��С
	float bgscaleX = visibleSize.width / background->getContentSize().width;
	float bgscaleY = visibleSize.height / background->getContentSize().height;
	background->setScaleX(bgscaleX);
	background->setScaleY(bgscaleY);

	// ����ͼ��ӵ�����
	this->addChild(background,0);


	//-----�̵걳��-------
	// �����̵걳��
	auto shopLayer = ShopLayer::create();
	if (shopLayer) {
		this->addChild(shopLayer, 2); // ����ָ��һ�� zOrder ������ͼ��˳��
	}
	//�������鱳��
	auto battleteam = BattleTeam::create();
	if (battleteam) {
		this->addChild(battleteam, 1); // ����ָ��һ�� zOrder ������ͼ��˳��
	}
	/*auto battleBlockLayer = BattleBlockLayer::create();
	this->addChild(battleBlockLayer);*/

	//----��ʼս����ť-----
	//������ť
	auto startBattleButton = cocos2d::ui::Button::create("play.png", "play1.png", "play2.png");

	// ���ð�ť��λ�á���С������
	startBattleButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	startBattleButton->setPosition(cocos2d::Vec2(origin.x, visibleSize.height));

	// ��Ӱ�ť���������
	this->addChild(startBattleButton);
	
	startBattleButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
			// ��ť����¼�
			this->startBattle();
		}
		});
	return true;

}

void MapScene::startBattle() {
	// ��������СӢ�ۣ��������ǵ�ս��״̬
	/*for (auto hero : heroes) {
		hero->enterBattleState();
	}*/
}

//void Hero::enterBattleState() {
//	// ����״̬������ս��������
//}