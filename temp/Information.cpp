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
	}
}
std::unordered_map<int, std::string> Information::name = {
    {1, "Hero1"},
    {2, "Hero2"},
    {3,"Hero3" },
    {4,"Hero4"}
};

std::unordered_map<int, std::string> Information::imagePaths = {
    {1, "hero1.png"},
    {2, "hero2.png"},
   {3,"hero3.png" },
    {4,"hero4.png"}
};

//std::unordered_map<int, std::string> Information::alternateImagePaths = {
//    {1, "hero1_alt.png"},
//    {2, "hero2_alt.png"},
//    {3, "hero3_alt.png"},
//    {4, "hero4_alt.png"}
//};
std::string Information::getNameByTag(int tag) {
    return name[tag];
}

std::string Information::getHeroPathByTag(int tag) {
    return imagePaths[tag];
}

heroInformation* Information::GetInfoByTag(int tag) {
	return &info[tag];
}