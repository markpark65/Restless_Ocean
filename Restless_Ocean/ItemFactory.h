#pragma once
#include <vector>
#include "GameManager.h"
#include "Item.h"
#include "Random.h"
#include "Player.h"

class ItemFactory
{
public:
	ItemFactory()
	{
		items.push_back(new HealthPotion("체력 포션", 1, 50, 1));
		items.push_back(new MaxHpUp("방수가 잘 되어있는 초코과자", 1, GameManager::getInstance().getPlayer().getMaxHp(), 1));
		items.push_back(new OxygenPotion("산소 포션", 1, 50, 1));
		items.push_back(new MaxOxygenUp("1000년 전의 스노클", 1, GameManager::getInstance().getPlayer().getMaxOxygen(), 1));
		items.push_back(new PressurePotion("압력 포션", 1, 20, 1));
		items.push_back(new MaxPressureUp("어느 물고기의 부레", 1, GameManager::getInstance().getPlayer().getMaxPressure(), 1));
		items.push_back(new AttackBoost("깨진 조개껍데기 목걸이", 1, 20, 1));
		
	}

	~ItemFactory()
	{
		for (Item* item : items) {
			delete item;
		}
		items.clear();
	}

	Item* getRandomItem() {
		Random random;
		int maxIndex = static_cast<int>(items.size()) - 1;
		int randomIndex = random.getRandomValue(0, maxIndex);

		Item* selectedItem = items[randomIndex];
		return selectedItem->clone();
	}

private:
	std::vector<Item*> items;
};

