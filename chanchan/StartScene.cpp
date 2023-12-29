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
	//�����ʼ��ʧ��
	if (!Scene::init())
		return false;
	//��ȡplist��������
	auto configData = FileUtils::getInstance()->getValueMapFromFile("res/tips.plist");
	//������������
	for (auto valPair : configData) {
		//���ֱ��
		int key = atoi(valPair.first.c_str());
		//����
		Value val = valPair.second;
		//CCLOG("key=%d,value=%s", key, val);
		prt_cnWords.insert(pair<int, Value>(key, val));
	}
	//��ȡ��Ļ��ʾ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// ��ȡ��Ļ�ߴ�
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ��������
	auto sprite = Sprite::create("coverdemo.png");
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	// �������ű���
	float scaleX = visibleSize.width / sprite->getContentSize().width;
	float scaleY = visibleSize.height / sprite->getContentSize().height;

	// ���þ�������ű�����������Ļ
	sprite->setScaleX(scaleX);
	sprite->setScaleY(scaleY);

	// ��������ӵ�����
	this->addChild(sprite);

	//����ť����������
	auto startBtn = createinitButton(0, Vec2(visibleSize / 2));
	this->addChild(startBtn);//����ť��������
	//float width = startBtn->getContentSize().width;//��ȡ��ť���
	//float height = startBtn->getContentSize().height;//��ȡ��ť�߶�

	//�������ı�ǩ
	/*auto _label = Label::createWithSystemFont(prt_cnWords.at(1000).asString(), "����", 36);
	_label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_label->setPosition(Vec2(visibleSize / 2));
	this->addChild(_label);*/


	//prt_content = prt_cnWords.at(1000).asString();
	//prt_label = Label::create("", "΢���ź�", 36);//ʵ�ִ���Ч��ʱ��һ�����벻��prt_content,���ǡ�������
	//prt_label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	//prt_label->setPosition(Vec2(visibleSize / 2));
	//prt_label->setColor(Color3B(200, 100, 100));//3B����͸���ȣ�4B��͸����
	//prt_label->enableBold();
	//prt_label->setDimensions(200, 100);//���еļ��
	//this->addChild(prt_label);


	////ʵ�ִ���Ч������������
	//static int i = 0;
	//this->schedule([&](float dlt) {
	//	char ch = prt_content[i];//��ȡ��ǰ�±���ַ�
	//    //�ж��Ƿ�Ϊ����
	//if (ch > -127 && ch < 0) {
	//	i += 3;//���ļ�3
	//}
	//else {
	//	i++;//Ӣ�ļ�1
	//}
	////��ȡ�ַ���
	//string str = prt_content.substr(0, i);
	//prt_label->setString(str);

	////��i�����ַ������ȵ�ʱ��ע��������
	//if (i > prt_content.length()) {
	//	this->unschedule("schedule_callback");
	//}
	//}, 0.3f, "schedule_callback");


	return true;
}


Button* StartScene::createinitButton(float rotation, Vec2 position)
{
	//������Ϸ��ʼ��ť
	auto button = Button::create("play.png", "play1.png", "play2.png");
	//button->setTitleText("start");//���ð�ť����
	//button->setColor(Color3B::RED); //�ı䰴ťǰ��ɫ
	button->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	button->setPosition(position);//���ð�ťλ��
	//button->setTitleFontSize(72);//���ð�ť�������ֺ�


	//���ð�ť
	button->setEnabled(true);

	//��ת��ť
	//button->setRotation(-90);

	button->addClickEventListener([](Ref* sender) {
		// �����ǵ���¼�����ʱ�Ļص�����
		auto scene = MapScene::createScene(); // ���� MapScene ����
	Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene)); // ʹ�ù��ɶ����滻����
		});

	return button;
}