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
	int act;//플레이어 입력마다 1씩 증가
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




	/// <param name="turn">현재 턴 수</param>
	/// <param name="type">이벤트 타입, EventType참조.</param>
	/// <param name="actor">행동의 주체</param>
	void log(int turn, EventType type, const std::string& actor);


	/// <param name="turn">현재 턴 수</param>
	/// <param name="type">이벤트 타입, EventType참조.</param>
	/// <param name="actor">행동의 주체</param>
	/// <param name="val">행동 값 입력.</param>
	void log(int turn, EventType type, const std::string& actor, int val);

	/// <param name="turn">현재 턴 수</param>
	/// <param name="type">이벤트 타입, EventType참조.</param>
	/// <param name="actor">행동의 주체</param>
	/// <param name="target">행동의 대상</param>
	void log(int turn, EventType type, const std::string& actor, const std::string& target);

	/// <param name="turn">현재 턴 수</param>
	/// <param name="type">이벤트 타입, EventType참조.</param>
	/// <param name="actor">행동의 주체</param>
	/// <param name="target">행동의 대상</param>
	/// <param name="val">공격 등의 행동일시 값 입력.</param>
	void log(int turn, EventType type, const std::string& actor, const std::string& target, int val);


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

