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
        chessPool.push_back(new Mage("ÒÁÜ½ÁÕ"));
        chessPool.push_back(new Shooter("°ÂÀ­·ò"));
        chessPool.push_back(new Shooter("ËþÄ·"));
    }
    for (int i = 0; i < 60; i++)
    {
        chessPool.push_back(new Mage("°²ÄÝ"));
        chessPool.push_back(new Mage("¿¨ÌØÁÕÄÈ"));
        chessPool.push_back(new Shooter("ÉªÌá"));
    }
    for (int i = 0; i < 30; i++)
    {
        chessPool.push_back(new Mage("°¢Àê"));
        chessPool.push_back(new Shooter("´¸Ê¯"));
    }
}

Chess* ChessPool::DrawChess()
{
    // ¿¨³ØÎª¿Õ£¬·µ»Ø¿ÕÖ¸Õë
    if (chessPool.empty()) 
    {
        return nullptr;
    }

    // Ëæ»ú³éÈ¡Ò»ÕÅÆå×Ó¿¨
    int randomIndex = rand() % chessPool.size();
    Chess* drawnChess = chessPool[randomIndex];

    // ´Ó¿¨³ØÖÐÒÆ³ý¸Ã¿¨
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