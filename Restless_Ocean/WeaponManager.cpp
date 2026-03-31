#include <iostream>
#include "WeaponManager.h"
#include "InputSystem.h"
#include "GlobalVal.h"
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
	//cout << "무기를 선택하세요.\n";
	g_sceneData.description = "무기를 선택하세요. \n ";
	printWeapons();

	//int choice;
	//InputSystem inputSystem;
	//choice = inputSystem.getInputInt(1, weapons.size());
	g_sceneData.selectedIndex = 0;
	g_sceneData.options = {
		"섬광탄",
		"반타블랙 검",
		"폭발형 수총",
	};
	while (true)
	{
		int selectedIndex = g_cliRenderer.OptionSelector(g_sceneData);
		switch (g_sceneData.selectedIndex)
		{
		case 0:
			return make_unique<Flashbang>();
		case 1:
			return make_unique<Vantablack>();
		case 2:
			return make_unique<WaterGun>();
		default:
			return nullptr;
		}
		break;
	}


}

void WeaponManager::printWeapons() const {

	for(int i = 0; i < weapons.size(); ++i) {

		g_sceneData.description += weapons[i]->getName();
		g_sceneData.description += " | 추가 대미지 : " + std::to_string(weapons[i]->getAddDamage())+ " \n ";
	}
}


