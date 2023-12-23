#include "Hero.h"
USING_NS_CC;

bool Hero::init()
{
    if (!Sprite::init())//若初始化失败，返回0
    {
        return false;
    }
    heroAttack = Attack::create();
    this->getParent()->addChild(heroAttack);//相当于把攻击物加为英雄的兄弟
    heroHP = showHPMP::create();
    this->getParent()->addChild(heroHP);
    heroMP = showHPMP::create();
    this->getParent()->addChild(heroMP);
}

Hero* Hero::create()
{
    Hero* sprite = new (std::nothrow) Hero();
    if (sprite)
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Hero::SetBaseInfo(heroInformation* info, std::string name,Vec2 pos) {
    baseInfo = info;
    heroName = name;
    heroPos = pos;
    this->setTexture(heroName + "action1.png");
    this->setVisible(0);
}

void Hero::SetHeroOn() {
    if (ison) {
        this->setPosition(heroPos);
        //血条初始化
        Vec2 posBlood;
        posBlood.x = heroPos.x;
        posBlood.y = heroPos.y + this->getContentSize().height / 2 + 8;
        heroHP->setPosition(posBlood);
        heroHP->setScale(2.2f);
        heroHP->setBackgroundTexture("Blood-back.png");
        heroHP->setForegroundTexture("Blood-front.png");
        heroHP->setTotalProgress(baseInfo->HP);
        heroHP->setCurrentProgress(baseInfo->HP);
        heroHP->setScale(0.8);
        //蓝条初始化
        Vec2 posMP;
        posMP.x = heroPos.x;
        posMP.y = posBlood.y - 14;
        heroMP->setPosition(posMP);
        heroMP->setScale(2.2f);
        heroMP->setBackgroundTexture("MP-back.png");
        heroMP->setForegroundTexture("MP-front.png");
        heroMP->setTotalProgress(baseInfo->MP);
        heroMP->setCurrentProgress(0.0f);
        heroMP->setScale(0.8);
        //英雄设为可见
        this->setVisible(1);
    }
}

//初始化移动和攻击动画
void Hero::SetAciton() {
    //设置攻击动作
    Vector<SpriteFrame*>spriteFrameVec;
    for (int i = 1; i <= 2; i++) {
        char imageName[20];
        sprintf(imageName, "-attack%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(heroName+imageName, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
        spriteFrameVec.pushBack(spriteFrame);
    }
    Animation* ani = Animation::createWithSpriteFrames(spriteFrameVec, 0.5);
    attackAction = Animate::create(ani);
    //设置移动动作
    Vector<SpriteFrame*>spriteFrameVec2;
    for (int i = 1; i <= 2; i++) {
        char imageName[20];
        sprintf(imageName, "-move%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(heroName + imageName, Rect(0, 0, this->getContentSize().width, this->getContentSize().height));
        spriteFrameVec2.pushBack(spriteFrame);
    }
    Animation* ani2 = Animation::createWithSpriteFrames(spriteFrameVec2, 0.5);
    moveAction = Animate::create(ani2);
}

//得到的应该是战斗场某个格子的中心位置
Vec2 Hero::GetTargetPos() {
    Vec2 enemyPos = atkTarget->getPosition();
    double distance = CountDistance();
    Vec2 direction = Vec2(enemyPos.x - heroPos.x, enemyPos.y - heroPos.y) / distance;
    Vec2 tarPos;
    if (distance - baseInfo->atkrange > 0)
        tarPos = direction * (distance - baseInfo->atkrange) + heroPos;
    return tarPos;
}

//移动到指定位置
void Hero::HeroMoveTo() {
    Vec2 pos = GetTargetPos();
    double time = CountDistance() / baseInfo->movespeed;
    this->runAction(moveAction);//开始移动动作
    MoveTo* moveTo = MoveTo::create(time,pos);
    Sequence* seq = Sequence::create(moveTo, CallFuncN::create(CC_CALLBACK_1(Hero::StopMove, this)), NULL);
    this->runAction(seq);
}

//停止动作
void Hero::StopMove(Ref* obj) {
    this->stopAllActions();
    this->setTexture(heroName +"-action1.png");
    ismove = 0;
}

void Hero::StopAttack(Ref* obj) {
    this->stopAllActions();
    this->setTexture(heroName + "-action1.png");
    isatk = 0;
}

//计算英雄位置到攻击目标的位置
double Hero::CountDistance() {
    Vec2 pos1 = heroPos;
    Vec2 pos2 = atkTarget->getPosition();
    return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}

void Hero::HeroAttack(float t) {
    this->runAction(attackAction);//开始攻击动作
    heroAttack->SetPosition(heroPos,this->getContentSize());
    heroAttack->setVisible(1);
    float flyTime = CountDistance() / attackSpeed;

    //攻击物计时器
    heroAttack->SetTarget(atkTarget);//告诉攻击物攻击目标
    heroAttack->scheduleUpdate();//运行attack内部的update，更新攻击物的状态

    //攻击物开始飞行
    MoveTo* attackMoveTo = MoveTo::create(flyTime,atkTarget->getPosition());
    heroAttack->runAction(attackMoveTo);
}

void Hero::ChangeHP(float data) {
    heroHP->setCurrentProgress(heroHP->getCurrentProgress() - data + baseInfo->defence);
    baseInfo->HP = heroHP->getCurrentProgress();
}

void Hero::ChangeMP(float data) {
    if(!isFull)
    heroMP->setCurrentProgress(heroMP->getCurrentProgress() + 10);
}

void Hero::update(float dt)
{
    if (baseInfo->HP <= 0)
    {
        this->isdead = 1;//死亡
        this->setVisible(0);//或许更改为淡出会更好，视后期效果而定
    }

    if (isdead)//如果死了就停止攻击
    {
        isatk = 0;
        heroAttack->setVisible(0);
        this->unscheduleUpdate();//停止该英雄的所有定时器
    }
    //棋子不在移动
    if (!ismove)
    {
        //若攻击目标在攻击范围内则发动攻击
        if (CountDistance() <= baseInfo->atkrange )//或许需要加一个可允许的误差值，先将所有英雄图片大小弄成一样的看看能不能避免误差
        {
            if (!isatk) {
                isatk = 1;//设置攻击状态为正在攻击//isatk何时置零？
                this->schedule(schedule_selector(Hero::HeroAttack), baseInfo->atkspeed);//每隔相应秒数发动攻击
            }
            //////////////////////////////
        }

        //目标不在攻击范围内＆棋子不移动
        else
        {
            if (!isatk) {
                ismove = 1;//标记正在移动
                heroAttack->setVisible(0);//移动状态，隐藏攻击物
                HeroMoveTo();//移动到能够发动攻击的位置
            }
            else {//如果不在攻击范围内仍在攻击
                isatk = 0;
            }
        }
    }
    isupdate = 1;
}

bool Hero::IsDead() {
    return isdead;
}