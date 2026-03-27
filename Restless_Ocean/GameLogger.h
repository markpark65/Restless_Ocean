#pragma once
#include <ctime>
#include <string>
//#include <format>#c++20필요해서 사용불가.
#include <vector>
//#include <optional>#c++17필요해서 사용불가.
#include <stdexcept>
#include <iostream>
#include "EventType.h"
#include "GameStatistics.h"


struct EventLog {
	EventType eventType;
	std::string actor;
	std::string target;
	int value = 0;
};

class GameLogger
{
private:
	std::vector<EventLog> logs;
	std::string getMessage(EventLog& log);
	GameStatistics &statistic = GameStatistics::getInstance();
	GameLogger() {}
public:
	GameLogger(const GameLogger&) = delete;
	GameLogger& operator=(const GameLogger&) = delete;
	static GameLogger& getInstance() {
		static GameLogger instance;
		return instance;
	}
	~GameLogger() {}

	/// <summary>
	/// 단순 이벤트 로깅에 사용 -
	/// Start, Return
	/// </summary>
	/// <param name="type">이벤트 타입</param>
	/// <param name="actor"></param>
	void log(EventType type, const std::string& actor);

	/// <summary>
	/// 값이 존재하는 이벤트 로깅에 사용 -
	/// LevelUp, ObtainGold, UseGold
	/// </summary>
	/// <param name="type">이벤트 타입</param>
	/// <param name="actor"></param>
	/// <param name="val">변경후 레벨, 획득/사용한 아이템 수</param>
	void log(EventType type, const std::string& actor, int val);

	/// <summary>
	/// 대상의 이름이 있는 이벤트 로깅에 사용 -
	/// Kill, Death, ObtainItem, ObtainItem 예외:Move - A구역->B구역
	/// </summary>
	/// <param name="type">이벤트 타입</param>
	/// <param name="actor">플레이어 이름</param>
	/// <param name="target">죽인 또는 플레이어를 죽인 몬스터 이름</param>
	void log(EventType type, const std::string& actor, const std::string& target);

	/// <summary>
	/// 값을 주고받는 이벤트 로깅에 사용 -
	/// DamageTaken, DamageDealt
	/// </summary>
	/// <param name="type">이벤트 타입</param>
	/// <param name="actor">플레이어</param>
	/// <param name="target">대상자</param>
	/// <param name="val">값(예시 : 데미지)</param>
	void log(EventType type, const std::string& actor, const std::string& target, int val);

	/// <summary>
	/// 가장 최근의 로그를 출력하는 함수
	/// </summary>
	/// <param name="count">기본값은 1이며, 가장 최근 count개의 로그를 출력함.</param>
	void printRecentLog(size_t count = 1);

	/// <summary>
	/// 저장된 모든 로그 출력.
	/// </summary>
	void printAllLogs();

};

