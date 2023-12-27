#pragma once
#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "cocos2d.h"
#include "Hero.h"
#include "Player.h"
#define MaxRow 3
#define MaxCol 6
#define MaxHero 9
#define MaxDis 1000000
USING_NS_CC;

class Battle :public Layer {
public:
	CREATE_FUNC(Battle);
	virtual bool init();
	static Battle* createLayer();
	void Start();//战斗正式开始
	void SetPlayer(Player* my, Player* en);//加载双方玩家
	void SetHeroPos();
	void SetHeroData();//设置场上棋子的信息，应该是备战时完成
	double CountDistance(Vec2 pos1, Vec2 pos2);//计算某两个英雄之间的距离
	void SetAtkTarget(std::vector <Hero*>& atk, std::vector <Hero*>& tar, int atkNum, int tarNum);
	void UpdateTarget(std::vector <Hero*>& atk, std::vector <Hero*>& tar, int atkNum, int tarNum);//更新棋子的攻击目标
	void ResetHero();//重置棋子状态
	int IsEnd();//判断本回合是否结束，即是否分出胜负
	void End();//做战斗结束后的处理，包括小小英雄的扣血
	virtual	void update(float dt);
	void Destory();//注销所有定时器
private:
	std::vector <Hero*> self;
	std::vector <Hero*> enemy;
	//Hero* self[MaxHero];//我方上阵的英雄
	//Hero* enemy[MaxHero];//敌方上阵的英雄

	Vec2 myField[MaxRow][MaxCol] =
	{{ Vec2(665, 455), Vec2(770, 455), Vec2(875, 455), Vec2(980, 455), Vec2(1085, 455), Vec2(1190, 455)},
	 {Vec2(665, 525), Vec2(770, 525), Vec2(875, 525), Vec2(980, 525), Vec2(1085, 525), Vec2(1190, 525)},
	 {Vec2(665, 597), Vec2(770, 597), Vec2(875, 597), Vec2(980, 597), Vec2(1085, 597), Vec2(1190, 597)}};
	Vec2 enemyField[MaxRow][MaxCol] =
	{{Vec2(665, 385), Vec2(770, 385), Vec2(875, 385), Vec2(980, 385), Vec2(1085, 385), Vec2(1190, 385)},
	 {Vec2(665, 315), Vec2(770, 315), Vec2(875, 315), Vec2(980, 315), Vec2(1085, 315), Vec2(1190, 315)},
	 {Vec2(665, 245), Vec2(770, 245), Vec2(875, 245), Vec2(980, 245), Vec2(1085, 245), Vec2(1190, 245)}};
	site* myPos;//记录我方上场英雄的位置
	site* enPos;//记录敌方上场英雄的位置
	Player* myPlayer;//我方小小英雄
	Player* enPlayer;//敌方小小英雄
	int myHeroNum;
	int enHeroNum;
	int myLive;
	int enLive;
};

#endif
