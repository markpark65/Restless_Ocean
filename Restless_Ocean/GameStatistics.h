#pragma once
#include <string>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

class GameStatistics
{
private:
	const std::string fileName = "Statistics.json";
	json statisticData;
	void writeJsonFile() {
		std::ofstream o(fileName);
		o << std::setw(4) << statisticData << std::endl;
	}
	void readJsonFile() {
		std::ifstream f(fileName);
		json data = json::parse(f);
	}
public:
	GameStatistics() {
		std::ifstream f(fileName);
		if (f.good()) {
			readJsonFile();
		}
		else {
			statisticData["ExplorationCount"] = 0;	//탐사 횟수
			statisticData["DeathCount"] = 0;		//사망 횟수
			statisticData["KillCount"] = {};		//처치리스트{"이름" : 횟수}
			statisticData["TotalKillCount"] = 0;	//총 처치 횟수
			statisticData["TotalDamageDealt"] = 0;	//총 준 딜량
			statisticData["DamageTakenBy"] = {};	//몬스터별 받은 피해량
			statisticData["TotalDamageTaken"] = 0;	//총 받은 딜량
			statisticData["TotalGoldGain"] = 0;		//총 얻은 재화
			statisticData["TotalGoldUse"] = 0;		//총 사용한 재화
		}
	}
	~GameStatistics() {
		writeJsonFile();
	}
};

