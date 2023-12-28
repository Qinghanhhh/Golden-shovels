#pragma once
#include "Battle.h"
USING_NS_CC;

class Round :public Scene {
public:
	CREATE_FUNC(Round);
	static Scene* createScene();
	virtual bool init();
	void PlayerInit();
	void CreateBattle(float t);
	virtual	void update(float dt);
	void callback(float t);
private:
	Battle* battlelayer;
	Player* myPlayer;
	Player* enPlayer;
	showHPMP* myHP;  //ÑªÌõ  
	showHPMP* enHP;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Battle* battlelayer;
};