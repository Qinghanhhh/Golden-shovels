#include "Attack.h"

bool Attack::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	isHit = 0;
	attack = 100;
	return true;
}

//创建攻击物，初始化攻击物图片
Attack* Attack::create(const std::string& filename)
{
	Attack* sprite = new (std::nothrow) Attack();
	if (sprite && sprite->initWithFile(filename + "-attack.png"))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Attack::SetPosition(Vec2 pos,Size heroSize) {//应该要根据英雄名称进行分类讨论
	this->setPosition(pos.x + heroSize.width / 2-23, pos.y + heroSize.height / 2 - 10);//10是调整值
}

void Attack::SetTarget(Hero* atktarget)
{
	target = atktarget;
	targetPos.x = target->getPosition().x;
	targetPos.y = target->getPosition().y;
	MoveTo* attackMoveTo = MoveTo::create(1.3, targetPos);
	this->runAction(attackMoveTo);
	//this->scheduleUpdate();
	if (isHit == 0)
		this->schedule(schedule_selector(Attack::timer), 0.01f);
}


void Attack::timer(float delta) {//这段代码每0.05s执行一次
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();//获取屏幕的尺寸、位置信息等
	//this->setPositionY(this->getPositionY() + 2);//按钮精灵向右移动2像素
	GetDistance();
	//if (present_position == target_position)
	if (distance <= 1){//如果按钮精灵超过屏幕的1/4
		if (!isHit) {
			isHit = 1;//设为已命中
			target->ChangeHP(attack);//target攻击目标是一个Hero类
			this->setVisible(false);//让攻击物消失
			this->unschedule(schedule_selector(Attack::timer));
		}
	}
}

void Attack::GetAttack(double atk)
{
	attack = atk;
}

void Attack::GetDistance() {
	Vec2 currentPos = this->getPosition();
	Vec2 targetPos = target->getPosition();
	//当前位置与目标攻击位置的距离
	distance = sqrt(pow(targetPos.x - currentPos.x, 2) + pow(targetPos.y - currentPos.y, 2));
}

void Attack::update(float dt)//更新攻击物状态
{
	GetDistance();
	//if (present_position == target_position)
	if (distance <= 1)
	{
		isHit = 1;//设为已命中
		target->ChangeHP(attack);//target攻击目标是一个Hero类
		this->unscheduleUpdate();
		this->setVisible(false);//让攻击物消失
	}
}
void Attack::destroy()
{
	if (isHit)
	{
		this->unscheduleUpdate();
		isHit = 0;
	}
}
