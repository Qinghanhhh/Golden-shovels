#include "Player.h"

Player::Player(ChessShop* shop) : chessShop(shop)
{
	playerIsDead = false;
	playerBlood = initplayerBlood;
	//playerMoney = 4;
	//待修改
	playerMoney = 1000;
	playerLevel = playerMaxNumChess = 1;
	playerExperience = 0;
	playerNeedExperience = addMaxExperience;
}

void Player::changeplayerBlood(int hurt)
{
	playerBlood -= hurt;
	if (playerBlood <= 0)
	{
		playerIsDead = true;//玩家死亡
	}
}

int Player::getplayerMoney() const
{
	return playerMoney;
}

void Player::changeplayerMoney(int num)
{
	playerMoney = num;
}

bool Player::buyplayerExperience()
{
	if (playerMoney < addExperience)
	{
		return false;
	}//钱不够

	playerMoney -= addExperience;
	playerExperience += addExperience;
	changeplayerLevel(0);

	return true;
}

bool Player::changeplayerLevel(int exp)
{
	playerExperience += exp;

	while (playerExperience >= playerNeedExperience)
	{
		playerExperience -= playerNeedExperience;
		playerLevel++;
		playerNeedExperience += addExperience;
		playerMaxNumChess++;
	}

	return true;
}

void Player::sellMyChess(Chess* chess)
{
	playerMoney+= chessShop->SellChess(chess);
	chessPlayer.erase(remove(chessPlayer.begin(), chessPlayer.end(), chess), chessPlayer.end());
	chessPreparePlayer.erase(remove(chessPlayer.begin(), chessPlayer.end(), chess), chessPlayer.end());
	delete chess;
}

bool Player::buyMyChess(Chess* chess)
{
	//备战区棋子加上场的
	if (!chessShop->BuyChess(chess, playerMoney, playerMaxNumChess + 6, chessPlayer.size()))
	{
		return false;
	}
	else 
	{
		chessPlayer.push_back(chess);
		if (chessPreparePlayer.size() < 6)
		{
			chessPreparePlayer.push_back(chess);
		}
		else
		{
			chessWarPlayer.push_back(chess);
		}
		
		return true;
	}
}

bool Player::Update() 
{
	if (playerMoney >= 2)
	{
		playerMoney -= 2;
		chessShop->getFiveChess();
		return true;
	}
	return false;
}