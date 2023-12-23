#ifndef  _CHESS_SHOP_H_
#define  _CHESS_SHOP_H_

#include "ChessPool.h"
#include "cocos2d.h"

USING_NS_CC;

//商店类
class ChessShop : public cocos2d::Layer
{
private:
	//卡池
	ChessPool* chessPool;
public:
	ChessShop(ChessPool* pool);

	//static Scene* creatScene(){}

	virtual bool init() { return true; }

	//待买的五个棋子
	vector<Chess*> displayFiveChess;

	//更新商店区
	void getFiveChess();

	//卖出棋子，返回所得金币值
	int SellChess(Chess* chess);

	//买棋子,金币减少
	bool BuyChess(Chess* chess, int& money, int maxChess, int nowChess);
};


#endif

