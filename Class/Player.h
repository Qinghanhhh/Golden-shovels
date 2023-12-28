#ifndef  _PLAYER_H_
#define  _PLAYER_H_

//#include "ChessShop.h"
#include "cocos2d.h"
#include <vector>
#include "Hero.h"
#define MaxHero 9

USING_NS_CC;

//初始血量
constexpr int initplayerBlood = 100;
//每次提升加 4 经验
constexpr int addExperience = 4;
//升级最大经验值加 4
constexpr int addMaxExperience = 4;

struct site {
	int x;
	int y;
};


class Hero;
class Player : public cocos2d::Sprite
{
private:
	//还活着吗
	bool playerIsDead;

	//玩家血量
	int playerBlood;

	////金币
	//int playerMoney;

	//玩家等级
	int playerLevel;

	////提升到下一级需要多少经验
	//int playerNeedExperience;

	////可以上场的棋子数量
	//int playerMaxNumChess;

	////玩家经验
	//int playerExperience;

	////玩家棋子
	//std::vector<Hero*> chessPlayer;

	////玩家备战区棋子
	//std::vector<Hero*> chessPreparePlayer;

	showHPMP* myHP;//小小英雄的血条

	Hero chessWarPlayer[MaxHero];//上阵的英雄

	int heroNum = 0;//上阵英雄数量

	site HeroPos[MaxHero];//应该没用
public:
	//ChessShop* chessShop;
    //Player(ChessShop* shop);

	//血量减少
	void changeplayerBlood(int hurt);

	////获取金币数量
	//int getplayerMoney() const;

	////改变金币数量
	//void changeplayerMoney(int num);

	////购买经验
	//bool buyplayerExperience();

	////判断提升等级
	//bool changeplayerLevel(int exp=0);

	////卖出（只能从备战区卖）
	//void sellMyChess(Hero* chess);

	////买入
	//bool buyMyChess(Hero* chess);

	////更新商店
	//bool Update();
	Player();

	static Player* create();

	void SetHP(Vec2 pos);

	int GetLv();

	void SetHero(Hero* hero);//设置上场英雄，里面是测试用数据

	void HeroInit();//英雄初始化

	Hero* GetWarHero();//传出上场英雄

	bool IsDead() {
		return playerIsDead;
	}

	int GetHeroNum();
};


#endif

