#pragma once
/*
* 文件名称：Chess.h
* 功能：棋子基本功能
*
* 作者：fbr
*
*
*/

#ifndef  _CHESS_H_
#define  _CHESS_H_

#include <string>
#include <vector>

#include "cocos2d.h"

using std::string;
using std::vector;

USING_NS_CC;

constexpr int CHESSTYPENUM = 14;

struct ChessData
{
	//生命值
	int HP[4];
	//法力值
	int MP;
	//攻击力
	int ATK[4];
	//攻击速度
	double AttackSpeed;
	//攻击距离
	int AttackRange;
	//物理防御
	int physicalDefense;
	//魔法防御
	int magicDefense;
	//棋子价格
	int chessPrice;
};


//棋子基类
class Chess : public cocos2d::Ref
{
protected:
	//棋子名称
	string chessName;
	int chessNameTag;

	//棋子职业名称
	string chessOccupation;

	//棋子等级==1/2/3
	int chessLevel;

	ChessData chessData;

	//图片路径
	string chessImage;

public:
	//初始化函数
	void InitChess();

	//返回棋子
	string GetchessName() const;
	int GetchessNameTag() const;
	string GetchessOccupation() const;
	int GetchessLevel()const;
	ChessData GetchessData() const;
	void setchessImage(const string& imagePath);
	string getchessImage();
};



//各个职业实现

//法师类
class Mage :public Chess
{
private:
	string chessOccupation = "法师";
public:
	//初始化
	Mage(string name);

};

//射手类
class Shooter :public Chess
{
private:
	string chessOccupation = "射手";
public:
	//初始化
	Shooter(string name);

};

//战士类
class Warrior :public Chess
{
private:
	string chessOccupation = "战士";
public:
	//初始化
	Warrior(string name);

};

//辅助类
class Support :public Chess
{
private:
	string chessOccupation = "辅助";
public:
	//初始化
	Support(string name);

};

#endif