#include "Weapon.h"
#include "Monster.h"
#include "GameLogger.h"
#include <iostream>

void Weapon::increaseDamage(int amount) {
	addDamage += amount;
	std::cout << name<<"(이)가 +" << amount << " 만큼 강화되었습니다!\n";
}

//// 섬광탄 (Flashbang)
Flashbang::Flashbang() : Weapon("섬광탄", WeaponType::FLASH, 30) {}
int Flashbang::calculateDamage(int baseAttack, const Monster* target) const {
	int total = baseAttack + addDamage;
	// MonsterStat의 type이 Hidden(은닉형)이면 2배 데미지
	if (target && target->getMonsterType() == AttributeType::Hidden) {
		std::cout << "\n 섬광이 은닉한 적을 밝혀냅니다! (데미지 2배)" << std::endl;
		return total * 2;
	}
	return total;
}

// 반타블랙 (Vantablack)
Vantablack::Vantablack() : Weapon("반타블랙 검", WeaponType::VANTA_BLACK, 35) {}
int Vantablack::calculateDamage(int baseAttack, const Monster* target) const {
	int total = baseAttack + addDamage;
	// Luminous(발광형)에게 2배
	if (target && target->getMonsterType() == AttributeType::Luminous) {
		std::cout << "\n 반타블랙이 적의 빛을 흡수합니다! (데미지 2배)" << std::endl;
		return total * 2;
	}
	return total;
}

// 폭발형 수총 (WaterGun)
WaterGun::WaterGun() : Weapon("폭발형 수총", WeaponType::EXPLOSIVE_GUN, 50) {}
int WaterGun::calculateDamage(int baseAttack, const Monster* target) const {
	int total = baseAttack + addDamage;
	// Giant(거대형)에게 2배
	if (target && target->getMonsterType() == AttributeType::Giant) {
		std::cout << "\n 압축 폭발이 거대한 외피를 뚫습니다! (데미지 2배)" << std::endl;
		return total * 2;
	}
	return total;
}
