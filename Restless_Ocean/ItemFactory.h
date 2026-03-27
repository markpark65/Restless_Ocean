#pragma once
#include <vector>
#include "Item.h"
#include "Random.h"

extern

class ItemFactory
{
public:
	ItemFactory()
	{
		items.push_back(new HealthPotion("체력 포션", 1, 20, 1));
		items.push_back(new MaxHpUp("방수가 잘 되어있는 초코과자", 1, 20, 1));
		items.push_back(new OxygenPotion("산소 포션", 1, 20, 1));
		items.push_back(new MaxOxygenUp("1000년 전의 스노클", 1, 20, 1));
		items.push_back(new PressurePotion("압력 포션", 1, 20, 1));
		items.push_back(new MaxPressureUp("어느 물고기의 부레", 1, 20, 1));
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
		int randomIndex = random.getRandomValue(0, items.size() - 1);
		Item* selectedItem = items[randomIndex];
		return selectedItem->clone();
	}


private:
	std::vector<Item*> items;
};

