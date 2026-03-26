#include "Player.h"

using namespace std;

Player::Player(string n)
	: name(n)
	, level(1)
	, hp(200)
	, maxHp(200)
	, attack(30)
	, exp(0)
	, maxExp(100)
	, gold(0)
	, oxygen(100)
	, pressure(0)
	, battery(100)
	, artifactCount(0) {
	cout << "심해 탐사대원: " << name << " 이(가) 등록되었습니다!" << endl;
}

//상태 출력
void Player::showStatus() const {
	cout << "===============================" << endl;
	cout << "대원 정보 이름: " << name << " - level. " << level << endl;
	cout << "HP      :" << hp << " / " << maxHp << endl;
	cout << "ATK     :" << attack << endl;
	cout << "EXP     :" << exp << " / " << maxExp << endl;
	cout << "GOLD    :" << gold << " G" << endl;
	cout << "===============================" << endl;
	cout << "O2      :" << oxygen << " %" << endl;
	cout << "Battery :" << battery << " %" << endl;
	cout << "Pressure:" << pressure << " %" << endl;
	cout << "Artifact:" << artifactCount << " / 5" << endl;
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

//채력 회복
void Player::recoverDamage(int amount) {
	int heal = amount;
	if (hp + amount > maxHp) heal = maxHp - hp;
	hp += heal;
	cout << name << " 대원의 체력이 " << heal << "만큼 회복 됐습니다. (현재 HP: " << hp << " / " << maxHp << ")" << endl;
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
void Player::spendBattery(int amount) {
	battery -= amount;
	if (battery < 0) battery = 0;
	cout << "배터리 " << amount << " % 소모했습니다. (현재 배터리: " << battery << " %)" << endl;
}
//압력 증가
void Player::takePressure(int amount) {
	pressure += amount;
	if (pressure > 100) pressure = 100;
	cout << "압력이 " << amount << " % 증가했습니다. (현재 압력 " << pressure << " %)" << endl;
	if (pressure >= 100) {
		cout << "압력이 너무 셉니다. 체력이 감소합니다." << endl;
		takeDamage(20);
	}
}
//골드 획드
void Player::addGold(int amount) {
	gold += amount;
	cout << amount << "G를 획득했습니다. (보유 골드: " << gold << "G)" << endl;

}
//유적 발견
void Player::addArtifact() {
	artifactCount++;
	cout << "고대 유적을 발견했습니다. (현재 유적 개수: " << artifactCount << "개)" << endl;
	if (artifactCount >= 5) {
		cout << "모든 유적을 모았습니다! 심해의 비밀이 드러납니다.\n";
		cout << "(대충왕국과 심해어들의 비밀)" << endl;
	}
}
//레벨 로직
void Player::gainExp(int amount) {

}
void Player::levelUp() {

}
//아이템 사용
void Player::useItem(string itemName) {
	cout << itemName << "을(를) 사용합니다." << endl;
	//아이템별 로직
}
//공격력 상승
void Player::addattack(int amount) {
	attack += amount;
	cout << "공격력이 " << amount << "만큼 증가했습니다. (현재 ATK: " << attack << ")" << endl;
}