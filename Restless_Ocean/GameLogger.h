#pragma once
#include <ctime>
#include <string>
//#include <format>#c++20필요해서 사용불가.
#include <vector>
//#include <optional>#c++17필요해서 사용불가.
#include <stdexcept>
#include <iostream>

enum class EventType {
	Start,			//게임시작(플레이어생성)
	Battle,			//전투(공격/방어)
	Death,			//사망
	Kill,			//처치
	Move,			//지역 이동,actor구역에서 target구역으로 이동
	LevelUp,		//레벨업
	ObtainItem,		//actor가 아이템 획득
	UseItem,		//아이템 사용
	Return			//육지로 복귀
};

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

