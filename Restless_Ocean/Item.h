#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "Player.h"
using namespace std;
class Skill;
class Item {
public:
    Item(string name, int price);
    virtual ~Item();

    string getName() const;
    int getPrice() const;

    virtual void use(Player* character) = 0;
    void clear();
    void printInfo() const;

	virtual Item* clone() const = 0;

protected:
    string name;
    int price;
};

//체력 회복
class HealthPotion : public Item {
public:
    HealthPotion(string name, int price, int heal);
    void use(Player* character) override;
	Item* clone() const override;

private:
    int healthRestore;
};

//체력 최대량 Up
class MaxHpUp: public Item {
public:
	MaxHpUp(string name, int price, int heal);
	void use(Player* character) override;
	Item* clone() const override;

private:
	int maxHpIncrease;
};

//산소 회복
class OxygenPotion : public Item {
public:
    OxygenPotion(string name, int price, int oxygen);
    void use(Player* character) override;
	Item* clone() const override;

private:
    int oxygenIncrease;
};

//산소 최대량 Up
class MaxOxygenUp : public Item {
public:
	MaxOxygenUp(string name, int price, int oxygen);
	void use(Player* character) override;
	Item* clone() const override;

private:
	int maxIncrease;
};

//압력 해소
class PressurePotion : public Item {
public:
    PressurePotion(string name, int price, int pressure);
    void use(Player* character) override;
	Item* clone() const override;

private:
    int pressurePotion;
};

//압력 최대량 Up
class MaxPressureUp: public Item{
public:
	MaxPressureUp(string name, int price, int pressure);
	void use(Player* character) override;
	Item* clone() const override;

private:
	int maxIncrease;
};


//공격력 Up
class AttackBoost : public Item {
public:
    AttackBoost(string name, int price, int attack);
    void use(Player* character) override;
	Item* clone() const override;

private:
    int attackIncrease;
};
//스킬북
class SkillBook : public Item {
private:
	std::unique_ptr<Skill> containedSkill;
public:
	SkillBook(string name, unique_ptr<Skill> skill);
	void use(Player* player) override;
	virtual ~SkillBook() override = default;
};
