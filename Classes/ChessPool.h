/*
* �ļ����ƣ�ChessPool.h
* ���ܣ����ص�ʵ��
*
* ���ߣ�fbr
* ��ע��
*
*/

#ifndef _CHESS_POOL_H_
#define _CHESS_POOL_H_

#include <vector>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include <memory>

#include "Chess.h"
#include "cocos2d.h"

USING_NS_CC;

using std::vector;

class ChessPool
{
public:
	//����
	vector<Chess*> chessPool;
public:
	ChessPool();

	//��ʼ������
	void InitChessPool();

	//�Ƴ�����
	Chess* DrawChess();

	//���뿨��
	void AddChess(Chess* chess);

	// ���ҿ���˳��
	void ShufflePool();
};

#endif // _CHESS_POOL_H_
