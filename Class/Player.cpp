#include "Player.h"

//Player::Player(ChessShop* shop) : chessShop(shop)
//{
//	playerIsDead = false;
//	playerBlood = initplayerBlood;
//	//playerMoney = 4;
//	//待修改
//	playerMoney = 1000;
//	playerLevel = playerMaxNumChess = 1;
//	playerExperience = 0;
//	playerNeedExperience = addMaxExperience;
//}
//
void Player::changeplayerBlood(int hurt)
{
	playerBlood -= hurt;
    myHP->setCurrentProgress(playerBlood);
	if (playerBlood <= 0)
	{
		playerIsDead = true;//玩家死亡
	}
}
//
//int Player::getplayerMoney() const
//{
//	return playerMoney;
//}
//
//void Player::changeplayerMoney(int num)
//{
//	playerMoney = num;
//}
//
//bool Player::buyplayerExperience()
//{
//	if (playerMoney < addExperience)
//	{
//		return false;
//	}//钱不够
//
//	playerMoney -= addExperience;
//	playerExperience += addExperience;
//	changeplayerLevel(0);
//
//	return true;
//}
//
//bool Player::changeplayerLevel(int exp)
//{
//	playerExperience += exp;
//
//	while (playerExperience >= playerNeedExperience)
//	{
//		playerExperience -= playerNeedExperience;
//		playerLevel++;
//		playerNeedExperience += addExperience;
//		playerMaxNumChess++;
//	}
//
//	return true;
//}
//
//void Player::sellMyChess(Hero* chess)
//{
//	playerMoney+= chessShop->SellChess(chess);
//	chessPlayer.erase(remove(chessPlayer.begin(), chessPlayer.end(), chess), chessPlayer.end());
//	chessPreparePlayer.erase(remove(chessPlayer.begin(), chessPlayer.end(), chess), chessPlayer.end());
//	delete chess;
//}
//
//bool Player::buyMyChess(Hero* chess)
//{
//	//备战区棋子加上场的
//	if (!chessShop->BuyChess(chess, playerMoney, playerMaxNumChess + 6, chessPlayer.size()))
//	{
//		return false;
//	}
//	else 
//	{
//		chessPlayer.push_back(chess);
//		if (chessPreparePlayer.size() < 6)
//		{
//			chessPreparePlayer.push_back(chess);
//		}
//		else
//		{
//			chessWarPlayer.push_back(chess);
//		}
//		
//		return true;
//	}
//}
//
//bool Player::Update() 
//{
//	if (playerMoney >= 2)
//	{
//		playerMoney -= 2;
//		chessShop->getFiveChess();
//		return true;
//	}
//	return false;
//}

///////////////////////////////////
// ////////////
//添加了以下成员函数

Player* Player::create()
{
    Player* sprite = new (std::nothrow) Player();
    if (sprite)
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

Player::Player() {
    playerLevel = 2;
    playerIsDead = 0;
    playerBlood = 100;
    HeroInit();
}

void Player::SetHP(Vec2 pos) {
    //血条初始化
    myHP = new showHPMP();
    myHP->setPosition(pos);
    myHP->setBackgroundTexture("Blood-back.png");
    myHP->setForegroundTexture("LiliaBlood-front.png");
    myHP->setTotalProgress(playerBlood);
    myHP->setCurrentProgress(playerBlood);
    myHP->setScale(1.2);
    this->getParent()->addChild(myHP, 2);
}

int Player::GetLv() {
    return playerLevel;
}

void Player::SetHero(Hero* hero) {
    chessWarPlayer[heroNum].SetBaseInfo(hero->GetBaseInfo(),hero->GetName(),hero->GetHeroPos());
    //chessWarPlayer.onBattle[chessWarPlayer.heroNum].SetHeroOn();
    chessWarPlayer[heroNum].SetOn(1);
    heroNum++;
}

void Player::HeroInit(){
}

class Hero* Player::GetWarHero() {
    return chessWarPlayer;
}

int Player::GetHeroNum() {
    return heroNum;
}