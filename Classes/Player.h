#ifndef  _PLAYER_H_
#define  _PLAYER_H_

#include "ChessShop.h"
#include "cocos2d.h"

USING_NS_CC;

//初始血量
constexpr int initplayerBlood = 100;
//每次提升加 4 经验
constexpr int addExperience = 4;
//升级最大经验值加 4
constexpr int addMaxExperience = 4;

class Player : public cocos2d::Scene
{
private:
	//还活着吗
	bool playerIsDead;

	//玩家血量
	int playerBlood;

	//金币
	int playerMoney;

	//玩家等级
	int playerLevel;

	//提升到下一级需要多少经验
	int playerNeedExperience;

	//可以上场的棋子数量
	int playerMaxNumChess;

	//玩家经验
	int playerExperience;

	//玩家棋子
	vector<Chess*> chessPlayer;

	//玩家备战区棋子
	vector<Chess*> chessPreparePlayer;

	//玩家上场棋子
	vector<Chess*> chessWarPlayer;
public:
	ChessShop* chessShop;
    Player(ChessShop* shop);

	//血量减少
	void changeplayerBlood(int hurt);

	//获取金币数量
	int getplayerMoney() const;

	//改变金币数量
	void changeplayerMoney(int num);

	//购买经验
	bool buyplayerExperience();

	//判断提升等级
	bool changeplayerLevel(int exp=0);

	//卖出（只能从备战区卖）
	void sellMyChess(Chess* chess);

	//买入
	bool buyMyChess(Chess* chess);

	//更新商店
	bool Update();
};


#endif

