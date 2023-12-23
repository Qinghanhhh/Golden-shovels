#include "ChessShop.h"

ChessShop::ChessShop(ChessPool* pool)
{
    chessPool = pool;
}

void ChessShop::getFiveChess()
{
	//清空商店5个卡牌
	if (!displayFiveChess.empty())
	{
		for (Chess* ptr : displayFiveChess)
		{
			if (ptr != nullptr) 
			{
				chessPool->AddChess(ptr);
				delete ptr; //释放内存
			}
			
		}
	}
	displayFiveChess.clear();

	for (int i = 0; i < 5; i++)
	{
		displayFiveChess.push_back(chessPool->DrawChess());
	}
}


int ChessShop::SellChess(Chess* chess)
{
	chessPool->AddChess(chess);
	return chess->GetchessData().chessPrice;
}

bool ChessShop::BuyChess(Chess* chess, int& money, int maxChess, int nowChess)
{
	//钱不够买不起
	if (money < chess->GetchessData().chessPrice)
	{
		return false;
	}
	//没地方放不能买
	else if (maxChess <= nowChess)
	{
		return false;
	}
	else
	{
		money -= chess->GetchessData().chessPrice;
		return true;
	}
}
