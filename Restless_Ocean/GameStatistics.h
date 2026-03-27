#pragma once
#include <string>
#include <fstream>
#include "json.hpp"
#include "EventType.h"
#include <iostream>
#include <filesystem> // 파일 존재 확인용
#include <map>
using json = nlohmann::json;

class GameStatistics
{
private:
	const std::string fileName = "Statistics.json";
	json statisticData;
	std::map<std::string, int> data;
	void writeJsonFile() {
		try {
			std::ofstream file(fileName);
			if (!file.is_open()) {
				std::cerr << "파일 열기 실패: " << fileName << '\n';
				return;
			}

			file << statisticData.dump(4);
			file.close();
		}
		catch (const nlohmann::json::exception& e) {
			std::cerr << "JSON 저장 예외: " << e.what() << '\n';
		}
		catch (const std::exception& e) {
			std::cerr << "일반 예외: " << e.what() << '\n';
		}
	}
	GameStatistics() {
		std::ifstream f(fileName);
		if (f.good() && f.peek() != std::ifstream::traits_type::eof()) {
			try {
				f >> statisticData; // parse 대신 스트림 주입 방식이 더 안전함
			}
			catch (json::parse_error& e) {
				initializeData(); // 파싱 실패 시 초기화
			}
		}
		else {
			initializeData();
		}
	}
	void initializeData() {
		statisticData = {
			{"ExplorationCount", 0},
			{"DeathCount", 0},
			{"ReturnCount", 0},
			{"KillCount", json::object()},
			{"TotalKillCount", 0},
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
	void LogToStatistic(EventType type, const std::string& name, int val)
	{
		switch (type) {
		case EventType::Start:
			statisticData["ExplorationCount"] = statisticData.value("ExplorationCount", 0) + 1;
			break;

		case EventType::DamageDealt:
			statisticData["TotalDamageDealt"] = statisticData.value("TotalDamageDealt", 0) + val;
			break;

		case EventType::DamageTaken:
			if (!statisticData["DamageTakenBy"].is_object()) {
				statisticData["DamageTakenBy"] = json::object();
			}
			{
				int current = statisticData["DamageTakenBy"].value(name, 0);
				statisticData["DamageTakenBy"][name] = current + val;
			}
			statisticData["TotalDamageTaken"] = statisticData.value("TotalDamageTaken", 0) + val;
			break;

		case EventType::Death:
			statisticData["DeathCount"] = statisticData.value("DeathCount", 0) + 1;
			break;

		case EventType::Kill:
			if (!statisticData["KillCount"].is_object()) {
				statisticData["KillCount"] = json::object();
			}
			{
				int currentKill = statisticData["KillCount"].value(name, 0);
				statisticData["KillCount"][name] = currentKill + 1;
			}
			statisticData["TotalKillCount"] = statisticData.value("TotalKillCount", 0) + 1;
			break;

		case EventType::Move:
			break;

		case EventType::LevelUp:
			statisticData["TotalLevelUp"] = statisticData.value("TotalLevelUp", 0) + 1;
			break;

		case EventType::ObtainItem:
			statisticData["TotalItemGain"] = statisticData.value("TotalItemGain", 0) + 1;
			break;

		case EventType::UseItem:
			statisticData["TotalItemUse"] = statisticData.value("TotalItemUse", 0) + 1;
			break;

		case EventType::Return:
			statisticData["ReturnCount"] = statisticData.value("ReturnCount", 0) + 1;
			break;
		}

		writeJsonFile();
	}

	
};

