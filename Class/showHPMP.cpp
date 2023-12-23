#include "showHPMP.h"  

bool showHPMP::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    P_back = NULL;
    P_front = NULL;
    total = 0;
    P_current = 0;
    P_scale = 1;
    return true;
}

showHPMP* showHPMP::create()
{
    showHPMP* sprite = new (std::nothrow) showHPMP();
    if (sprite)
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

void showHPMP::setBackgroundTexture(const char* pName)
{
    P_back = Sprite::create(pName);
    this->addChild(P_back);
}

void showHPMP::setForegroundTexture(const char* pName)
{
    P_front = Sprite::create(pName);
    P_front->setAnchorPoint(Vec2(0.0f, 0.5f));//ÉèÖÃÃªµã  
    P_front->setPosition(Vec2(-P_front->getContentSize().width * 0.5f, 0));
    this->addChild(P_front);
}

void showHPMP::setTotalProgress(float data)
{
    if (P_front == NULL) { return; }
    P_scale = P_front->getContentSize().width / total;
    total = data;
}

void showHPMP::setCurrentProgress(float progress)
{
    if (P_front == NULL) { return; }
    if (progress < 0.0f) { progress = 0.0f; }
    if (progress > total) { progress = total; }
    P_current = progress;
    float rectWidth = progress * P_scale;
    const Point from = P_front->getTextureRect().origin;
    const Rect rect = CCRectMake(from.x, from.y, rectWidth, P_front->getContentSize().height);
    setForegroundTextureRect(rect);
}

void showHPMP::setForegroundTextureRect(const CCRect& rect)
{
    P_front->setTextureRect(rect);
}

float showHPMP::getCurrentProgress() const
{
    return P_current;
}

float showHPMP::getTotalProgress() const
{
    return total;
}