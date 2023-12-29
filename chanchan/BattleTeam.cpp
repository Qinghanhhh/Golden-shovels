#include"BattleTeam.h"
#include"ShopLayer.h"
// ���徲̬��Ա����
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
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//---ս��λ����----
	teamBackground = Sprite::create("team.png");
	//teamBackground->setVisible(false);//���ò��ɼ�
	// �����̵걳��������Ԫ��
	Size originalSize = teamBackground->getContentSize();//��ȡԭʼͼƬ��С
	// ����ê��Ϊ���е�
	teamBackground->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	// �����µĿ�Ⱥ͸߶�
	float newWidth = visibleSize.width/2; // ռ��������Ļ���
	float newHeight = visibleSize.height / 8; 
	// �������ű���
	float spscaleX = newWidth / originalSize.width;
	float spscaleY = newHeight / originalSize.height;

	float posY = ShopLayer::shopBackground->getContentSize().height;
	// ����
	teamBackground->setScale(spscaleX, spscaleY);
	// ����λ��
	teamBackground->setPosition(Vec2(850.0f,posY));
	teamBackground->setLocalZOrder(0); // ȷ�������� Z-Order �ϵ�
	this->addChild(teamBackground, 0);
}
Rect BattleTeam::getBattleAreaRect() {
	// ��ȡս������ͼ��λ�úͳߴ�
	Vec2 bgPosition = teamBackground->getPosition();
	Size bgSize = teamBackground->getContentSize();

	// ������������
	float scaleX = teamBackground->getScaleX();
	float scaleY = teamBackground->getScaleY();

	// ����ʵ����ʾ�ĳߴ�
	float actualWidth = bgSize.width * scaleX;
	float actualHeight = bgSize.height * scaleY;

	// ����һ�����δ���ս������
	// ע�⣺����ê���λ�õ������ε���ʼ��
	Rect battleAreaRect = Rect(bgPosition.x - actualWidth / 2, bgPosition.y - actualHeight / 2, actualWidth, actualHeight);

	return battleAreaRect;
}

BattleTeam* BattleTeam::getInstance()
{
	if (!_instance) {
		_instance = new BattleTeam();
		// ���ܻ���Ҫִ��������ʼ������
	}
	return _instance;
}

void BattleTeam::addCard(Card* card)
{
	if (teamMembers.size() < maxTeamSize) {
		// ���㿨����ս�������ڵ�λ��
		// ���迨��Ӧ�ú�������
		float cardSpacing = 10.0f; // ����֮��ļ��
		Rect battleArea = getBattleAreaRect();
		Vec2 startPos = Vec2(battleArea.getMinX(), battleArea.getMidY()); // ս���������ʼλ��

		Vec2 cardPos = startPos + Vec2(teamMembers.size() * (card->getContentSize().width + cardSpacing), 0);
		card->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		card->setPosition(cardPos);
		// ��������ӵ�ս��������Ӿ��ڵ���
		this->addChild(card);

		// ��������ӵ�������
		teamMembers.push_back(card);
		card->setLocalZOrder(2); // ����Ϊ 1
		teamBackground->setLocalZOrder(0); // ����Ϊ 0 �����
	}
}
Vec2 BattleTeam::calculateCardPosition(int index) {
	// ʾ����ˮƽ���п���
	float xOffset = 100.0f; // ��ʼƫ����
	float spacing = 50.0f; // ���Ƽ��
	return (Vec2(xOffset + index * spacing, this->getContentSize().height / 2));
}

void BattleTeam::addCardToTeam(int cardIndex,Card*card)
{
	// ȷ�������±���Ч
	if (cardIndex < 0 || cardIndex >= 5) {
		return; // ������Ч�±�����
	}

	// ��ӿ����±굽����
	cardCount[cardIndex]++;//��Ӧ��ſ�������+1
	float spacing = 15.0f;
	float itemWidth = 140.0f; // ����ÿ�ű���ͼ�Ŀ��
	float itemHeight = 140.0f; // ����ÿ�ű���ͼ�ĸ߶�
	float posY = teamBackground->getPositionY();
	float startposX = teamBackground->getPositionX();
	if (cardCount[cardIndex] == 1) {
		//��ӿ��Ƶ�����
		teamMembers.push_back(card);
		card->removeFromParent();
		card->setTag(cardIndex);//���Ʊ�ǩ
		card->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		float posX = startposX + (teamMembers.size() - 1) * (itemWidth + spacing);
		card->setPosition(Vec2(posX, posY));
		card->setScale(0.9, 0.9);
		teamBackground->addChild(card,3);
		//һ����
		card->upgradeCard(card);
	}
	else if (cardCount[cardIndex] > 1) {
		card->removeFromParent();
		Card* card = dynamic_cast<Card*>(teamBackground->getChildByTag(cardIndex));
		//����
		card->upgradeCard(card);
	}
	//λ������Ϊ�ڶ�����
	card->setLocation(IN_TEAM);
	card->updateTouchListener();

	
}

void BattleTeam::removeCard(Card* card)
{
}
