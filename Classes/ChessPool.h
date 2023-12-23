/*
* 文件名称：ChessPool.h
* 功能：卡池的实现
*
* 作者：fbr
* 备注：
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
	//卡池
	vector<Chess*> chessPool;
public:
	ChessPool();

	//初始化函数
	void InitChessPool();

	//移除卡池
	Chess* DrawChess();

	//加入卡池
	void AddChess(Chess* chess);

	// 打乱卡池顺序
	void ShufflePool();
};

#endif // _CHESS_POOL_H_
