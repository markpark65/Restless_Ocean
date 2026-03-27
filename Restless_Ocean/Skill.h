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
public:
	Skill(std::string n);
	virtual ~Skill();

	virtual void execute(Player* player, Monster* target) = 0;
	std::string getName() const { return name; }
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
