#include "Attack.h"

bool Attack::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	isHit = 0;
	return true;
}

//创建攻击物，初始化攻击物图片
Attack* Attack::create(const std::string& filename)
{
	Attack* sprite = new (std::nothrow) Attack();
	if (sprite && sprite->initWithFile(filename + "attack.png"))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Attack::SetPosition(Vec2 pos,Size heroSize) {//应该要根据英雄名称进行分类讨论
	this->setPosition(pos.x + heroSize.width / 2, pos.y + heroSize.height / 2 - 10);//10是调整值
}

void Attack::SetTarget(Hero* atktarget)
{
	target = atktarget;
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
		isHit = 0;
		target->ReduceHp(attack);//target攻击目标是一个Hero类
		this->unscheduleUpdate();
		this->setVisible(false);//让攻击物消失
	}
}
