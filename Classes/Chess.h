/*
* �ļ����ƣ�Chess.h
* ���ܣ����ӻ�������
*
* ���ߣ�fbr
* 
*
*/

#ifndef  _CHESS_H_
#define  _CHESS_H_

#include <string>
#include <vector>

#include "cocos2d.h"

using std::string;
using std::vector;

USING_NS_CC;

constexpr int CHESSTYPENUM = 14;

struct ChessData 
{
	//����ֵ
	int HP[4];
	//����ֵ
	int MP;
	//������
	int ATK[4];
	//�����ٶ�
	double AttackSpeed;
	//��������
	int AttackRange;
	//�������
	int physicalDefense;
	//ħ������
	int magicDefense;
	//���Ӽ۸�
	int chessPrice;
};


//���ӻ���
class Chess : public cocos2d::Ref
{
protected:
	//��������
	string chessName;
	int chessNameTag;

	//����ְҵ����
	string chessOccupation;

	//���ӵȼ�==1/2/3
	int chessLevel;

	ChessData chessData;

	//ͼƬ·��
	string chessImage;

public:
	//��ʼ������
	void InitChess();

	//��������
	string GetchessName() const;
	int GetchessNameTag() const;
	string GetchessOccupation() const;
	int GetchessLevel()const;
	ChessData GetchessData() const;
	void setchessImage(const string& imagePath); 
	string getchessImage();
};



//����ְҵʵ��

//��ʦ��
class Mage :public Chess
{
private:
	string chessOccupation = "��ʦ";
public:
	//��ʼ��
	Mage(string name);

};

//������
class Shooter :public Chess
{
private:
	string chessOccupation = "����";
public:
	//��ʼ��
	Shooter(string name);

};

//սʿ��
class Warrior :public Chess
{
private:
	string chessOccupation = "սʿ";
public:
	//��ʼ��
	Warrior(string name);

};

//������
class Support :public Chess
{
private:
	string chessOccupation = "����";
public:
	//��ʼ��
	Support(string name);

};

#endif
