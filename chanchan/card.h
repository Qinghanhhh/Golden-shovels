#pragma once
#include"cocos2d.h"
USING_NS_CC;
#include"ChessShop.h"
#include"Chess.h"
#include "ui/CocosGUI.h"
using namespace ui;
#include<vector>
#include<string>
using namespace std;

enum CardLocation {
	IN_SHOP,
	IN_TEAM
};

class Card : public cocos2d::Sprite {
public:
	
	int level;
	
	static vector<string> cardImages;
	std::string name;
	std::string cardname;
	ChessShop chessshop;
	Chess chess;//��������
	Card()
		: level(0), // ��ʼ�� level
		cardImageIndex(0), // ��ʼ�� cardImageIndex
		location(IN_SHOP), // ��ʼ�� location��Ĭ��Ϊ IN_SHOP
		originalPosition(Vec2::ZERO) {}// ��ʼ�� originalPosition
	virtual bool init();

	static Card* createCard(const std::string& cardImage);
	
	void setLocation(CardLocation loc);//��ʼ��λ��

	void setCardImageIndex(int index);//����ͼƬ

	int getCardImageIndex() const;//�����±�

	void upgradeCard(Card* card);//������Ƭ
	void setStarLevel(int count, Card* card);//�����Ǽ�

	
	//�ع�ԭλ
	void setOriginalPosition(const Vec2& position);

	Vec2 getOriginalPosition() const;
	//����
	void onEnter();

	bool onTouchBegan(Touch* touch, Event* event);

	void onTouchMoved(Touch* touch, Event* event);

	void onTouchEnded(Touch* touch, Event* event);

	void updateTouchListener();

	CREATE_FUNC(Card);

private:

	CardLocation location;//���Ƶ�λ�� 0Ϊ�̵꣬1Ϊ������

	//Hero*hero;//ָ��Role�������
	int cardImageIndex; // �洢����ͼƬ�� cardImages �е��±�
	Vec2 originalPosition; // �洢���Ƶ�ԭʼλ��
};
