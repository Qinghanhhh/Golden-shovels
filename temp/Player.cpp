#include "Player.h"

// 初始化静态成员变量
Player* Player::_instance = nullptr;

Player* Player::getInstance() {
	if (!_instance) {
		_instance = new Player();
		// 这里可以初始化其他属性，比如金币
		_instance->gold = 100; // 示例初始金币数量
	}
	return _instance;
}

// 构造函数
Player::Player() : gold(0) {
	// 初始化其他成员变量
}

// 如果需要，可以在这里实现析构函数
Player::~Player() {
	// 清理资源，如果有的话
}

// 可以在此实现其他 Player 类的方法
bool Player:: hasEnoughGold(int amount) {
	return gold >= amount;  // 检查金币是否足够
}


void Player::spendGold(int amount) {
	if (gold >= amount) {
		gold -= amount;  // 减少金币
	}
}

int Player::getGold()
{
	return gold;
}
