#include "Information.h"
#include<algorithm>

// 在类外初始化静态成员变量
std::map<int, heroInformation> Information::info;

Information::Information() {
	////英雄名map
	//name[0] = "";
	////法师
	//name[1] = "Taric";
	//name[2] = "Ali";
	//name[3] = "Anny";
	//name[4] = "Alice";
	////射手
	//name[5] = "Nami";
	//name[6] = "Erlius";
	//name[7] = "Kasia";
	////辅助（远战）
	//name[8] = "Lilia";
	////辅助（近战）
	//name[9] = "Kuqi";
	////战士
	//name[10] = "Kennen";
	//name[11] = "Chuishi";
	//name[12] = "Serti";
	//name[13] = "Katerina";
	//name[14] = "Evelynn";

	//英雄信息设置
	SetHeroInfo();
}
heroInformation* Information::getheroInformation(int heroTag, int level) {
	// 检查是否存在该英雄的信息
	if (info.find(heroTag) != info.end()) {
		// 获取基础信息
		heroInformation* baseInfo = &info[heroTag];

		// 创建一个新的 heroInformation 对象来存储升级后的属性
	 heroInformation* upgradedInfo = new heroInformation(*baseInfo);

		// 更新属性，这里假设每级增加的属性是固定的
		upgradedInfo->HP += level * 10; // 示例：每级增加10点生命值
		upgradedInfo->attack += level * 5; // 示例：每级增加5点攻击力

		// 返回更新后的英雄信息
		return upgradedInfo;
	}
	return nullptr; // 如果找不到英雄信息，返回 nullptr
}
void Information::SetHeroInfo() {
	for (int i = 1; i <= 14; i++) {
		HeroInfo[i] = { 500,60,70,1.2,35,200,80,160 };
	}
	//待设置...

	//初始化英雄信息查找表
	for (int i = 1; i <= 14; i++) {
		info[i] = HeroInfo[i];
		//info[i].HP = 500;
	}
}
std::unordered_map<int, std::string> Information::name = {
	{0, ""},
	{1, "Taric"},
	{2, "Ali"},
	{3, "Anny"},
	{4, "Alice"},
	{5, "Nami"},
	{6, "Erlius"},
	{7, "Kasia"},
	{8, "Lilia"},
	{9, "Kuqi"},
	{10, "Kennen"},
	{11, "Chuishi"},
	{12, "Serti"},
	{13, "Katerina"},
	{14, "Evelynn"}
};


std::unordered_map<int, std::string> Information::imagePaths = {
    {1, "Taric.png"},
    {2, "Ali.png"},
   {3,"Anny.png" },
    {4,"Alice.png"},
	{5, "Nami.png"},
	{6, "Erlius.png"},
	{7, "Kasia.png"},
	{8, "Lilia.png"},
	{9, "Kuqi.png"},
	{10, "Kennen.png"},
	{11, "Chuishi.png"},
	{12, "Serti.png"},
	{13, "Katerina.png"},
	{14, "Evelynn.png"}
};

std::unordered_map<int, std::string> Information::warimagePaths = {
	{1, "Taric-action1.png"},
	{2, "Ali-action1.png"},
   {3,"Anny-action1.png" },
	{4,"Alice-action1.png"},
	{5, "Nami-action1.png"},
	{6, "Erlius-action1.png"},
	{7, "Kasia-action1.png"},
	{8, "Lilia-action1.png"},
	{9, "Kuqi-action1.png"},
	{10, "Kennen-action1.png"},
	{11, "Chuishi-action1.png"},
	{12, "Serti-action1.png"},
	{13, "Katerina-action1.png"},
	{14, "Evelynn-action1.png"}
};

std::string Information::getNameByTag(int tag) {
    return name[tag];
}

std::string Information::getHeroPathByTag(int tag) {
    return imagePaths[tag];
}

heroInformation* Information::GetInfoByTag(int tag) {
	heroInformation* testInfo4 = new heroInformation;
	testInfo4->HP = 700;
	testInfo4->MP = 60;
	testInfo4->attack = 60;
	testInfo4->atkspeed = 1.5;
	testInfo4->defence = 35;
	testInfo4->atkrange = 200;
	testInfo4->movespeed = 80;
	testInfo4->attackSpeed = 160;
	info[tag] = *testInfo4;
	return &info[tag];
}