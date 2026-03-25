#pragma once

#include <iostream>
#include <string>

using namespace std;

class Player
{
private:
	string name;
	int level;
	int hp;
	int maxHp;
	int attack;
	int exp;
	int maxExp;
	int gold;
	int oxygen;
	int pressure;
	int battery;
	int artifactCount;

public:
	Player(string n);

	//상태 출력
	void showStatus() const;
	//경험치, 레벨업
	void gainExp(int amount);
	void levelUp();
	//전투 결과
	void takeDamage(int damage);
	void recoverDamage(int amount);
	void useOxygen(int amount);
	void addArtifact();
	void spendBattery(int amount);
	void addGold(int amount);
	//정보 참조
	string getName() const { return name; }
	int getLevel() const { return level; }
	int getHp() const { return hp; }
	int getAttack() const { return attack; }
	int getGold() const { return gold; }
	int getArtifactCount() const { return artifactCount; }

};

