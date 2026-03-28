#pragma once
#include <string>
#include <memory>
#include <iostream>
//#include "Player.h"
class Player;
using namespace std;

class Skill;
class Item {
public:
    Item(string name, int price,int unlocklevel);
    virtual ~Item();

    string getName() const;
    int getPrice() const;

    virtual void use(Player* character) = 0;
    void clear();
    void printInfo() const;

	bool isUnlocked(int playerLevel) const;
	int getUnlockLevel() const { return unlocklevel; }
	virtual Item* clone() const = 0;
	virtual bool hideInfo() const { return false; }

protected:
    string name;
    int price;
	int unlocklevel;
};

//체력 회복
class HealthPotion : public Item {
public:
    HealthPotion(string name, int price, int heal,int unlocklevel);
    void use(Player* character) override;
	Item* clone() const override;

private:
    int healthRestore;
};

//체력 최대량 Up
class MaxHpUp: public Item {
public:
	MaxHpUp(string name, int price, int heal,int unlocklevel);
	void use(Player* character) override;
	Item* clone() const override;

private:
	int maxHpIncrease;
};

//강화 체력 포션
class MegaHealthPotion : public Item {
public:
	MegaHealthPotion();
	void use(Player* player) override;
	Item* clone() const override;
	bool hideInfo() const;
private:
	int healAmount;

};

//산소 회복
class OxygenPotion : public Item {
public:
    OxygenPotion(string name, int price, int oxygen,int unlocklevel);
    void use(Player* character) override;
	Item* clone() const override;

private:
    int oxygenIncrease;
};

//산소 최대량 Up
class MaxOxygenUp : public Item {
public:
	MaxOxygenUp(string name, int price, int oxygen,int unlocklevel);
	void use(Player* character) override;
	Item* clone() const override;

private:
	int maxIncrease;
};

//강화 산소 포션
class MegaOxygenPotion : public Item {
public:
	MegaOxygenPotion();
	void use(Player* p) override;
	Item* clone() const override;
	bool hideInfo() const;

private:
	int oxygen;
};

//압력 해소
class PressurePotion : public Item {
public:
    PressurePotion(string name, int price, int pressure,int unlocklevel);
    void use(Player* character) override;
	Item* clone() const override;

private:
    int pressurePotion;
};

//압력 최대량 Up
class MaxPressureUp: public Item{
public:
	MaxPressureUp(string name, int price, int pressure,int unlocklevel);
	void use(Player* character) override;
	Item* clone() const override;

private:
	int maxIncrease;
};

//강화 압력 포션
class MegaPressurePotion : public Item {
public:
	MegaPressurePotion();
	void use(Player* p) override;
	Item* clone() const override;
	bool hideInfo() const;
private:
	int pressure;
};


//공격력 Up
class AttackBoost : public Item {
public:
    AttackBoost(string name, int price, int attack,int unlocklevel);
    void use(Player* character) override;
	Item* clone() const override;

private:
    int attackIncrease;
};

//무기 강화 아이템
class WeaponUpgrade : public Item {
public:
	WeaponUpgrade(string name, int price, int atk, int unlocklevel);
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
	SkillBook(string name, unique_ptr<Skill> skill, int unlocklevel);
	void use(Player* player) override;
	virtual ~SkillBook() override = default;
};


