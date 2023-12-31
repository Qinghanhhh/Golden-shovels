#include "ShopLayer.h"
#include"HeroData.h"
#include"Hero.h"
#include"Information.h"
#include"Player.h"
#include"TeamManager.h"
#include"MapScene.h"
#include<vector>
#include<algorithm>
#include "cocos/ui/UIButton.h"  // 引入UIButton头文件
#include "cocos/ui/UIWidget.h"  // 引入UIWidget头文件

const int DisplayedCardNum = 5;

bool ShopLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    /*--------------初始化商店界面----------------*/
        //创建商店背景
    this->createShopBackground();

	//角色位背景
	this->createItemPlace();

	this->createRefreshButton();

	this->createGoldIcon();
    /*--------------初始化商店界面----------------*/
	this->displayCards();
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
	float newHeight = visibleSize.height / 4; // 占据屏幕高度的1/4
	// 应用缩放
	shopBackground->setScale(0.9, 0.9);
	// 设置位置，使商店位于屏幕底部
	shopBackground->setPosition(Vec2(newWidth / 2, originalSize.height / 8));
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
		itemBackground->setPosition(startX + i * (itemWidth + itemSpacing), startY);
		this->addChild(itemBackground);
	}
}

vector<int>  ShopLayer::selectRandomHeroes(int count)
{
	std::vector<int> tags = {1,2,3,4 };
	std::random_shuffle(tags.begin(), tags.end());
	if (count > tags.size()) 
		count = tags.size();
	return std::vector<int>(tags.begin(), tags.begin() + count);
}

void ShopLayer::displayCards()
{
	Vec2 shopbg = shopBackground->getPosition();
	float cardSpacing = 12.0f;//间隔
	float startX = 750.0f;//起始坐标值
	float itemWidth = 110.0f; // 假设每张背景图的宽度
	float itemHeight = 110.0f; // 假设每张背景图的高度
/*-----------------------预置值------------------------*/

	int count = DisplayedCardNum - 1;
	std::vector<int> heroTags = selectRandomHeroes(DisplayedCardNum - 1);

	for (int i = 0; i < heroTags.size(); ++i) {
		int tag = heroTags[i];
		std::string heroName = Information::getNameByTag(tag);
		std::string heroImagePath = Information::getHeroPathByTag(tag);  

		Hero* heroCard = Hero::create(heroImagePath);  // 使用正确的图片路径
		if (!heroCard) {
			continue;
		}

		heroCard->setContentSize(Size(itemWidth, itemHeight));
		float posX = startX + i * (itemWidth + cardSpacing);
		float posY = 60;
		heroCard->setPosition(Vec2(posX, posY));
		heroCard->setUserData(new std::string(heroName));  // 存储英雄名称

		this->addTouchListenerToCard(heroCard, tag);
		this->addChild(heroCard);
		heroesInShop.push_back(heroCard);
		
	}
	//this->createRefreshButton();  // 添加刷新按钮
}


void ShopLayer::addTouchListenerToCard(Hero* heroCard,int tag) {
	// 为卡牌添加触摸事件监听器的逻辑
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = [heroCard, this, tag](Touch* touch, Event* event) -> bool {
		if (heroCard->getBoundingBox().containsPoint(touch->getLocation())) {
			this->onCardSelected(tag);
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, heroCard);//为卡牌添加监听器
}

void ShopLayer::onCardSelected(int heroTag) {
	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Player* player = Player::getInstance();
	TeamManager* teamManager = TeamManager::getInstance();
	const int HeroCost = 10;  // 假设每个英雄的成本是10金币

	if (player->hasEnoughGold(HeroCost)) {
		player->spendGold(HeroCost);  // 减少玩家的金币

		// 更新金币数量标签的显示内容
		int currentGold = player->getGold();
		goldLabel->setString(StringUtils::format("%d", currentGold));

		// 从已创建的英雄中找到对应的英雄实例
		Hero* selectedHero = nullptr;
		for (auto& hero : heroesInShop) {
			std::string* heroName = static_cast<std::string*>(hero->getUserData());
			if (heroName && *heroName == Information::getNameByTag(heroTag)) {
				selectedHero = hero;
				break;
			}
		}//遍历商店中的英雄，找到和tag对应的英雄加入队伍

		if (selectedHero) {
			teamManager->addOrUpdateHeroToTeam(selectedHero);  // 将英雄添加到队伍
			
			removeHeroFromShop(selectedHero);
			
			
		}

	}
	else {
		// 显示一个提示消息
		auto label = Label::createWithSystemFont("No enough money!", "arial", 50);
		label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(label);
		label->setColor(Color3B::RED);
		label->runAction(Sequence::create(
			DelayTime::create(2),  // 延迟2秒
			RemoveSelf::create(),   // 移除自身
			nullptr
		));
	}
	 
}

void ShopLayer::removeHeroFromShop(Hero* hero) {
	if (hero) {
		//hero->removeFromParent();  // 从层中移除英雄卡牌，会卡死
		heroesInShop.erase(std::remove(heroesInShop.begin(), heroesInShop.end(), hero), heroesInShop.end());  // 从容器中移除
	}
}

void ShopLayer::createRefreshButton() {
	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Size shopbgSize = shopBackground->getContentSize();
	float startX = visibleSize.width / 2 - shopbgSize.width / 2;

	auto refreshButton = cocos2d::ui::Button::create("refresh.png", "refresh.png");

	float scale = 0.18f; // 缩小到原始大小的
	refreshButton->setScale(scale);

	Size buttonSize = refreshButton->getContentSize();//注意：得到的大小是没有缩放前的大小！

	// 设置按钮的位置为商店左下角
	float posX = (visibleSize.width / 2 - shopbgSize.width / 2) + 30.0f;
	float posY = buttonSize.height * scale / 2-10;
	refreshButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	refreshButton->setPosition(Vec2(posX, posY));

	refreshButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
			this->refreshShopCards();  // 调用刷新商店卡牌的方法
		}
		});
	this->addChild(refreshButton);
}

void ShopLayer::refreshShopCards() {
	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Player* player = Player::getInstance();
	TeamManager* teamManager = TeamManager::getInstance();
	for (auto& hero : heroesInShop) {
		hero->removeFromParent();  // 从层中移除英雄卡牌
	}
	
	const int Cost = 20;
	if (player->hasEnoughGold(Cost)) {
		player->spendGold(Cost);  // 减少玩家的金币

		// 更新金币数量标签的显示内容
		int currentGold = player->getGold();
		goldLabel->setString(StringUtils::format("%d", currentGold));
		heroesInShop.clear();  // 清空容器
		displayCards();  // 重新展示随机抽取的角色
	}
	else {
		// 显示一个提示消息
		auto label = Label::createWithSystemFont("No enough money!", "arial", 50);
		label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(label);
		label->setColor(Color3B::RED);
		label->runAction(Sequence::create(
			DelayTime::create(2),  // 延迟2秒
			RemoveSelf::create(),   // 移除自身
			nullptr
		));
	}
}

void ShopLayer::createGoldIcon() {

	/*------------------金币图-------------------------------------------------*/

	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size shopbgSize = shopBackground->getContentSize();
	float startX = visibleSize.width / 2 - shopbgSize.width / 2;
	auto gold = Sprite::create("money.png");
	float scale = 0.3f; // 缩小到原始大小的
	gold->setScale(scale);
	gold->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	gold->setPosition(Vec2(startX + gold->getContentSize().width / 2 - 10.0f, 100.0f));
	this->addChild(gold);
	/*------------------金币图-------------------------------------------------*/

	/*-----------钱数-------------------------------*/
	 // 获取Player实例
	auto player = Player::getInstance();

	int currentGold = player->getGold();
	// 创建标签用于显示钱数
	goldLabel = Label::createWithSystemFont(StringUtils::format("%d", currentGold), "MarkerFelt.ttf", 40);
	goldLabel->setColor(Color3B::RED);
	// 设置标签位置（这里我们将其放在图标的右侧）
	goldLabel->setPosition(Vec2(startX + gold->getContentSize().width/1.5, 100.0f));

	// 将标签作为子节点添加到精灵
	this->addChild(goldLabel);
	/*-----------钱数-------------------------------*/

}