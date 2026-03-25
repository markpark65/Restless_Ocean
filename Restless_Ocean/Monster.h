#pragma once

#include <iostream>
#include <string>

class Monster
{
protected:
	std::string		name;
	int				health;
	int				attack;

public:
	Monster(const std::string& name, const int health, const int attack)
		: name(name), health(health), attack(attack) { }

	virtual ~Monster() = default;

	virtual std::string getName() const = 0;
	virtual	int getHealth() const = 0;
	virtual	int getAttack() const = 0;
	virtual bool isAlive() const = 0;

	virtual void takeDamage(int damage) = 0;
};

