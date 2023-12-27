#pragma once
#include"card.h"
#include"cocos2d.h"
using namespace cocos2d;
#include<vector>

class ShopLayer : public cocos2d::Layer {
public:
    //卡池
    vector<Chess*> chessPool;

    //卡池
        //初始化函数
    void InitChessPool();

    //移除卡池
    Chess* DrawChess();

    //加入卡池
    void AddChess(Chess* chess);

    // 打乱卡池顺序
    void ShufflePool();
    static ShopLayer* createLayer();

    //待买的五个棋子
    vector<Chess*> displayFiveChess;
    //更新商店区
    void getFiveChess();

    //卖出棋子，返回所得金币值
    int SellChess(Chess* chess);

    //买棋子,金币减少
    bool BuyChess(Chess* chess, int& money, int maxChess, int nowChess);

    virtual bool init()override;
    CREATE_FUNC(ShopLayer);

    static Sprite* shopBackground;

    void createShopBackground();

    void createItemPlace();
    void displayCards();//展示卡牌
    void createRefreshButton();//刷新按钮
    void refreshShop(Ref* pSender);
    void displayMoney();
    //回调函数
    void createMoneyButton();//金币相关
    void addCardTouchListener(Card* card);

private:

    Vector<Card*> currentCards; // 存储卡牌的向量
   
};