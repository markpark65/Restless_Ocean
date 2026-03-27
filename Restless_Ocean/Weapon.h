#pragma once
#include <string>

class Monster;

enum class WeaponType { FLASH, VANTA_BLACK, EXPLOSIVE_GUN, NONE };

class Weapon {
protected:
	std::string name;
	WeaponType type;
	int addDamage;
	int batteryCost;

public:
	Weapon(std::string n, WeaponType t, int d, int bc)
		: name(n)
		, type(t)
		, addDamage(d)
		, batteryCost(bc) {
	}

	virtual ~Weapon() {} // 상속 시
	
	// 자식 클래스들이 각자 다르게 구현할 "핵심 로직"
	virtual int calculateDamage(int baseAttack, const Monster* target) const = 0;

	// 공통 정보 조회
	std::string getName() const { return name; }
	WeaponType getType() const { return type; }
	int getBatteryCost() const { return batteryCost; }
};
class Flashbang : public Weapon {
public:
	Flashbang();
	int calculateDamage(int baseAttack, const Monster* target) const override;
};

class Vantablack : public Weapon {
public:
	Vantablack();
	int calculateDamage(int baseAttack, const Monster* target) const override;
};

class WaterGun : public Weapon {
public:
	WaterGun();
	int calculateDamage(int baseAttack, const Monster* target) const override;
};
