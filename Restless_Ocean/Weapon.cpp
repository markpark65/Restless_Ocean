#include "Weapon.h"
#include "Monster.h"
#include "GameLogger.h"
#include <iostream>



int Weapon::calculateDamage(int baseAttack, const Monster* target) const {
	int totalAtk = baseAttack + addDamage;

	//if (type != WeaponType::NONE && target != nullptr) {
	//	if (type == target->getWeakness()) {
	//		std::cout << name << "이(가) 적의 약점을 찔렀습니다!" << std::endl;
	//		return totalAtk * 2;

	//	}
	//}

	return totalAtk;
}
// --- 섬광탄 (Flashbang) ---
class Flashbang : public Weapon {
public:
	Flashbang() : Weapon("섬광탄", WeaponType::FLASH, 30, 15) {}

	int calculateDamage(int baseAttack, const Monster* target) const override {
		int total = baseAttack + addDamage;
		// 은닉형 몬스터(FLASH에 약함) 체크 로직은 나중에 Monster 클래스 완성 시 연동
		return total;
	}
};

// --- 반타블랙 (Vantablack) ---
class Vantablack : public Weapon {
public:
	Vantablack() : Weapon("반타블랙 검", WeaponType::VANTA_BLACK, 35, 5) {}

	int calculateDamage(int baseAttack, const Monster* target) const override {
		return baseAttack + addDamage;
	}
};

// --- 폭발형 수총 (WaterGun) ---
class WaterGun : public Weapon {
public:
	WaterGun() : Weapon("폭발형 수총", WeaponType::EXPLOSIVE_GUN, 50, 25) {}

	int calculateDamage(int baseAttack, const Monster* target) const override {
		return baseAttack + addDamage;
	}
};
