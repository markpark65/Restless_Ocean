#pragma once
#include <ctime>
#include <string>
#include <vector>



enum class EventType {
	Start,//게임시작(플레이어생성)
	Battle,//전투(공격/방어)
	BattleResult,//전투결과
	LevelUp,
	ObtainItem,//아이템 획득
	UseItem,//아이템 사용
	Ending//게임 결과
};

struct EventLog {
	struct tm* t;//기록 시간
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

public:

	static GameLogger& getInstance() {
		//메이어스 싱글톤
		static GameLogger instance;
		return instance;
	}
	~GameLogger() {}

	/// <summary>
	/// 로그를 기록하는 함수
	/// </summary>
	/// <param name="turn">현재 턴 수</param>
	/// <param name="actor">행동의 주체</param>
	/// <param name="target">행동의 대상</param>
	/// <param name="type">이벤트 타입, EventType참조.</param>
	/// <param name="val">공격 등의 행동일시 값 입력.</param>
	void log(int turn, std::string actor, std::string target, EventType type, int val = 0);

	/// <summary>
	/// 가장 최근의 로그를 출력하는 함수
	/// </summary>
	/// <param name="count">기본값은 1이며, 가장 최근 count개의 로그를 출력함.</param>
	void printRecentLog(int count = 1);

};

