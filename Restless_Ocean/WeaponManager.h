#pragma once
#include <vector>
#include "Weapon.h"
using namespace std;

class WeaponManager
{
public:
	WeaponManager();
	~WeaponManager();
	unique_ptr<Weapon> selectWeapon() const;
	void printWeapons() const;
private:
	vector<Weapon*> weapons;
};

