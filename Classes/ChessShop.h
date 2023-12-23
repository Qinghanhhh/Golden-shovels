#ifndef  _CHESS_SHOP_H_
#define  _CHESS_SHOP_H_

#include "ChessPool.h"
#include "cocos2d.h"

USING_NS_CC;

//�̵���
class ChessShop : public cocos2d::Layer
{
private:
	//����
	ChessPool* chessPool;
public:
	ChessShop(ChessPool* pool);

	//static Scene* creatScene(){}

	virtual bool init() { return true; }

	//������������
	vector<Chess*> displayFiveChess;

	//�����̵���
	void getFiveChess();

	//�������ӣ��������ý��ֵ
	int SellChess(Chess* chess);

	//������,��Ҽ���
	bool BuyChess(Chess* chess, int& money, int maxChess, int nowChess);
};


#endif

