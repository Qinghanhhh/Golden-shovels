#include "ChessShop.h"

ChessShop::ChessShop(ChessPool* pool)
{
    chessPool = pool;
}

void ChessShop::getFiveChess()
{
	//����̵�5������
	if (!displayFiveChess.empty())
	{
		for (Chess* ptr : displayFiveChess)
		{
			if (ptr != nullptr) 
			{
				chessPool->AddChess(ptr);
				delete ptr; //�ͷ��ڴ�
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
	//Ǯ��������
	if (money < chess->GetchessData().chessPrice)
	{
		return false;
	}
	//û�ط��Ų�����
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
