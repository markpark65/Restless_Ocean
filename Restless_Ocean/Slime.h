#pragma once

#include "Monster.h"

class Slime : public Monster
{
private:

public:
	Slime(int level);

	std::string getName() const	override;
	int getHealth() const		override;
	int getAttack() const		override;
	bool isAlive() const		override;

	void takeDamage(int damage)	override;
};

