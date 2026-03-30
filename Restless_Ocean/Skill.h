#pragma once
#include <string>
#include <memory>
#include <iostream>

class Player;
class Monster;

class Skill
{
protected:
	std::string name;
	int batteryCost;
public:
	Skill(std::string n, int cost);
	virtual ~Skill();

	virtual void execute(Player* player, Monster* target) = 0;
	std::string getName() const { return name; }
	int getCost() const { return batteryCost; }
};
class TripleDamageSkill : public Skill {
public:
	TripleDamageSkill();
	void execute(Player* player, Monster* target) override;
};
class BindSkill : public Skill {
public:
	BindSkill();
	void execute(Player* player, Monster* target) override;
};
class CounterSkill : public Skill {
public:
	CounterSkill();
	void execute(Player* player, Monster* target) override;
};
