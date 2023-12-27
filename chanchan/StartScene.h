#pragma once

#include"cocos2d.h"

USING_NS_CC;

#include "ui/CocosGUI.h"
using namespace ui;

#include<map>
using namespace std;

class StartScene :public Scene
{
public:
	//创建场景
	static Scene* createScene();
	//初始化界面数据和界面UI组件
	virtual bool init();

	CREATE_FUNC(StartScene);
private:
	//记录中文字集合 key：文字编号 value：中文字
	map<int, Value>prt_cnWords;

	//记录当前文字内容
	string prt_content;

	//记录标签UI空间
	Label* prt_label;

	//创建方向按钮
	Button* createinitButton(float rotation, Vec2 position);
	void menuCloseCallback(Ref* pSender);
};

