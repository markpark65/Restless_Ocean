#pragma once
#include <string>

class Monster;

enum class WeaponType { FLASH, VANTA_BLACK, EXPLOSIVE_GUN, NONE };

class Weapon {
protected:
	std::string name;
	WeaponType type;
	int addDamage;

public:
	Weapon(std::string n, WeaponType t, int d, int bc)
		: name(n)
		, type(t)
		, addDamage(d) {
	}

	virtual ~Weapon() {} // 상속 시
	

	// 공통 정보 조회
	std::string getName() const { return name; }
	WeaponType getType() const { return type; }
	int getAddDamage() const { return addDamage; } 
};
class Flashbang : public Weapon {
public:
	Flashbang();
};

class Vantablack : public Weapon {
public:
	Vantablack();
};

class WaterGun : public Weapon {
public:
	WaterGun();
};
