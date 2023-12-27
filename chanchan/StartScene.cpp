#include"StartScene.h"
#include"MapScene.h"

#include "ui/CocosGUI.h"
using namespace ui;

Scene* StartScene::createScene()
{

	return StartScene::create();
}

bool StartScene::init()
{
	//父类初始化失败
	if (!Scene::init())
		return false;
	//获取plist配置数据
	auto configData = FileUtils::getInstance()->getValueMapFromFile("res/tips.plist");
	//解析配置数据
	for (auto valPair : configData) {
		//文字编号
		int key = atoi(valPair.first.c_str());
		//文字
		Value val = valPair.second;
		//CCLOG("key=%d,value=%s", key, val);
		prt_cnWords.insert(pair<int, Value>(key, val));
	}
	//获取屏幕显示大小
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// 获取屏幕尺寸
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 创建精灵
	auto sprite = Sprite::create("coverdemo.png");
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	// 计算缩放比例
	float scaleX = visibleSize.width / sprite->getContentSize().width;
	float scaleY = visibleSize.height / sprite->getContentSize().height;

	// 设置精灵的缩放比例以铺满屏幕
	sprite->setScaleX(scaleX);
	sprite->setScaleY(scaleY);

	// 将精灵添加到场景
	this->addChild(sprite);

	//将按钮加入容器中
	auto startBtn = createinitButton(0, Vec2(visibleSize / 2));
	this->addChild(startBtn);//将按钮加入容器
	//float width = startBtn->getContentSize().width;//获取按钮宽度
	//float height = startBtn->getContentSize().height;//获取按钮高度

	//创建中文标签
	/*auto _label = Label::createWithSystemFont(prt_cnWords.at(1000).asString(), "宋体", 36);
	_label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_label->setPosition(Vec2(visibleSize / 2));
	this->addChild(_label);*/


	//prt_content = prt_cnWords.at(1000).asString();
	//prt_label = Label::create("", "微软雅黑", 36);//实现打字效果时第一个输入不是prt_content,而是“”才行
	//prt_label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//prt_label->setPosition(Vec2(visibleSize / 2));
	//prt_label->setColor(Color3B(200, 100, 100));//3B不带透明度，4B带透明度
	//prt_label->enableBold();
	//prt_label->setDimensions(200, 100);//换行的间距
	//this->addChild(prt_label);


	////实现打字效果（调度器）
	//static int i = 0;
	//this->schedule([&](float dlt) {
	//	char ch = prt_content[i];//获取当前下标的字符
	//    //判断是否为中文
	//if (ch > -127 && ch < 0) {
	//	i += 3;//中文加3
	//}
	//else {
	//	i++;//英文加1
	//}
	////截取字符串
	//string str = prt_content.substr(0, i);
	//prt_label->setString(str);

	////当i超过字符串长度的时候，注销调度器
	//if (i > prt_content.length()) {
	//	this->unschedule("schedule_callback");
	//}
	//}, 0.3f, "schedule_callback");


	return true;
}


Button* StartScene::createinitButton(float rotation, Vec2 position)
{
	//创建游戏开始按钮
	auto button = Button::create("play.png", "play1.png", "play2.png");
	//button->setTitleText("start");//设置按钮字样
	//button->setColor(Color3B::RED); //改变按钮前景色
	button->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	button->setPosition(position);//设置按钮位置
	//button->setTitleFontSize(72);//设置按钮字样的字号


	//禁用按钮
	button->setEnabled(true);

	//旋转按钮
	//button->setRotation(-90);

	button->addClickEventListener([](Ref* sender) {
		// 这里是点击事件发生时的回调函数
		auto scene = MapScene::createScene(); // 创建 MapScene 场景
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene)); // 使用过渡动画替换场景
		});

	return button;
}