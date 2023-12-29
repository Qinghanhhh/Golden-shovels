#include "Chess.h"

void Chess::InitChess()
{
	chessLevel = 1;
}

string Chess::GetchessName() const
{
	return chessName;
}

int Chess::GetchessNameTag() const
{
	return chessNameTag;
}

string Chess::GetchessOccupation() const
{
	return chessOccupation;
}

ChessData Chess::GetchessData() const
{
	return chessData;
}

int Chess::GetchessLevel()const
{
	return chessLevel;
}

void Chess::setchessImage(const string& imagePath)
{
	chessImage = imagePath;
}

string Chess::getchessImage()
{
	return chessImage;
}


//法师类
Mage::Mage(string name)
{
	chessName = name;
	if (chessName == "伊芙琳")
	{
		chessNameTag = 1;
		chessData = { {0,550,990,1782},60,{0,45,68,101},0.7,3,35,35,1 };
		chessImage = "Mage1.png";
	}
	else if (chessName == "安妮")
	{
		chessNameTag = 2;
		chessData = { {0,450,810,1458},50,{0,40,60,90},0.65,4,20,20,2 };
		chessImage = "Mage2.png";
	}
	else if (chessName == "卡特琳娜")
	{
		chessNameTag = 3;
		chessData = { {0,650,1170,2106},60,{0,40,60,90},0.7,2,35,35,2 };
		chessImage = "Mage3.png";
	}
	else if (chessName == "阿狸")
	{
		chessNameTag = 4;
		chessData = { {0,700,1260,2268},30,{0,40,60,90},0.8,4,30,30,3 };
		chessImage = "Mage4.png";
	}
}

//战士类
Warrior::Warrior(string name)
{
	chessName = name;
	if (chessName == "奥拉夫")
	{
		chessNameTag = 5;
		chessData = { {0,650,1170,2106},0,{0,50,75,113},0.65,1,45,45,1 };
		chessImage = "Warrior1.png";
	}
	else if (chessName == "塔姆")
	{
		chessNameTag = 6;
		chessData = { {0,650,1170,2106},0,{0,60,90,135},0.55,1,45,45,1 };
		chessImage = "Warrior2.png";
	}
	else if (chessName == "瑟提")
	{
		chessNameTag = 7;
		chessData = { {0,950,1710,3078},60,{0,55,83,124},0.7,1,45,45,2 };
		chessImage = "Warrior3.png";
	}
	else if (chessName == "锤石")
	{
		chessNameTag = 8;
		chessData = { {0,1000 ,1800 ,3240},120,{0,60,90,135},0.65,1,60,60,3 };
		chessImage = "Warrior4.png";
	}
}

//射手类
Shooter::Shooter(string name)
{
	//待修改
	chessName = name;
	if (chessName == "射手1")
	{
		chessNameTag = 9;
		chessData = { {0,0,0,0},0,{0,0,0,0},0,0,0,0,0 };
		chessImage = "Warrior1.png";
	}
	else if (chessName == "射手2")
	{
		chessNameTag = 10;
		chessData = { {0,0,0,0},0,{0,0,0,0},0,0,0,0,0 };
		chessImage = "Warrior1.png";
	}
	else if (chessName == "射手3")
	{
		chessNameTag = 11;
		chessImage = "Warrior1.png";
		chessData = { {0,0,0,0},0,{0,0,0,0},0,0,0,0,0 };
	}
	else if (chessName == "射手4")
	{
		chessNameTag = 12;
		chessData = { {0,0,0,0},0,{0,0,0,0},0,0,0,0,0 };
		chessImage = "Warrior1.png";
	}
}

//辅助类
Support::Support(string name)
{
	//待修改
	chessName = name;
	if (chessName == "辅助1")
	{
		chessNameTag = 13;
		chessData = { {0,0,0,0},0,{0,0,0,0},0,0,0,0,0 };
		chessImage = "Warrior1.png";
	}
	else if (chessName == "辅助2")
	{
		chessNameTag = 14;
		chessData = { {0,0,0,0},0,{0,0,0,0},0,0,0,0,0 };
		chessImage = "Warrior1.png";
	}
}