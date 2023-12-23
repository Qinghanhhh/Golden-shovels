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









//��ʦ��
Mage::Mage(string name)
{
	chessName = name;
	if (chessName == "��ܽ��")
	{
		chessNameTag = 1;
		chessData = { {0,550,990,1782},60,{0,45,68,101},0.7,3,35,35,1};
		chessImage = "Mage1.png";
	}
	else if (chessName == "����")
	{
		chessNameTag = 2;
		chessData = { {0,450,810,1458},50,{0,40,60,90},0.65,4,20,20,2 };
		chessImage = "Mage2.png";
	}
	else if (chessName == "��������")
	{
		chessNameTag = 3;
		chessData = { {0,650,1170,2106},60,{0,40,60,90},0.7,2,35,35,2 };
		chessImage = "Mage3.png";
	}
	else if (chessName == "����")
	{
		chessNameTag = 4;
		chessData = { {0,700,1260,2268},30,{0,40,60,90},0.8,4,30,30,3 };
		chessImage = "Mage4.png";
	}
}

//սʿ��
Warrior::Warrior(string name)
{
	chessName = name;
	if (chessName == "������")
	{
		chessNameTag = 5;
		chessData = { {0,650,1170,2106},0,{0,50,75,113},0.65,1,45,45,1 };
		chessImage = "Warrior1.png";
	}
	else if (chessName == "��ķ")
	{
		chessNameTag = 6;
		chessData = { {0,650,1170,2106},0,{0,60,90,135},0.55,1,45,45,1 };
		chessImage = "Warrior2.png";
	}
	else if (chessName == "ɪ��")
	{
		chessNameTag = 7;
		chessData = { {0,950,1710,3078},60,{0,55,83,124},0.7,1,45,45,2 };
		chessImage = "Warrior3.png";
	}
	else if (chessName == "��ʯ")
	{
		chessNameTag = 8;
		chessData = { {0,1000 ,1800 ,3240},120,{0,60,90,135},0.65,1,60,60,3 };
		chessImage = "Warrior4.png";
	}
}

//������
Shooter::Shooter(string name)
{
	//���޸�
	chessName = name;
	if (chessName == "����1")
	{
		chessNameTag = 9;
		chessData = { {0,0,0,0},0,{0,0,0,0},0,0,0,0,0 };
		chessImage = "Warrior1.png";
	}
	else if (chessName == "����2")
	{
		chessNameTag = 10;
		chessData = { {0,0,0,0},0,{0,0,0,0},0,0,0,0,0 };
		chessImage = "Warrior1.png";
	}
	else if (chessName == "����3")
	{
		chessNameTag = 11;
		chessImage = "Warrior1.png";
		chessData = { {0,0,0,0},0,{0,0,0,0},0,0,0,0,0 };
	}
	else if (chessName == "����4")
	{
		chessNameTag = 12;
		chessData = { {0,0,0,0},0,{0,0,0,0},0,0,0,0,0 }; 
		chessImage = "Warrior1.png";
	}
}

//������
Support::Support(string name)
{
	//���޸�
	chessName = name;
	if (chessName == "����1")
	{
		chessNameTag = 13;
		chessData = { {0,0,0,0},0,{0,0,0,0},0,0,0,0,0 };
		chessImage = "Warrior1.png";
	}
	else if (chessName == "����2")
	{
		chessNameTag = 14;
		chessData = { {0,0,0,0},0,{0,0,0,0},0,0,0,0,0 };
		chessImage = "Warrior1.png";
	}
}
