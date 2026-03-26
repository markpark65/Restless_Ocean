#include <random>
#include "Random.h"

int Random::getRandomValue(int min, int max)
{
	// 재사용 가능한 난수 엔진
	static std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<int> dis(min, max);

	return dis(gen);
}