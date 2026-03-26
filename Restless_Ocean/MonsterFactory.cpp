#include "MonsterFactory.h"
#include "Item.h"

int MonsterFactory::getRandomValue(int min, int max)
{
	// 재사용 가능한 난수 엔진
	static std::mt19937 gen(std::random_device{}());
	// 플레이어 레벨에 따라 몬스터의 스탯 범위를 결정하기 위한 난수열
	std::uniform_int_distribution<int> dis(min, max);

	return dis(gen);
}

// 플레이어 레벨에 따라 랜덤으로 몬스터의 스탯 조정
Monster* MonsterFactory::GenerateMonster(int level)
{
	MonsterStat stat;
	Item* item;

	int randomType = getRandomValue(0, 2);
	int randomItem = getRandomValue(0, 1);

	switch (randomType)
	{
	case 0:
		stat.name = "초롱 아귀";
		stat.health = getRandomValue(20, 30) * level;
		stat.attack = getRandomValue(5, 10) * level;
		stat.type = MonsterType::Luminous;
		break;
	case 1:
		stat.name = "바이퍼 피쉬";
		stat.health = getRandomValue(20, 30) * level;
		stat.attack = getRandomValue(5, 10) * level;
		stat.type = MonsterType::Hidden;
		break;
	case 2:
		stat.name = "대형 오징어";
		stat.health = getRandomValue(20, 30) * level;
		stat.attack = getRandomValue(5, 10) * level;
		stat.type = MonsterType::Giant;
		break;
	default:
		return nullptr;
		break;
	}

	switch (randomItem)
	{
	case 0:
		item = new HealthPotion();
		break;
	case 1:
		item = new AttackBoost();
		break;
	default:
		return nullptr;
		break;
	}

	MonsterReward reward = { 50, 50, item};

	return new Monster(stat, reward);
}