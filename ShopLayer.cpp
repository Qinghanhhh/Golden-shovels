#include "ShopLayer.h"

cocos2d::Sprite* ShopLayer::shopBackground;
const int maxCardsInShop = 5;
ShopLayer* ShopLayer::createLayer()
{
	return ShopLayer::create();
}

bool ShopLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	//创建商店背景
	this->createShopBackground();
	//创建商店中卡牌存放位置
	this->createItemPlace();
	//初始化展示商店卡牌
	this->displayCards();
	this->createRefreshButton();  // 创建刷新按钮
	return true;
}

void ShopLayer::createShopBackground()
{
	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	shopBackground = Sprite::create("shopbackground.png");
	// 配置商店背景和其他元素
	Size originalSize = shopBackground->getContentSize();//获取原始图片大小
	// 设置锚点为左中点
	shopBackground->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	// 设置新的宽度和高度
	float newWidth = visibleSize.width; // 占据整个屏幕宽度
	float newHeight = visibleSize.height/4; // 占据屏幕高度的1/4
	// 应用缩放
	shopBackground->setScale(0.9, 0.9);
	// 设置位置，使商店位于屏幕底部
	shopBackground->setPosition(Vec2(newWidth / 2, originalSize.height /8));
	this->addChild(shopBackground);
}

void ShopLayer::createItemPlace()
{
	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	
	// 计算第一张背景图的起始位置
	float startX = 750.0f;
	float startY = 0;
	float itemWidth = 118.0f; // 假设每张背景图的宽度是 100
	float itemHeight = 118.0f; // 假设每张背景图的高度是 100
	float itemSpacing = 5.0f;//间距
	// 循环创建和放置四张背景图
	for (int i = 0; i < 4; ++i) {
		auto itemBackground = Sprite::create("position.png"); 
		itemBackground->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		//itemBackground->setScale(0.6, 0.6);
		itemBackground->setContentSize(Size(itemWidth, itemHeight)); // 设置背景图尺寸
		//startY = (shopBackground->getContentSize().height/2);
		//float itemWidth = itemBackground->getContentSize().width;
		itemBackground->setPosition(startX + i * (itemWidth+itemSpacing), startY);
		this->addChild(itemBackground);
	}
}
void ShopLayer::displayCards()
{
	Vec2 shopbg = shopBackground->getPosition();
	const int numCards = 4;//商店展示卡牌数量
	float cardSpacing = 12.0f;//间隔
	float startX = 750.0f;//起始坐标值
	float itemWidth = 110.0f; // 假设每张背景图的宽度
	float itemHeight = 110.0f; // 假设每张背景图的高度


	for (int i = 0; i < numCards; ++i) {
		// 随机选择一张卡牌图片
		int randomIndex = rand() % (Card::cardImages.size()-1);
		auto card = Card::createCard(Card::cardImages[randomIndex]);
		card->setCardImageIndex(randomIndex); // 设置卡牌对应的图片下标
		if (card) {
			//float scale = 0.4f; // 缩小到原始大小的
			//card->setScale(scale);
			
			card->setContentSize(Size(itemWidth, itemHeight)); // 设置背景图尺寸
			float posX = startX + i * (card->getContentSize().width + cardSpacing);
			float posY = 60;
			card->setPosition(Vec2(posX, posY));
			card->setLocation(IN_SHOP);
			card->setOriginalPosition(card->getPosition());
			this->addChild(card);
			currentCards.pushBack(card);
		}
	}
}

void ShopLayer::createRefreshButton() {
	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size shopbgSize = shopBackground->getContentSize();
	float startX =visibleSize.width/2-shopbgSize.width/2;
	auto refreshButton = MenuItemImage::create(
		"refresh.png",
		"refresh.png",
		CC_CALLBACK_1(ShopLayer::refreshShop, this));

	
	float scale = 0.2f; // 缩小到原始大小的
	refreshButton->setScale(scale);

	Size buttonSize = refreshButton->getContentSize();//注意：得到的大小是没有缩放前的大小！

	// 设置按钮的位置为商店左下角
	float posX =(visibleSize.width / 2 - shopbgSize.width / 2)+30.0f;
	float posY = buttonSize.height*scale/2;
	refreshButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	refreshButton->setPosition(Vec2(posX, posY));

	auto menu = Menu::create(refreshButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,3);
}

void ShopLayer::refreshShop(Ref* pSender) {
	// 实现刷新商店的逻辑
		// 清除当前的卡牌，如果清除了的话，就是清楚了这个节点，队伍中的卡牌也会消失
	/*for (auto& card : currentCards) {
		card->removeFromParent();
	}*/
	currentCards.clear();

	this->displayCards();
}

void ShopLayer::createMoneyButton()
{
	float startX = 850.0f;
}


