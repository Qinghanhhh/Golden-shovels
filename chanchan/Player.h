#pragma once
#ifndef  _PLAYER_H_
#define  _PLAYER_H_
#include"ShopLayer.h"
#include "cocos2d.h"

USING_NS_CC;

//��ʼѪ��
constexpr int initplayerBlood = 100;
//ÿ�������� 4 ����
constexpr int addExperience = 4;
//���������ֵ�� 4
constexpr int addMaxExperience = 4;

class Player : public cocos2d::Scene
{
private:
	//��������
	bool playerIsDead;

	//���Ѫ��
	int playerBlood;

	//���
	int playerMoney;

	//��ҵȼ�
	int playerLevel;

	//��������һ����Ҫ���پ���
	int playerNeedExperience;

	//�����ϳ�����������
	int playerMaxNumChess;

	//��Ҿ���
	int playerExperience;

	//�������
	vector<Chess*> chessPlayer;

	//��ұ�ս������
	vector<Chess*> chessPreparePlayer;

	//����ϳ�����
	vector<Chess*> chessWarPlayer;
public:
	ShopLayer* chessShop;
	Player(ShopLayer** shop);

	//Ѫ������
	void changeplayerBlood(int hurt);

	//��ȡ�������
	int getplayerMoney() const;

	//�ı�������
	void changeplayerMoney(int num);

	//������
	bool buyplayerExperience();

	//�ж������ȼ�
	bool changeplayerLevel(int exp = 0);

	//������ֻ�ܴӱ�ս������
	void sellMyChess(Chess* chess);

	//����
	bool buyMyChess(Chess* chess);

	//�����̵�
	bool Update();
};


#endif

