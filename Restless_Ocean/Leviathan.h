#pragma once
#include "BossMonster.h"
#include "Player.h"

class Leviathan : public BossMonster
{
private:
	int _defence = 20;

public:
	Leviathan(const MonsterStat& stat) : BossMonster(stat) {}

	void takeDamage(int damage) override
	{
		damage -= getDefence();

		if (damage < 0)
		{
			damage = 0;
		}

		monsterStat.health -= damage;

		if (monsterStat.health <= 0)
		{
			monsterStat.health = 0;
		}
	}

	void useBasicAttack(Player* target) override
	{
		if (!target)
			return;

		int pressure = 10;

		std::cout << getName() << "이 일반 공격을 사용했습니다!" << '\n';
		std::cout << getName() << "이 거대한 턱으로 " << target->getName() << "을 물어뜯습니다!" << '\n';
		std::cout << getName() << "은 " << target->getName() << "에게" << getAttack() << "의 피해를 입힙니다!" << '\n';
		target->takeDamage(getAttack());
		std::cout << getName() << "은 압력으로 " << target->getName() << "을 압력으로 짓누릅니다!" << '\n';
		target->takePressure(pressure);
	}

	void useSpecialAttack(Player* target) override
	{
		if (!target)
			return;

		int pressure = 20;

		std::cout << getName() << "이 특수 공격을 사용했습니다!" << '\n';
		std::cout << getName() << "은 거대한 물살로 " << target->getName() << "을 심연으로 끌어들입니다!" << '\n';
		int damage = getAttack() * 2;
		std::cout << getName() << "은 " << target->getName() << "에게" << damage << "의 피해를 입힙니다!" << '\n';
		target->takeDamage(damage);
		std::cout << getName() << "은 압력으로 " << target->getName() << "을 압력으로 짓누릅니다!" << '\n';
		target->takePressure(pressure);
	}

	void activatePassive() override
	{
		std::cout << getName() << "의 패시브가 발동됩니다!" << '\n';
		std::cout << getName() << "의 몸이 더 단단해집니다!" << '\n';
		std::cout << getName() << "의 방어력이 " << 10 << " 증가합니다!" << '\n';
		int defence = 10;
		enhancedDefence(defence);
	}

	int getDefence()
	{
		return _defence;
	}

	void enhancedDefence(int defence)
	{
		_defence += defence;
	}
};
