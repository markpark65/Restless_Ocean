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
// 섬광탄 (Flashbang)
int Flashbang::calculateDamage(int baseAttack, const Monster* target) const {
	int total = baseAttack + addDamage;
	// MonsterStat의 type이 Hidden(은닉형)이면 2배 데미지
	if (target && target->getMonsterStat().type == AttributeType::Hidden) {
		std::cout << "\n[특수] 섬광이 은닉한 적을 밝혀냅니다! (데미지 2배)" << std::endl;
		return total * 2;
	}
	return total;
}

// 반타블랙 (Vantablack)
int Vantablack::calculateDamage(int baseAttack, const Monster* target) const {
	int total = baseAttack + addDamage;
	// Luminous(발광형)에게 2배
	if (target && target->getMonsterStat().type == AttributeType::Luminous) {
		std::cout << "\n[특수] 반타블랙이 적의 빛을 흡수합니다! (데미지 2배)" << std::endl;
		return total * 2;
	}
	return total;
}

// 폭발형 수총 (WaterGun)
int WaterGun::calculateDamage(int baseAttack, const Monster* target) const {
	int total = baseAttack + addDamage;
	// Giant(거대형)에게 2배
	if (target && target->getMonsterStat().type == AttributeType::Giant) {
		std::cout << "\n[특수] 압축 폭발이 거대한 외피를 뚫습니다! (데미지 2배)" << std::endl;
		return total * 2;
	}
	return total;
}
