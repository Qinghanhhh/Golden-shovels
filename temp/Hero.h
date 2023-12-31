#pragma once
 
//#include "showHPMP.h"
//#include "Attack.h"
#include "cocos2d.h"  
#include"Information.h"
using namespace cocos2d;

//英雄（卡牌）基础信息
class showHPMP;
class Attack;

class Hero :public cocos2d::Sprite
{
public:
	Hero();

	void Hero::upgrade();

	int getLevel() const;
	void setLevel(int x);

	void updateStarLevel();  // 更新星级显示的方法

	static Hero* create(const std::string& filename);
	void SetBaseInfo(heroInformation* info, std::string name, Vec2 pos);//设置英雄初始信息
	void HPInit();
	void SetHeroOn();//设置英雄上场，包括血条初始化，根据heroPos设置位置
	void SetAction();//初始化移动和攻击动作序列
	Vec2 GetTargetPos();//根据攻击目标得到英雄的战斗位置
	void Movetimer(float delta);
	void HeroMoveTo();//英雄移动到指定位置，包括移动动画的实现（提供移动时间，目标位置）
	void StopMove(Ref* obj);//回调函数，停止所有动作
	void StopAttack(Ref* obj);//回调函数，停止所有动作
	void StartBattle(Hero* target);
	void HeroAttack();//开始攻击动作
	void ChangeHP(float data);//受到攻击减少血量或得到治疗恢复血量
	void ChangeMP();//回蓝，暂时写一个普攻回蓝的简单机制
	void ChangeHPColor();
	double GetAtk();
	bool IsDead();
	bool IsOn();
	bool IsRecover();
	void SetRecover();
	void SetOn(int data);
	void SetDead(int data);
	Hero* ShowTarget();
	double CountDistance();
	CREATE_FUNC(Hero);
	//virtual	void update(float dt);//每一帧更新一次英雄状态
	void Destory();

	heroInformation* GetBaseInfo();
	std::string GetName();
	Vec2 GetHeroPos();
private:
	int level;  // 英雄的等级
	cocos2d::Sprite* starSprite;  // 星级表示的精灵

	std::string heroName;         //卡牌名，图片名称
	heroInformation* baseInfo;
	Vec2 heroPos;//英雄位置
	showHPMP* heroHP;//显示英雄的血条
	showHPMP* heroMP;//显示英雄的蓝条
	Attack* heroAttack;//该英雄的攻击物指针
	Hero* atkTarget;//攻击的敌方目标英雄
	bool ison;//是否上场
	bool isdead;//是否死亡
	bool isatk;//是否正在攻击
	bool ismove;//是否正在移动
	bool isFull;//蓝条是否已满（是否释放大招）
	bool isupdate;//是否在update
	bool isrecover;//是否为队友恢复血量
	Animate* moveAction;//移动动作序列
	Animate* attackAction;//攻击动作序列
	float atktimer;//攻击计时器
	float curAtkTimer;//记录当前时间的计时器
	float movetime;//移动需要的时间
	float movetimer;//移动计时器
	float curMoveTimer;//记录当前时间的计时器
	float moveActTimer;
	float curMoveActTimer;
	Vec2 direction;
};
