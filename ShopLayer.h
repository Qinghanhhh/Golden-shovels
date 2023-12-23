#pragma once
#include"card.h"
#include"cocos2d.h"
using namespace cocos2d;
#include<vector>

class ShopLayer : public cocos2d::Layer {
public:
    static ShopLayer* createLayer();
    virtual bool init()override;
    CREATE_FUNC(ShopLayer);

    static Sprite* shopBackground;

    void createShopBackground();

    void createItemPlace();
    void displayCards();//展示卡牌
    void createRefreshButton();//刷新按钮
    void refreshShop(Ref* pSender);//回调函数
    void createMoneyButton();//金币相关
    void addCardTouchListener(Card* card);

private:
    Vector<Card*> currentCards; // 存储卡牌的向量
   
};