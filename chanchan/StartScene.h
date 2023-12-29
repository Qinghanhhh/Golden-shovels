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
	//��������
	static Scene* createScene();
	//��ʼ���������ݺͽ���UI���
	virtual bool init();

	CREATE_FUNC(StartScene);
private:
	//��¼�����ּ��� key�����ֱ�� value��������
	map<int, Value>prt_cnWords;

	//��¼��ǰ��������
	string prt_content;

	//��¼��ǩUI�ռ�
	Label* prt_label;

	//��������ť
	Button* createinitButton(float rotation, Vec2 position);
	void menuCloseCallback(Ref* pSender);
};

