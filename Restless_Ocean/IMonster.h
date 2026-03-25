#pragma once

#include <iostream>
#include <string>

using namespace std;

class IMonster
{
protected:
	string	_name;
	int		_health;
	int		_attack;

public:
	virtual string getName() const = 0;
	virtual	int getHealth() const = 0;
	virtual	int getAttack() const = 0;
	
	virtual void takeDamage(int damage) = 0;

};

