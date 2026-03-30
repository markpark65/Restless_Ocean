#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Inventory.h"

class Weapon;
class Monster;
class Skill;
class Item;

class Player
{
private:
	std::string name;
	int level;
	int hp;
	int maxHp;
	int baseAttack;
	int tempAttack;
	int speed;
	int baseSpeed;
	int exp;
	int maxExp;
	int gold;
	int oxygen;
	int maxOxygen;
	int pressure;
	int maxPressure;
	int battery;
	int maxBattery;
	int artifactCount;
	int gachaCount;
	std::vector<std::string> artifacts;
	std::unique_ptr<Weapon> equippedWeapon;
	std::unique_ptr<Skill> currentSkill;
	Inventory<Item> inventory;

public:
	Player(std::string n);
	~Player();
	//상태 출력
	void showStatus() const;
	//경험치, 레벨업, 스킬 배우기
	void gainExp(int amount);
	void levelUp();
	//아이템, 무기, 추가 공격력
	void addAttack(int amout);
	void addTempAttack(int amount);
	void resetTempStats();
	void setWeapon(std::unique_ptr<Weapon> newWeapon);
	void upgradeWeapon(int amount);
	int attack(const Monster* target);
	void learnSkill(std::unique_ptr<Skill> newSkill);
	int getGachaCount() const { return gachaCount; }
	void addGachaCount(int n) { gachaCount += n; }
	
	
	//전투 결과
	bool useSkill(Monster* target);
	void takeDamage(int damage);
	void recoverDamage(int amount);
	void increaseMaxHp(int amount);
	void recoverOxygen(int amount);
	void useOxygen(int amount);
	void IncreaseOxygen(int amount);
	void showArtifacts() const;
	void addArtifact(std::string name);
	bool spendBattery(int amount);
	void addGold(int amount);
	void recoverPressure(int amount);
	void IncreasePressure(int amount);
	void takePressure(int amount);
	void debuffSpeed(int reduction);
	void resetSpeed();
	void rechargeBattery(int amount);

	//정보 참조
	std::string getName() const { return name; }
	int getLevel() const { return level; }
	int getHp() const { return hp; }
	int getMaxHp() const { return maxHp; }
	int getExp() const { return exp; }
	int getMaxExp() const { return maxExp; }
	int getAttack() const { return baseAttack+tempAttack; }
	int getGold() const { return gold; }
	int getArtifactCount() const { return static_cast<int>(artifacts.size()); }
	int getOxygen() const { return oxygen; }
	int getPressure() const { return pressure; }
	int getBattery() const { return battery; }
	int getMaxOxygen() const { return maxOxygen; }
	int getMaxPressure() const { return maxPressure; }
	int getSpeed() const { return speed; }
	Skill* getCurrentSkill() const;
	Inventory<Item>& getInventory() { return inventory; }
	bool hasWeapon() const { return equippedWeapon != nullptr; }

	bool hasAllArtifacts() const;
};

