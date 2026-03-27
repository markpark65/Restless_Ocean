#pragma once
#include <string>
#include <fstream>
#include "json.hpp"
#include "EventType.h"
#include <iostream>
//#include <filesystem> // 파일 존재 확인용인데c++17
#include <map>
using json = nlohmann::json;

class GameStatistics
{
private:
	const std::string filePath = "Statistics.json";
	//const std::string folder = "GameLogs";
	json statisticData;//통계데이터가 담길 json

	void writeJsonFile();
	GameStatistics() {
		std::ifstream f(filePath);
		if (f.good() && f.peek() != std::ifstream::traits_type::eof()) {
			try {
				f >> statisticData; // parse 대신 스트림 주입 방식이 더 안전함
			}
			catch (json::parse_error& e) {
				initializeData(); // 파싱 실패 시 초기화하기
			}
		}
		else {
			initializeData();
		}
	}
	void initializeData() {
		//기록할 데이터 정의
		statisticData = {
			{"ExplorationCount", 0},
			{"ReturnCount", 0},
			{"DeathCount", 0},
			{"DeathByCount", json::object()},
			{"KillCount", json::object()},
			{"TotalKillCount", 0},
			{"DamageDealtTo", json::object()},
			{"TotalDamageDealt", 0},
			{"DamageTakenBy", json::object()},
			{"TotalDamageTaken", 0},
			{"TotalItemGain", 0},
			{"TotalItemUse", 0},
			{"TotalGoldGain", 0},
			{"TotalGoldUse", 0},
			{"TotalLevelUp", 0}
		};
		writeJsonFile(); // 초기 구조를 파일로 즉시 저장
	}
public:
	GameStatistics(const GameStatistics&) = delete;
	GameStatistics& operator=(const GameStatistics&) = delete;
	static GameStatistics& getInstance() {
		static GameStatistics instance;
		return instance;
	}
	~GameStatistics() {
		try {
			writeJsonFile();
		}
		catch (...) {
		}
	}
	void LogToStatistic(EventType type, const std::string& name, int val);
	void PrintStatistics();
};
