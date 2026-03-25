#include "Player.h"


Player::Player(string n)
	: name(n)
	, level(1)
	, hp(200)
	, maxHp(200)
	, attack(30)
	, exp(0)
	, maxExp(100)
	, gold(0)
	, oxygen(100)
	, pressure(0)
	, battery(100)
	, artifactCount(0) {
	cout << "심해 탐사대원: " << name << " 이(가) 등록되었습니다!" << endl;
}

void Player::showStatus() const {
	cout << "===============================" << endl;
	cout << "대원 정보 이름: " << name << " - level. " << level << endl;
	cout << "HP      :" << hp << " / " << maxHp << endl;
	cout << "ATK     :" << attack << endl;
	cout << "EXP     :" << exp << " / " << maxExp << endl;
	cout << "GOLD    :" << gold << " G" << endl;
	cout << "===============================" << endl;
	cout << "O2      :" << oxygen << " %" << endl;
	cout << "Battery :" << battery << " %" << endl;
	cout << "Pressure:" << pressure << " %" << endl;
	cout << "Artifact:" << artifactCount << " / 5" << endl;
}
//void takedamage(int damage){}
//void recoverdamage(int amount){}
//void useoxygen(int amount){}
//void addartifact(){}
//void spendbattery(int amount){}
//void addgold(int amount){}
//void useItem(){}
//void levelUp(){}