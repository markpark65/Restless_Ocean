#include "Player.h"
#include "Weapon.h"
#include "Monster.h"
#include "Random.h"
#include "Skill.h"
#include "InputSystem.h"
#include "TextUtility.h"

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
	cout << amount << "의 경험치를 획득했습니다. (현재: " << exp << "/" << maxExp << ")" << endl;
	while (exp >= maxExp && level < 10) {
		levelUp();
	}
}
void Player::levelUp() {
	level++;
	int hpBonus = level * 20;
	int atkBonus = level * 5;

	maxHp += hpBonus;
	baseAttack += atkBonus;
	hp = maxHp;
	exp -= maxExp;
	if (exp < 0) exp = 0;

	cout << "=============================" << endl;
	cout << "Level UP!!! 현재 레벨: " << level << endl;
	cout << "최대 체력 " << hpBonus << " 증가 / 공격력 " << atkBonus << " 증가" << endl;
	cout << "=============================" << endl;

	if (level == 3 || level == 6 || level == 9) {
		cout << "특정 레벨 도달! 고대의 기술 중 하나를 연마할 수 있습니다." << endl;

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
		cout << "새롭게 발견한 기술 : [" << discoveredSkill->getName() << "] " << endl;

		this->learnSkill(move(discoveredSkill));
	}
}

//무기 장착 구현
void Player::setWeapon(std::unique_ptr<Weapon> newWeapon) {
	if (!newWeapon) return;
	equippedWeapon = std::move(newWeapon);
	cout << name << " 대원이 " << equippedWeapon->getName() << "무기를 장착했습니다";
}

//무기 업그레이드
void Player::upgradeWeapon(int amount) {
	if (!equippedWeapon) {
		std::cout << "장착된 무기가 없습니다!\n";
		return;
	}

	equippedWeapon->increaseDamage(amount);
}

//스킬 배우기
void Player::learnSkill(unique_ptr<Skill> newSkill) {
	if (!newSkill) return;
	if (currentSkill) {
		cout << "---------------------------------------------" << endl;
		cout << "이미 스킬[" << currentSkill->getName() << "]을 보유 중입니다." << endl;
		cout << "새 스킬 [" << newSkill->getName() << "]로 교체하시겠습니까?" << endl;
		cout << "1. 교체한다 (기존 기술 삭제)  2. 유지한다 (새 기술 버림)" << endl;

		if (InputSystem::getInputInt(1, 2) == 1) {
			currentSkill = move(newSkill);
			cout << "새로운 스킬을 배웠습니다!" << endl;
		}
		else {
			cout << "기존 스킬을 유지합니다." << endl;
		}
	}
	else {
		currentSkill = move(newSkill);
		cout << "\n스킬 [" << currentSkill->getName() << "]을 습득했습니다!\n";
	}
}
// 스킬 사용
bool Player::useSkill(Monster* target) {
	if (!currentSkill) {
		std::cout << "[알림] 배운 스킬이 없어 사용할 수 없습니다.\n";
		return false;
	}
	int cost = currentSkill->getCost();
	if (getBattery() >= cost) {
		spendBattery(cost);
		std::cout << "[에너지] 스킬 발동을 위해 배터리 " << cost << "%를 소모합니다.\n";
		currentSkill->execute(this, target);
		return true;
	}
	else {
		std::cout << "[경고] 배터리가 부족합니다! (현재: " << getBattery()
			<< "% / 필요: " << cost << "%)\n";
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
	cout << name << " 대원이 " << damage << " 의 피해를 입었습니다." << endl;

	if (hp <= 0) {
		hp = 0;
		cout << name << " 대원이 쓰러졌습니다. 게임 오버" << endl;
	}
}

//체력 회복
void Player::recoverDamage(int amount) {
	int heal = amount;
	if (hp + amount > maxHp) heal = maxHp - hp;
	hp += heal;
	cout << name << " 대원의 체력이 " << heal << "만큼 회복 됐습니다. (현재 HP: " << hp << " / " << maxHp << ")" << endl;
}

//체력 최대량 회복
void Player::increaseMaxHp(int amount) {
	maxHp += amount;
	cout << name << " 대원의 체력 최대량이 " << amount << "만큼 증가 됐습니다. (현재 HP: " << hp << " / " << maxHp << ")" << endl;
}

//산소 회복
void Player::recoverOxygen(int amount) {
	int heal = amount;
	if (oxygen >= maxOxygen) 
	{	cout << "산소가 충분합니다." << endl;
		return;
	}
	if (oxygen + amount > maxOxygen) { heal = maxOxygen - oxygen; }
	oxygen += heal;
	cout << name << " 대원의 산소가 " << heal << "만큼 회복 됐습니다. (현재 산소량: " << oxygen << " / 100 )" << endl;
}

//산소 최대량 증가
void Player::IncreaseOxygen(int amount) {
	maxOxygen += amount;
	cout << name << " 대원의 최대 산소량이 "
		<< amount << " 증가했습니다! (최대 산소: "
		<< maxOxygen << ")" << endl;
}

//산소 소모
void Player::useOxygen(int amount) {
	oxygen -= amount;
	if (oxygen < 0) oxygen = 0;

	if (oxygen > 0 && oxygen <= 10) cout << "산소가 부족합니다. 산소회복 혹은 지상으로 복귀하십쇼" << endl;
	
	cout << "산소를 " << amount << " % 소모했습니다. (남은 산소: " << oxygen << " %)" << endl;

	if (oxygen <= 0) {
		cout << "산소가 고갈됐습니다. 체력이 감소합니다." << endl;
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
	if (pressure < 0) pressure = 0;
	cout << "압력이 " << amount << "% 감소했습니다. (현재 압력 " << pressure << " %)" << endl;
	
}

//압력 최대량 증가
void Player::IncreasePressure(int amount) {
	maxPressure += amount;
	cout << "압력 최대량이 " << amount << " % 증가했습니다. (현재 압력 최대량" << maxPressure << " %)" << endl;
}

//압력 증가
void Player::takePressure(int amount) {
	pressure += amount;
	if (pressure > 100) pressure = 100;
	cout << "압력이 " << amount << " % 증가했습니다. (현재 압력 " << pressure << " %)" << endl;
	if (pressure >= 100) {
		cout << "압력이 너무 셉니다. 체력이 감소합니다." << endl;
		//takeDamage(20);
		debuffSpeed(50);
	}
}
//압력 증가로 속도 디버프
void Player::debuffSpeed(int reduction) {
	speed -= reduction;
	if (speed < 10) speed = 10;
	cout << "[디버프] 과도한 수압으로 몸이 무거워집니다! (현재 속도: " << speed << ")" << endl;
}
void Player::resetSpeed() {
	speed = baseSpeed;
	cout << "수압이 해소되어 몸이 가벼워졌습니다!" << endl;
}
//골드 획드
void Player::addGold(int amount) {
	gold += amount;
	cout << amount << "G (보유 골드: " << gold << "G)" << endl;

}
//유적 발견
void Player::addArtifact(std::string name) {
	// 유적 중복 검사
	for (auto& artifact : artifacts)
	{
		if (artifact == name)
		{
			std::cout << name << "은 이미 발견한 유적입니다!" << std::endl;
			std::cout << "현재 유적의 개수: " << artifactCount << "개" << std::endl;
			return;
		}
	}
	artifacts.push_back(name);
	cout << name<<"을 발견했습니다. (현재 유적 개수: " << ++artifactCount << "개)" << endl;
	if (artifactCount >= 3) {
		cout << "모든 유적을 모았습니다! 심해의 비밀이 드러납니다.\n";
		cout << "심해의 잊혀진 왕국, '아틀란티스'의 기록을 모두 복원했습니다." << endl
			<< "축하합니다! 심해의 영웅이시여. 당신은 심연의 공포를 이겨내고 인류에게 금지된 지식을 가져왔습니다." << endl
			<< "당신의 이름은 고대 비석에 영원히 기록될 것입니다." << endl;
	}
}
//유적 확인
void Player::showArtifacts() const {
	cout << "===== 보유 유적 =====\n";
	for (int i = 0; i < artifacts.size(); i++) {
		cout << "- " << artifacts[i] <<"\n";
	}
	cout << "\n";
}

// 유적 개수 확인
bool Player::hasAllArtifacts() const
{
	return artifacts.size() >= 3;
}

//공격력 상승
void Player::addAttack(int amount) {
	baseAttack += amount;
	cout << "공격력이 " << amount << "만큼 증가했습니다. (현재 ATK: " << baseAttack << ")" << endl;
}

//해당 전투에만 공격력 상승
void Player::addTempAttack(int amount) {
	tempAttack += amount;
	cout << "임시 공격력이 " << amount << "만큼 증가했습니다. (현재 ATK: "
		<< getAttack() << ")" << endl;
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
		cout << "배터리가 충분합니다." << endl;
		return;
	}
	if (battery + amount > maxBattery) { charge = maxBattery - battery; }
	battery += charge;
	cout << name << " 대원의 배터리가 " << charge << "만큼 회복 됐습니다. (현재 배터리: " << battery << " / 100 )" << endl;
}
