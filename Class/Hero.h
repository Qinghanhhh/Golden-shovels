#pragma once
#ifndef __HERO_H__  
#define __HERO_H__  
#include "showHPMP.h"
#include "Attack.h"
#include "cocos2d.h"  
using namespace cocos2d;

//英雄（卡牌）基础信息
class showHPMP;
class Attack;
struct heroInformation {
	
	float HP;                 //生命值
	float MP;                 //法力值
	float attack;            //攻击力
	float atkspeed;          //攻击速度(每几秒攻击一次)
	float defence;           //防御力
	float atkrange;          //攻击距离
	float movespeed;         //移动速度
	double attackSpeed;//攻击物飞行速度
};

class Hero :public cocos2d::Sprite
{
public:
	Hero();
	static Hero* create(const std::string& filename);
	void SetBaseInfo(heroInformation* info, std::string name,Vec2 pos);//设置英雄初始信息
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
	virtual	void update(float dt);//每一帧更新一次英雄状态
	void Destory();

	heroInformation* GetBaseInfo();
	std::string GetName();
	Vec2 GetHeroPos();
private:
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

//
//class Chess : public cocos2d::Sprite
//{
//public:
//	CREATE_FUNC(Chess);
//	virtual bool init();
//	static Chess* create(const std::string& filename);
//	double ShowHp();
//	double ShowAtk();
//	double ShowAtkSpeed();
//	double ShowMoveSpeed();
//	double ShowDef();
//	double ShowAtkRange();
//	double ShowFlySpeed();
//	int IsDead();
//	int IsOn();
//	std::string ShowName();
//	void SetHp(double data);
//	void SetAtk(double data);
//	void SetAtkSpeed(double data);
//	void SetMoveSpeed(double data);
//	void SetDef(double data);
//	void SetAtkRange(double data);
//	void SetName(std::string data);
//	void SetFlySpeed(double data);
//	double SetAtkTimer(double data);
//	double SetMoveTimer();
//	void SetAtkMark();
//	void SetMovemark();
//	void SetMoveTime();
//	void AtkTargetInit(Chess* data);
//	double CountTheDistance(Vec2 position1, Vec2 position2);//计算两个坐标之间的距离
//	void SetDead(int);
//	void SetOn(int);
//	void PointInit();
//	void AttackTo(Vec2 position);//生成攻击物移动至目标位置，可能需求写一个攻击物类，参照本类写法，攻击物类应有攻击物的飞行速度
//	void AttackTarget();//攻击函数，传入一个目标棋子的指针，获取目标棋子的位置，调用上面的函数生成一个攻击物移动至目标棋子位置，到达后目标旗子扣血
//	void ReduceHp(double atk);
//	void Reverse(int);
//	void MoveTo(Vec2 position);//棋子移动至目标位置
//	void MoveTarget(Chess* target);//根据目标棋子位置决定要移动到的位置
//	void Test(cocos2d::Ref* pSender);//用于调试的回调函数
//	virtual	void update(float dt);
//	Chess* ShowTarget();
//	void destroy();//销毁update的包装方法
//	void setdatafromcard();
//	void setatkptrimage();
//private:
//	double healthpoint;       //HP
//	double attack;            //攻击力
//	double atkspeed;          //攻击速度
//	double movespeed;         //移动速度
//	double defence;           //防御力
//	double atkrange;          //攻击距离
//	double flyspeed;          //攻击物的飞行速度
//	std::string name;         //卡牌名
//	Attack* p_attack;         //攻击物指针
//	double standard_atktimer;    //计数器标准//atktimer=atkspeed*60;
//	double standard_movetimer;   //计数器//
//	double atktimer;             //真正实现计时器功能
//	double movetimer;
//	int atkmark;              //记录是否在攻击//0代表未攻击 1代表攻击中
//	int movemark;             //记录是否在移动//0代表未移动 1代表移动中
//	double move_time;        //移动需要花费的时间//记得初始化
//	Chess* atktarget;         //存放目标棋子
//	/// /////////////////////////////////////////////////////////////////////
//	int isdead;               //记录是否死亡
//	int ison;                 //记录是否上场
//	int isupdate = 0;       //记录是否在执行update
//};



#endif  