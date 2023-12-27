#pragma once
#ifndef __SHOWHPMP_H__
#define __SHOWHPMP_H__

#include "cocos2d.h"  
using namespace cocos2d;

class showHPMP : public cocos2d::Sprite
{
public:
    virtual bool init();
    static showHPMP* showHPMP::create();
public:
    //设置血条背景  
    void setBackgroundTexture(const char* pName);
    //设置血条前景  
    void setForegroundTexture(const char* pName);
    //设置总血量  
    void setTotalProgress(float total);
    //设置当前血量  
    void setCurrentProgress(float progress);
    //得到当前血量  
    float getCurrentProgress() const;
    //得到总血量  
    float getTotalProgress() const;

private:
    //设置前景血条显示的长度  
    void setForegroundTextureRect(const CCRect& rect);

private:
    Sprite* P_back;//背景血条  
    Sprite* P_front;//前景血条  
    float total;//总血量  
    float P_current;//当前血量  
    float P_scale;//放大倍数  
};

#endif
