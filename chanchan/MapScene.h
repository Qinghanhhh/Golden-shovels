#pragma once
//���Ԥ������Ϊ�˷�ֹ�ظ����������޵ݹ�
//�������ifndef......endif.....

#include "cocos2d.h"
#include"card.h"
USING_NS_CC;
#include<map>
#include<vector>
using namespace std;

class MapScene :public Scene
{

public:
	MapScene() : maxCardsInShop(5), cardGap(10.0f), cardHeight(100.0f) {
		// ������ʼ�����룬����еĻ�
	}
	//sSprite* shopBackground;//�̵걳��
	static Scene* createScene();
	virtual bool init();
	void startBattle();
	CREATE_FUNC(MapScene);//���ڴ���Cocos2d-x��Ϸ�����еĽڵ������Զ������ʵ��

	static MapScene* createcard();
	vector<Card*> currentCards;// ��ǰ�̵��еĿ������顣
	void configureCard(Card* card);
	void refreshShop(Ref* pSender);
	//ˢ���̵�
	Card* createRandomCard();//������ɿ���
	Vec2 getCardPosition(int cardIndex);



private:
	
	Sprite* background;// ս�����򱳾���
	vector<Sprite*> cardPlaceholders; //���ڴ洢����ռλ�������顣
	const int maxCardsInShop;// �̵��������������
	const float cardGap = 0;
	const float cardHeight = 0;// ����֮��ļ�϶�Ϳ��Ƶĸ߶ȣ����ڼ��㿨��λ�ã���
};

