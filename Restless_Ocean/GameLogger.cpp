#include "GameLogger.h"


std::string GameLogger::getMessage(EventLog& log)
{
	std::string message{ "" };
	switch (log.eventType) {
	case EventType::Start:
		message = log.actor + "의 탐험이 시작.";
		break;
	case EventType::DamageDealt:
		message = log.actor + "가 " + log.target + "에게 " + std::to_string(log.value) + "의 데미지를 입힘.";
		break;
	case EventType::DamageTaken:
		message = log.actor + "는 " + log.target + "에게 " + std::to_string(log.value) + "의 데미지를 받음.";
		break;
	case EventType::Death:
		message = log.actor + "는 " + log.target + "과의 전투에서 사망";
		break;
	case EventType::Kill:
		message = log.actor + "는 " + log.target + "을 처치하였음.";
		break;
	case EventType::Move:
		message = log.actor + "에서 구역 " + log.target + "으로 이동.";
		break;
	case EventType::LevelUp:
		message = log.actor + " 레벨 " + std::to_string(log.value) + "으로 상승.";
		break;
	case EventType::ObtainItem:
		message = log.actor + "가 " + log.target + "을(를) 획득.";
		break;
	case EventType::UseItem:
		message = log.actor + "가 " + log.target + "을(를) 사용.";
		break;
	case EventType::Return:
		message = log.actor + "는 육지로 무사히 복귀하였음.";
		break;
	}
	return message;
}


void GameLogger::log(EventType type, const std::string& actor)
{
	log(type, actor, "", 0);
}

void GameLogger::log(EventType type, const std::string& actor, int val)
{
	log(type, actor, "", val);
}

void GameLogger::log(EventType type, const std::string& actor, const std::string& target)
{
	log(type, actor, target, 0);
}


void GameLogger::log(EventType type, const std::string& actor, const std::string& target, int val)
{
	logs.push_back(EventLog{
		type,
		actor,
		target,
		val
	});
	statistic.LogToStatistic(type, target, val);
}

void GameLogger::printRecentLog(size_t count)
{
	//to-do 최근 count개의 로그를 출력, 이벤트에 맞게 적절한 내용으로.
	int currentidx = 0;
	//for (auto& log : std::vector<EventLog>(logs.rbegin(), logs.rend())) {
	for (auto& log : logs) {
		std::string message = getMessage(log);
		std::cout << message << '\n';

		if (count <= currentidx)
			break;
		else
			currentidx++;
	}
}

void GameLogger::printAllLogs()
{
	printRecentLog(logs.size());
}
