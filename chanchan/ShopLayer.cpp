#include "ShopLayer.h"

cocos2d::Sprite* ShopLayer::shopBackground;
const int maxCardsInShop = 5;
ShopLayer* ShopLayer::createLayer()
{
	return ShopLayer::create();
}



bool ShopLayer::BuyChess(Chess* chess, int& money, int maxChess, int nowChess)
{
	//Ǯ��������
	if (money < chess->GetchessData().chessPrice)
	{
		return false;
	}
	//û�ط��Ų�����
	else if (maxChess <= nowChess)
	{
		return false;
	}
	else
	{
		money -= chess->GetchessData().chessPrice;
		return true;
	}
}

bool ShopLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	//�����̵걳��
	this->createShopBackground();
	//�����̵��п��ƴ��λ��
	this->createItemPlace();
	//��ʼ������
	InitChessPool();
	//��ʼ��չʾ�̵꿨��
	this->displayCards();
	this->createRefreshButton();  // ����ˢ�°�ť
	this->displayMoney();
	return true;
}

void ShopLayer::createShopBackground()
{
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	shopBackground = Sprite::create("shopbackground.png");
	// �����̵걳��������Ԫ��
	Size originalSize = shopBackground->getContentSize();//��ȡԭʼͼƬ��С
	// ����ê��Ϊ���е�
	shopBackground->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	// �����µĿ�Ⱥ͸߶�
	float newWidth = visibleSize.width; // ռ��������Ļ���
	float newHeight = visibleSize.height/4; // ռ����Ļ�߶ȵ�1/4
	// Ӧ������
	shopBackground->setScale(0.9, 0.9);
	// ����λ�ã�ʹ�̵�λ����Ļ�ײ�
	shopBackground->setPosition(Vec2(newWidth / 2, originalSize.height /8));
	this->addChild(shopBackground);
}

void ShopLayer::createItemPlace()
{
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	
	// �����һ�ű���ͼ����ʼλ��
	float startX = 650.0f;
	float startY = 0;
	float itemWidth = 118.0f; // ����ÿ�ű���ͼ�Ŀ���� 100
	float itemHeight = 118.0f; // ����ÿ�ű���ͼ�ĸ߶��� 100
	float itemSpacing = 5.0f;//���
	// ѭ�������ͷ������ű���ͼ
	for (int i = 0; i < maxCardsInShop; ++i) {
		auto itemBackground = Sprite::create("position.png"); 

		itemBackground->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
		//itemBackground->setScale(0.6, 0.6);
		itemBackground->setContentSize(Size(itemWidth, itemHeight)); // ���ñ���ͼ�ߴ�
		//startY = (shopBackground->getContentSize().height/2);
		//float itemWidth = itemBackground->getContentSize().width;
		itemBackground->setPosition(startX + i * (itemWidth+itemSpacing), startY);
		this->addChild(itemBackground);
	}
}
void  ShopLayer::InitChessPool()
{
	chessPool.clear();

	for (int i = 0; i < 108; i++)
	{
		chessPool.push_back(new Mage("��ܽ��"));
		chessPool.push_back(new Shooter("������"));
		chessPool.push_back(new Shooter("��ķ"));
	}
	for (int i = 0; i < 60; i++)
	{
		chessPool.push_back(new Mage("����"));
		chessPool.push_back(new Mage("��������"));
		chessPool.push_back(new Shooter("ɪ��"));
	}
	for (int i = 0; i < 30; i++)
	{
		chessPool.push_back(new Mage("����"));
		chessPool.push_back(new Shooter("��ʯ"));
	}
}
Chess* ShopLayer::DrawChess()
{
	// ����Ϊ�գ����ؿ�ָ��
	if (chessPool.empty())
	{
		return nullptr;
	}

	// �����ȡһ�����ӿ�
	int randomIndex = rand() % chessPool.size();
	Chess* drawnChess = chessPool[randomIndex];

	// �ӿ������Ƴ��ÿ�
	chessPool.erase(chessPool.begin() + randomIndex);

	return drawnChess;
}
void ShopLayer::AddChess(Chess* chess)
{
	chessPool.push_back(chess);
}
void ShopLayer::getFiveChess()
{
	//����̵�5������
	if (!displayFiveChess.empty())
	{
		for (Chess* ptr : displayFiveChess)
		{
			if (ptr != nullptr)
			{
				AddChess(ptr);
				delete ptr; //�ͷ��ڴ�
			}

		}
	}
	displayFiveChess.clear();

	for (int i = 0; i < 5; i++)
	{
		displayFiveChess.push_back(DrawChess());
	}
}
int ShopLayer::SellChess(Chess* chess)
{
	AddChess(chess);
	return chess->GetchessData().chessPrice;
}
void ShopLayer::displayCards()
{
	Vec2 shopbg = shopBackground->getPosition();
	const int numCards = maxCardsInShop;//�̵�չʾ��������
	float cardSpacing = 12.0f;//���
	float startX = 650.0f;//��ʼ����ֵ
	float itemWidth = 110.0f; // ����ÿ�ű���ͼ�Ŀ��
	float itemHeight = 110.0f; // ����ÿ�ű���ͼ�ĸ߶�


	for (int i = 0; i < numCards; ++i) {
		// ���ѡ��һ�ſ���ͼƬ
		int randomIndex = rand() % (Card::cardImages.size()-1);
		auto card = Card::createCard(Card::cardImages[randomIndex]);
		card->setCardImageIndex(randomIndex); // ���ÿ��ƶ�Ӧ��ͼƬ�±�
		if (card) {
			//float scale = 0.4f; // ��С��ԭʼ��С��
			//card->setScale(scale);
			
			card->setContentSize(Size(itemWidth, itemHeight)); // ���ñ���ͼ�ߴ�
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
void  ShopLayer::ShufflePool()
{
	random_shuffle(chessPool.begin(), chessPool.end());
}
void ShopLayer::createRefreshButton()
{
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size shopbgSize = shopBackground->getContentSize();
	float startX =visibleSize.width/2-shopbgSize.width/2;
	auto refreshButton = MenuItemImage::create(
		"refresh.png",
		"refresh.png",
		CC_CALLBACK_1(ShopLayer::refreshShop, this));

	
	float scale = 0.15f; // ��С��ԭʼ��С��
	refreshButton->setScale(scale);

	Size buttonSize = refreshButton->getContentSize();//ע�⣺�õ��Ĵ�С��û������ǰ�Ĵ�С��

	// ���ð�ť��λ��Ϊ�̵����½�
	float posX =(visibleSize.width / 2 - shopbgSize.width / 2)+30.0f;
	float posY = buttonSize.height*scale/2;
	refreshButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	refreshButton->setPosition(Vec2(posX, posY));

	auto menu = Menu::create(refreshButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,3);
}

void ShopLayer::refreshShop(Ref* pSender) 
{
	// ʵ��ˢ���̵���߼�
		// �����ǰ�Ŀ��ƣ��������˵Ļ����������������ڵ㣬�����еĿ���Ҳ����ʧ
	/*for (auto& card : currentCards) {
		card->removeFromParent();
	}*/
	currentCards.clear();

	this->displayCards();
}

void ShopLayer::displayMoney()
{
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size shopbgSize = shopBackground->getContentSize();
	float startX = visibleSize.width / 2 - shopbgSize.width / 2;
	auto money = Sprite::create("money.png");
	float scale = 0.3f; // ��С��ԭʼ��С��
	money->setScale(scale);
	money->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	money->setPosition(Vec2(startX+money->getContentSize().width/2-10.0f, 100.0f));
	this->addChild(money,4);
	// ������ǩ������ʾǮ��
	auto moneyLabel = Label::createWithSystemFont("0", "MarkerFelt.ttf", 40);
	moneyLabel->setColor(Color3B::RED);

	// ���ñ�ǩλ�ã��������ǽ������ͼ����²ࣩ
  // ���ñ�ǩλ�ã��������ǽ������ͼ����Ҳࣩ
	moneyLabel->setPosition(Vec2(startX + money->getContentSize().width/2, 100.0f));
	
	// ����ǩ��Ϊ�ӽڵ���ӵ�����
	this->addChild(moneyLabel);


}


