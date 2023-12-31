#pragma once
#include "cocos2d.h"
class SetScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menu_click_music(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(SetScene);
};