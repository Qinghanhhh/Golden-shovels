#include "ChessPool.h"

ChessPool::ChessPool()
{
    srand((unsigned int)(time(NULL)));
}

void ChessPool::InitChessPool()
{
    chessPool.clear();

    for (int i = 0; i < 108; i++) 
    {
        chessPool.push_back(new Mage("��ܽ��"));
        chessPool.push_back(new Shooter("������"));
        chessPool.push_back(new Shooter("��ķ"));
    }
    for (int i = 0; i < 60; i++)
    {
        chessPool.push_back(new Mage("����"));
        chessPool.push_back(new Mage("��������"));
        chessPool.push_back(new Shooter("ɪ��"));
    }
    for (int i = 0; i < 30; i++)
    {
        chessPool.push_back(new Mage("����"));
        chessPool.push_back(new Shooter("��ʯ"));
    }
}

Chess* ChessPool::DrawChess()
{
    // ����Ϊ�գ����ؿ�ָ��
    if (chessPool.empty()) 
    {
        return nullptr;
    }

    // �����ȡһ�����ӿ�
    int randomIndex = rand() % chessPool.size();
    Chess* drawnChess = chessPool[randomIndex];

    // �ӿ������Ƴ��ÿ�
    chessPool.erase(chessPool.begin() + randomIndex);

    return drawnChess;
}

void ChessPool::AddChess(Chess* chess)
{
    chessPool.push_back(chess);
}

void ChessPool::ShufflePool()
{
    random_shuffle(chessPool.begin(), chessPool.end());
}