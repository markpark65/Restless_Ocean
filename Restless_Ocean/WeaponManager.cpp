#include <iostream>
#include "WeaponManager.h"
#include "InputSystem.h"

using namespace std;

WeaponManager::WeaponManager()
{
	weapons.push_back(new Flashbang());
	weapons.push_back(new Vantablack());
	weapons.push_back(new WaterGun());
}
WeaponManager::~WeaponManager()
{

}
unique_ptr<Weapon> WeaponManager::selectWeapon() const
{
	cout << "무기를 선택하세요.\n";
	printWeapons();

	int choice;
	InputSystem inputSystem;
	choice = inputSystem.getInputInt(1, weapons.size());

	switch (choice)
	{
	case 1:
		return make_unique<Flashbang>();
	case 2:
		return make_unique<Vantablack>();
	case 3:
		return make_unique<WaterGun>();
	default:
		return nullptr;
	}


}

void WeaponManager::printWeapons() const {

	for(int i = 0; i < weapons.size(); ++i) {
		cout << i + 1 << ". " << weapons[i]->getName() << '\n';
		//cout << "타입: " << weapons[i]->getType() << '\n';
		cout << "추가 대미지: " << weapons[i]->getAddDamage() << "\n";
	}
}

