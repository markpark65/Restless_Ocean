#include "GameStatistics.h"



void GameStatistics::writeJsonFile() {
	try {
		std::ofstream file(filePath);
		if (!file.is_open()) {
			//std::cerr << "파일 열기 실패: " << filePath << '\n';
			return;
		}

		file << statisticData.dump(4);
		file.close();
	}
	catch (const nlohmann::json::exception& e) {
		//std::cerr << "JSON 저장 예외: " << e.what() << '\n';
	}
	catch (const std::exception& e) {
		//std::cerr << "일반 예외: " << e.what() << '\n';
	}
}

void GameStatistics::LogToStatistic(EventType type, const std::string& name, int val) {
		switch (type) {
		case EventType::Start:
			statisticData["ExplorationCount"] = statisticData.value("ExplorationCount", 0) + 1;
			break;

		case EventType::DamageDealt:
			if (!statisticData["DamageDealtTo"].is_object()) {
				statisticData["DamageDealtTo"] = json::object();
			}
			{
				int current = statisticData["DamageDealtTo"].value(name, 0);
				statisticData["DamageDealtTo"][name] = current + val;
			}
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
			if (!statisticData["DeathByCount"].is_object()) {
				statisticData["DeathByCount"] = json::object();
			}
			{
				int current = statisticData["DeathByCount"].value(name, 0);
				statisticData["DeathByCount"][name] = current + val;
			}

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

void GameStatistics::PrintStatistics() {
	std::cout << "탐사에 나선 횟수 : " << statisticData["ExplorationCount"] << '\n';
	std::cout << "탐사를 성공하고 돌아온 횟수 : " << statisticData["ReturnCount"] << '\n';
	std::cout << "탐사 실패한 횟수 : " << statisticData["DeathCount"] << '\n';
	std::cout << "탐사중 레벨업 횟수 : " << statisticData["TotalLevelUp"] << '\n';

	//처치횟수
	std::cout << "처치한 적의 숫자 : " << statisticData["TotalKillCount"] << '\n';
	auto& killLog = statisticData["KillCount"];
	for (auto& item : killLog.items()) {
		std::cout << '\t' << item.key() << " 처치 횟수 :" << item.value() << '\n';
	}

	//입힌 피해
	std::cout << "적들에게 입힌 피해량 : " << statisticData["TotalDamageDealt"] << '\n';
	auto& dealingLog = statisticData["DamageDealtTo"];
	for (auto& item : dealingLog.items()) {
		std::cout << '\t' << item.key() << "를 대상으로 준 피해 :" << item.value() << '\n';
	}

	//받은 피해
	std::cout << "적들의 공격을 버텨낸 량 : " << statisticData["TotalDamageTaken"] << '\n';
	auto& damagedLog = statisticData["DamageTakenBy"];
	for (auto& item : damagedLog.items()) {
		std::cout << '\t' << item.key() << "로부터 받은 피해 :" << item.value() << '\n';
	}

	std::cout << "탐사에서 찾은 아이템 수 : " << statisticData["TotalItemGain"] << '\n';
	std::cout << "탐사중 사용한 아이템 수 : " << statisticData["TotalItemUse"] << '\n';
	std::cout << "탐사에서 획득한 골드 : " << statisticData["TotalGoldGain"] << '\n';
	std::cout << "탐사중 사용한 골드 : " << statisticData["TotalGoldUse"] << '\n';
}
