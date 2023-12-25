#ifndef __SMALL_HERO_H__  
#define __SMALL_HERO_H__ 

#include "cocos2d.h" 
#include "showHPMP.h"
#include "ui/CocosGUI.h"

#include <string>  

using namespace cocos2d;
using std::string;
USING_NS_CC;

class Click;

//每次提升加 4 经验
const int addExperience = 4;
//升级最大经验值加 4
const int addMaxExperience = 4;

class SmallHero : public Sprite
{
public:
	virtual bool init();
	static SmallHero* create();//创建英雄
	void SetBaseInfo(string name, Vec2 pos);//设置英雄初始信息
	Vec2 onMouseUp(Event* event);//得到英雄的目标位置
	void handleMouseClick(const Vec2& clickPos);
	void smallHeroMoveTo(const Vec2& clickPos);//英雄移动到指定位置
	void StopMove(Ref* obj);//回调函数，停止所有动作
	void ChangeHP(float data);//受到攻击减少血量或得到治疗恢复血量
	bool IsDead();

	//CREATE_FUNC(SmallHero);

	virtual	void update(float dt);//每一帧更新一次英雄状态
private:
	string smallHeroName;//卡牌名，图片名称
	Vec2 smallHeroPos;//英雄位置
	showHPMP* heroHP;//显示英雄的血条
	bool isdead;//是否死亡
	bool ismove;//是否正在移动
	bool isupdate;//是否在update
	int HP;//玩家血量
	int money;//金币
	int Level;//玩家等级
	int needExperience;//提升到下一级需要多少经验
};

#endif  