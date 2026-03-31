#include "Player.h"
#include "Weapon.h"
#include "Monster.h"
#include "Random.h"
#include "Skill.h"
#include "InputSystem.h"
#include "TextUtility.h"
#include "GlobalVal.h"

using namespace std;

Player::Player(string n)
	: name(n)
	, level(1)
	, hp(200)
	, maxHp(200)
	, baseAttack(30)
	, exp(0)
	, maxExp(100)
	, gold(0)
	, oxygen(100)
	, maxOxygen(100)
	, speed(100)
	, baseSpeed(100)
	, pressure(0)
	, maxPressure(100)
	, battery(100)
	, maxBattery(100)
	, tempAttack(0)
	, artifactCount(0)
	, gachaCount(0)
	, inventory(10) {
	cout << "심해 탐사대원: " << name << " 이(가) 등록되었습니다!" << endl;
}
Player::~Player() {}
//상태 출력
void Player::showStatus() const {
	cout << "===============================" << endl;
	cout << "대원 정보 이름: " << name << " - level. " << level << endl;
	cout << "HP      : " << TextUtility::makeBar(hp, maxHp, 15, true) << hp << " / " << maxHp << endl;
	cout << "ATK     : " << baseAttack << endl;
	cout << "EXP     : " << TextUtility::makeBar(exp, maxExp, 15) << exp << " / " << maxExp << endl;
	cout << "GOLD    : " << gold << " G" << endl;
	cout << "===============================" << endl;
	cout << "O2      : " << TextUtility::makeBar(oxygen, 100, 15, true) << oxygen << " %" << endl;
	cout << "Battery : " << TextUtility::makeBar(battery, 100, 15, true) << battery << " %" << endl;
	cout << "Pressure: " << TextUtility::makeBar(pressure, 100, 15, true, true) << pressure << " %" << endl;
	cout << "Artifact: " << artifactCount << " / 3" << endl;
}
//레벨 로직
void Player::gainExp(int amount) {
	if (level >= 10) return;
	exp += amount;

	g_sceneData.description += std::to_string(amount) + "의 경험치를 획득했습니다. (현재: " + std::to_string(exp) + "/" + std::to_string(maxExp) + ") \n ";
	while (exp >= maxExp && level < 10) {
		levelUp();
	}
}
void Player::levelUp() {
	level++;
	int hpBonus = 30;
	int atkBonus = 8;

	maxHp += hpBonus;
	baseAttack += atkBonus;
	hp = maxHp;
	exp -= maxExp;
	if (exp < 0) exp = 0;

	g_sceneData.description += "Level UP!!!현재 레벨 : " + std::to_string(level) + " \n ";
	g_sceneData.description += "최대 체력 " + std::to_string(hpBonus) + " 증가 / 공격력 " + std::to_string(atkBonus) + " 증가 \n ";
  
	if (level == 3 || level == 6 || level == 9) {
		g_sceneData.description += "특정 레벨 도달! 고대의 기술 중 하나를 연마할 수 있습니다. \n ";

		int skillIdx = Random::getRandomValue(1, 3);
		unique_ptr<Skill> discoveredSkill;

		switch (skillIdx) {
		case 1:
			discoveredSkill = make_unique<TripleDamageSkill>();
			break;

		case 2:
			discoveredSkill = make_unique<BindSkill>();
			break;

		case 3:
			discoveredSkill = make_unique<CounterSkill>();
			break;
		}
		g_sceneData.description += "새롭게 발견한 기술 : [" + discoveredSkill->getName() + "] \n ";

		this->learnSkill(move(discoveredSkill));
	}
}

//무기 장착 구현
void Player::setWeapon(std::unique_ptr<Weapon> newWeapon) {
	if (!newWeapon) return;
	equippedWeapon = std::move(newWeapon);
	g_sceneData.description += name + " 대원이 " + equippedWeapon->getName() + "무기를 장착했습니다 \n ";
}

//무기 업그레이드
void Player::upgradeWeapon(int amount) {
	if (!equippedWeapon) {
		g_sceneData.description += "장착된 무기가 없습니다! \n ";
		std::cout << "장착된 무기가 없습니다!\n";
		return;
	}

	equippedWeapon->increaseDamage(amount);
}

//스킬 배우기
void Player::learnSkill(unique_ptr<Skill> newSkill) {
	if (!newSkill) return;
	if (currentSkill) {
		g_sceneData.description += "이미 스킬[" + currentSkill->getName() + "]을 보유 중입니다.  스킬로 교체하시겠습니까? \n ";
		g_sceneData.description += "1. 교체한다 (기존 기술 삭제)  2. 유지한다 (새 기술 버림) \n ";
		g_sceneData.options={
			"교체하기",
			"유지하기"
		};
		g_sceneData.selectedIndex = 0;

		int selectedIndex = g_cliRenderer.OptionSelector(g_sceneData);
		if (selectedIndex == 0) {
			currentSkill = move(newSkill);
			g_sceneData.description = "새로운 스킬을 배웠습니다! \n ";
		}
		else {
			g_sceneData.description = "기존 스킬을 유지합니다. \n ";
		}
	}
	else {
		currentSkill = move(newSkill);
		g_sceneData.description = "스킬 [" + currentSkill->getName() + "]을 습득했습니다! \n ";
	}
}
// 스킬 사용
bool Player::useSkill(Monster* target) {
	if (!currentSkill) {
		g_sceneData.description = "[알림] 배운 스킬이 없어 사용할 수 없습니다. \n ";
		return false;
	}
	int cost = currentSkill->getCost();
	if (getBattery() >= cost) {
		spendBattery(cost);
		g_sceneData.description = "[에너지] 스킬 발동을 위해 배터리 " + std::to_string(cost) + "%를 소모합니다. \n ";
		currentSkill->execute(this, target);
		return true;
	}
	else {
		g_sceneData.description = "[경고] 배터리가 부족합니다! (현재: " + std::to_string(getBattery()) + "% / 필요: "+ std::to_string(cost) + "%) \n ";
		return false;
	}
}
//공격 로직 구현
int Player::attack(const Monster* target) {
	if (!equippedWeapon) {
		return baseAttack + tempAttack;
	}
	return equippedWeapon->calculateDamage(baseAttack + tempAttack, target);
}
//데미지
void Player::takeDamage(int damage) {
	hp -= damage;
	g_sceneData.description += name + " 대원이 " + std::to_string(damage) + " 의 피해를 입었습니다. \n ";

	if (hp <= 0) {
		hp = 0;
		g_sceneData.description += name + " 대원이 쓰러졌습니다. 게임 오버. \n ";
	}
}

//체력 회복
void Player::recoverDamage(int amount) {
	int heal = amount;
	if (hp + amount > maxHp) heal = maxHp - hp;
	hp += heal;
	g_sceneData.description += name + " 대원의 체력이 " + std::to_string(heal) + "만큼 회복 됐습니다. (현재 HP: " +std::to_string(hp)+" / " + std::to_string(maxHp)+") \n ";
}

//체력 최대량 회복
void Player::increaseMaxHp(int amount) {
	maxHp += amount;
	g_sceneData.description += name + " 대원의 체력 최대량이 " + std::to_string(amount) + "만큼 증가 됐습니다. (현재 HP: " + std::to_string(hp) + " / " + std::to_string(maxHp) + ") \n ";
}

//산소 회복
void Player::recoverOxygen(int amount) {
	int heal = amount;
	if (oxygen >= maxOxygen) 
	{
		g_sceneData.description += "산소가 충분합니다.";
		//cout << "산소가 충분합니다." << endl;
		return;
	}
	if (oxygen + amount > maxOxygen) { heal = maxOxygen - oxygen; }
	oxygen += heal;
	g_sceneData.description += name + " 대원의 산소가 " + std::to_string(heal) + "만큼 회복 됐습니다. (현재 산소량: " + std::to_string(oxygen) + " / 100 ) \n ";
}

//산소 최대량 증가
void Player::IncreaseOxygen(int amount) {
	maxOxygen += amount;

	g_sceneData.description += name + " 대원의 최대 산소량이 " + std::to_string(amount) + " 증가했습니다! (최대 산소: " + std::to_string(maxOxygen) + ") \n ";
}

//산소 소모
void Player::useOxygen(int amount) {
	oxygen -= amount;
	if (oxygen < 0) oxygen = 0;
	if (oxygen > 10) {
		//10보다 많으면
		g_sceneData.description += "산소를 " + std::to_string(amount) + " % 소모했습니다. (남은 산소: " + std::to_string(oxygen) + " %) \n ";
	}
	else if (oxygen > 0 && oxygen <= 10) {
		//10이하(마지막 산소 소모)
		g_sceneData.description += "산소가 부족합니다. 산소를 회복하거나 지상으로 복귀하십시오. \n ";
	}
	else if (oxygen <= 0) {
		//고갈
		g_sceneData.description += "산소가 고갈됐습니다. 체력이 감소합니다. \n ";
		takeDamage(20);
	}
}
//배터리 소모(무기 사용 시)
bool Player::spendBattery(int amount) {
	if (battery >= amount) {
		battery -= amount;
		return true;
	}
	else {
		return false;
	}
}

//압력 감소
void Player::recoverPressure(int amount) {
	pressure -= amount;
	if (pressure < 0)
		pressure = 0;

	g_sceneData.description += "압력이 " + std::to_string(amount) + "% 감소했습니다. (현재 압력:" + std::to_string(pressure) + " %) \n ";
	
}

//압력 최대량 증가
void Player::IncreasePressure(int amount) {
	maxPressure += amount;
	g_sceneData.description += "압력 최대량이 " + std::to_string(amount) + " % 증가했습니다. (현재 압력 최대량" + std::to_string(maxPressure) + " %) \n ";
}

//압력 증가
void Player::takePressure(int amount) {
	pressure += amount;
	if (pressure > maxPressure)
		pressure = maxPressure;
	g_sceneData.description += "압력이 " + std::to_string(amount) + " % 증가했습니다. (현재 압력:" + std::to_string(pressure) + " %) \n ";
	if (pressure >= maxPressure) {
		//아래 속도 디버프와 중복출력
		g_sceneData.description += "압력이 너무 강합니다. 속도가 감소합니다.";
		debuffSpeed(50);
	}
}
//압력 증가로 속도 디버프
void Player::debuffSpeed(int reduction) {
	speed -= reduction;
	if (speed < 10)
		speed = 10;
	g_sceneData.description += "[디버프] 과도한 수압으로 몸이 무거워집니다! (현재 속도: " + std::to_string(speed)+") \n ";
}
void Player::resetSpeed() {
	speed = baseSpeed;
	g_sceneData.description += "수압이 해소되어 몸이 가벼워졌습니다! \n ";
}
//골드 획드
void Player::addGold(int amount) {
	gold += amount;
	g_sceneData.description += std::to_string(amount) + "G(보유 골드: " + std::to_string(gold) + "G) \n ";

}
//유적 발견
void Player::addArtifact(std::string name) {
	// 유적 중복 검사
	for (auto& artifact : artifacts)
	{
		if (artifact == name)
		{
			g_sceneData.description += name + "은 이미 발견한 유적입니다! \n ";
			g_sceneData.description += name + "현재 유적의 개수: " + std::to_string(artifactCount) + "개 \n ";
			return;
		}
	}
	artifacts.push_back(name);
	++artifactCount;
	g_sceneData.description += name + "을 발견했습니다. (현재 유적 개수: " + std::to_string(artifactCount) + "개) \n ";
	//cout << name<<"을 발견했습니다. (현재 유적 개수: " << ++artifactCount << "개)" << endl;
	if (artifactCount >= 3) {
		g_sceneData.sceneText = {
			"모든 유적을 모았습니다! 심해의 비밀이 드러납니다.",
			"심해의 잊혀진 왕국, '아틀란티스'의 기록을 모두 복원했습니다.",
			"축하합니다! 심해의 영웅이시여. ",
			"당신은 심연의 공포를 이겨내고 인류에게 금지된 지식을 가져왔습니다.",
			"당신의 이름은 고대 비석에 영원히 기록될 것입니다.",
		};
	}
}
//유적 확인
void Player::showArtifacts() const {

	g_sceneData.description = name + "===== 보유 유적 ===== \n ";

	for (int i = 0; i < artifacts.size(); i++) {
		g_sceneData.description += artifacts[i] + "\n";

	}

}

// 유적 개수 확인
bool Player::hasAllArtifacts() const
{
	return artifacts.size() >= 3;
}

//공격력 상승
void Player::addAttack(int amount) {
	baseAttack += amount;
	g_sceneData.description += "공격력이 " + std::to_string(amount) + "만큼 증가했습니다. (현재 ATK: " + std::to_string(baseAttack) + ") \n ";

}

//해당 전투에만 공격력 상승
void Player::addTempAttack(int amount) {
	tempAttack += amount;
	g_sceneData.description += "공격력이 " + std::to_string(amount) + "만큼 증가했습니다. (현재 ATK: " + std::to_string(baseAttack) + ") \n ";

}

//전투 종료시 tempAttack 초기화
void Player::resetTempStats() {
	tempAttack = 0;
}
//현재 스킬 받기
Skill* Player::getCurrentSkill() const {
	return currentSkill.get();
}
void Player::rechargeBattery(int amount) {
	int charge = amount;
	if (battery >= maxBattery)
	{
		g_sceneData.description += "배터리가 충분합니다. \n ";
		return;
	}
	if (battery + amount > maxBattery) { charge = maxBattery - battery; }
	battery += charge;

	g_sceneData.description += name + " 대원의 배터리가 " + std::to_string(charge) + "만큼 회복 됐습니다. (현재 배터리: " + std::to_string(battery) + " / 100) \n ";
}
