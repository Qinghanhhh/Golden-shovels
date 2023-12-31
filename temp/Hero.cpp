#include "Hero.h"
#include"Information.h"
#include<string>
using namespace std;
USING_NS_CC;

Hero::Hero() {

    atkTarget = NULL;//攻击的敌方目标英雄
    ison = 0;//是否上场
    isdead = 0;//是否死亡
    isatk = 0;//是否正在攻击
    ismove = 0;//是否正在移动
    isrecover = 0;
    isFull = 0;//蓝条是否已满（是否释放大招）
    isupdate = 0;//是否在update
    moveAction = NULL;//移动动作序列
    attackAction = NULL;//攻击动作序列

}

void Hero::upgrade()
{
    if (level < 4) {
        level++;
        // 更新星级显示
        updateStarLevel();

        heroInformation* attributes = Information::getheroInformation(this->getTag(), level);
        if (attributes) {
            // 使用新的属性更新英雄
            baseInfo->HP=attributes->HP;
            baseInfo->HP=attributes->attack;
            // ... 更新其他属性 ...

            // 释放 attributes 对象以避免内存泄漏
            delete attributes;
        }

        
    }
}


int Hero::getLevel() const {
    return level;
}

void Hero::setLevel(int x)
{
    level = x;
}

void Hero::updateStarLevel()
{
    string StarList[4] = { "star1.png","star2.png","star3.png","star4.png" };
    // 清除旧的星星精灵
    this->removeAllChildren();
    string starFileName = StarList[this->level - 1];
    auto star = Sprite::create(starFileName);
    if (star) {
        float spacing = 15.0f;
        float CardWidth = this->getContentSize().width;
        float CardHeight = this->getContentSize().height;
        float posY =this->getPositionY() / 10;
        float posX = this->getPositionX() / 50;
        //大小
        if (level == 1)
            star->setScale(0.1, 0.1);
        else
            star->setScale(0.15, 0.15);
        //位置
        star->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        Vec2 StarPosition = this->getPosition();
        star->setPosition(posX, posY);
        this->addChild(star, 0);
    }
}



Hero* Hero::create(const std::string& filename)
{
    Hero* sprite = new (std::nothrow) Hero();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void Hero::SetBaseInfo(heroInformation* info, std::string name, Vec2 pos) {
    baseInfo = info;
    heroName = name;
    heroPos = pos;
    this->setTexture(heroName + "-action1.png");
    this->setVisible(0);
}

//void Hero::HPInit() {
//    heroHP = showHPMP::create();
//    this->getParent()->addChild(heroHP, 5);
//    heroMP = showHPMP::create();
//    this->getParent()->addChild(heroMP, 5);
//}

