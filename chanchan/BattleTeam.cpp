#include"BattleTeam.h"
#include"ShopLayer.h"
// 定义静态成员变量
BattleTeam* BattleTeam::_instance = nullptr;
cocos2d::Sprite* BattleTeam::teamBackground = nullptr;
BattleTeam* BattleTeam::createLayer()
{
    return BattleTeam::create();
}

bool BattleTeam::init()
{
	if (!Layer::init()) {
		return false;
	}
	this->createTeamBackground();
    
    return true;
}
void BattleTeam::createTeamBackground()
{
	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//---战斗位背景----
	teamBackground = Sprite::create("team.png");
	//teamBackground->setVisible(false);//设置不可见
	// 配置商店背景和其他元素
	Size originalSize = teamBackground->getContentSize();//获取原始图片大小
	// 设置锚点为左中点
	teamBackground->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	// 设置新的宽度和高度
	float newWidth = visibleSize.width/2; // 占据整个屏幕宽度
	float newHeight = visibleSize.height / 8; 
	// 计算缩放比例
	float spscaleX = newWidth / originalSize.width;
	float spscaleY = newHeight / originalSize.height;

	float posY = ShopLayer::shopBackground->getContentSize().height;
	// 缩放
	teamBackground->setScale(spscaleX, spscaleY);
	// 设置位置
	teamBackground->setPosition(Vec2(850.0f,posY));
	teamBackground->setLocalZOrder(0); // 确保背景的 Z-Order 较低
	this->addChild(teamBackground, 0);
}
Rect BattleTeam::getBattleAreaRect() {
	// 获取战斗背景图的位置和尺寸
	Vec2 bgPosition = teamBackground->getPosition();
	Size bgSize = teamBackground->getContentSize();

	// 考虑缩放因子
	float scaleX = teamBackground->getScaleX();
	float scaleY = teamBackground->getScaleY();

	// 计算实际显示的尺寸
	float actualWidth = bgSize.width * scaleX;
	float actualHeight = bgSize.height * scaleY;

	// 创建一个矩形代表战斗区域
	// 注意：根据锚点和位置调整矩形的起始点
	Rect battleAreaRect = Rect(bgPosition.x - actualWidth / 2, bgPosition.y - actualHeight / 2, actualWidth, actualHeight);

	return battleAreaRect;
}

BattleTeam* BattleTeam::getInstance()
{
	if (!_instance) {
		_instance = new BattleTeam();
		// 可能还需要执行其他初始化操作
	}
	return _instance;
}

void BattleTeam::addCard(Card* card)
{
	if (teamMembers.size() < maxTeamSize) {
		// 计算卡牌在战斗区域内的位置
		// 假设卡牌应该横向排列
		float cardSpacing = 10.0f; // 卡牌之间的间距
		Rect battleArea = getBattleAreaRect();
		Vec2 startPos = Vec2(battleArea.getMinX(), battleArea.getMidY()); // 战斗区域的起始位置

		Vec2 cardPos = startPos + Vec2(teamMembers.size() * (card->getContentSize().width + cardSpacing), 0);
		card->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		card->setPosition(cardPos);
		// 将卡牌添加到战斗队伍的视觉节点上
		this->addChild(card);

		// 将卡牌添加到队伍中
		teamMembers.push_back(card);
		card->setLocalZOrder(2); // 设置为 1
		teamBackground->setLocalZOrder(0); // 设置为 0 或更低
	}
}
Vec2 BattleTeam::calculateCardPosition(int index) {
	// 示例：水平排列卡牌
	float xOffset = 100.0f; // 起始偏移量
	float spacing = 50.0f; // 卡牌间距
	return (Vec2(xOffset + index * spacing, this->getContentSize().height / 2));
}

void BattleTeam::addCardToTeam(int cardIndex,Card*card)
{
	// 确保卡牌下标有效
	if (cardIndex < 0 || cardIndex >= 5) {
		return; // 或处理无效下标的情况
	}

	// 添加卡牌下标到数组
	cardCount[cardIndex]++;//对应序号卡牌数量+1
	float spacing = 15.0f;
	float itemWidth = 140.0f; // 假设每张背景图的宽度
	float itemHeight = 140.0f; // 假设每张背景图的高度
	float posY = teamBackground->getPositionY();
	float startposX = teamBackground->getPositionX();
	if (cardCount[cardIndex] == 1) {
		//添加卡牌到队伍
		teamMembers.push_back(card);
		card->removeFromParent();
		card->setTag(cardIndex);//卡牌标签
		card->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		float posX = startposX + (teamMembers.size() - 1) * (itemWidth + spacing);
		card->setPosition(Vec2(posX, posY));
		card->setScale(0.9, 0.9);
		teamBackground->addChild(card,3);
		//一颗星
		card->upgradeCard(card);
	}
	else if (cardCount[cardIndex] > 1) {
		card->removeFromParent();
		Card* card = dynamic_cast<Card*>(teamBackground->getChildByTag(cardIndex));
		//升星
		card->upgradeCard(card);
	}
	//位置设置为在队伍里
	card->setLocation(IN_TEAM);
	card->updateTouchListener();

	
}

void BattleTeam::removeCard(Card* card)
{
}
