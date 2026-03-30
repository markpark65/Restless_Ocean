#include "Player.h"
#include "Item.h"
#include "Skill.h"

Item::Item(string name, int price, int increaseAmount, int unlocklevel)
	: name(name), price(price), increaseAmount(increaseAmount), unlocklevel(unlocklevel) {}
Item::~Item() {}
string Item::getName() const { return name; }
int Item::getPrice() const { return price; }
int Item::getIncreaseAmount() const { return increaseAmount; }
void Item::clear() { name = ""; price = 0; }
bool Item::isUnlocked(int playerLevel) const {
	return playerLevel >= unlocklevel;
}

void Item::printInfo() const {
	cout << "[이름: " << name;
	if (hideInfo()) {
		cout << "]";
		return;
	}
	cout << ", 가격: " << price;
	if (name == "체력 포션"){
		cout << "G, 체력 회복량: " << getIncreaseAmount();
	}
	else if (name == "산소 포션") {
		cout << "G, 산소 회복량: " << getIncreaseAmount();
	}
	else if (name == "압력 포션") {
		cout << "G, 압력 해소량: " << getIncreaseAmount();
	}
	else if (name == "방수가 잘 되어있는 초코과자") {
		cout << "G, 최대 체력 증가량: " << getIncreaseAmount();
	}
	else if (name == "1000년 전의 스노클") {
		cout << "G, 최대 산소 증가량: " << getIncreaseAmount();
	}
	else if (name == "어느 물고기의 부레") {
		cout << "G, 최대 압력 증가량: " << getIncreaseAmount();
	}
	else if (name == "깨진 조개껍데기 목걸이"){
		cout << "G, 공격력 30% 증가";
	}
	cout << ", 필요 레벨: " << unlocklevel << "]";
}

//체력 회복
HealthPotion::HealthPotion(string name, int price, int heal,int unlocklevel)
	: Item(name, price, heal, unlocklevel) {
}
void HealthPotion::use(Player* character) {
    if (!character) return;
    cout << "체력 포션 사용! \n";
    character->recoverDamage(increaseAmount);
}
Item* HealthPotion::clone() const {
	return new HealthPotion(*this);
}


//체력 최대량 Up
MaxHpUp::MaxHpUp(string name, int price, int heal,int unlocklevel)
	: Item(name, price, heal, unlocklevel) {
}
void MaxHpUp::use(Player* character) {
	if (!character) return;
	cout << "방수가 잘 되어있는 초코과자 사용! \n" ;
	character->increaseMaxHp(increaseAmount);
}
Item* MaxHpUp::clone() const {
	return new MaxHpUp(*this);
}


//강화 체력 포션
MegaHealthPotion::MegaHealthPotion()
		: Item("강화 체력 포션", 0, 100, 1){
	}

void MegaHealthPotion::use(Player* player) {
		if (!player) return;
		std::cout << "강화 체력 포션 사용!\n";
		player->recoverDamage(increaseAmount);
	}

Item* MegaHealthPotion:: clone() const {
		return new MegaHealthPotion(*this);
	}
bool MegaHealthPotion::hideInfo() const {
	return true;
}



//산소 회복
OxygenPotion::OxygenPotion(string name, int price, int oxygen,int unlocklevel) 
:Item(name, price, oxygen, unlocklevel) {
}
void OxygenPotion::use(Player* character) {
    if (!character) return;
    cout << "산소 포션 사용! \n";
    character->recoverOxygen(increaseAmount);
}
Item* OxygenPotion::clone() const {
	return new OxygenPotion(*this);
}


//산소 최대량 Up
MaxOxygenUp::MaxOxygenUp(string name, int price, int oxygen,int unlocklevel)
: Item(name, price, oxygen, unlocklevel) {
}
void MaxOxygenUp::use(Player* character){
	if (!character) return;
	cout << "1000년 전의 스노클 사용!\n" ;
	character->IncreaseOxygen(increaseAmount);
}
Item* MaxOxygenUp::clone() const {
	return new MaxOxygenUp(*this);
}

//강화 산소 아이템
MegaOxygenPotion::MegaOxygenPotion()
	: Item("강화 산소 포션", 0, 100, 1){
}
void MegaOxygenPotion::use(Player* p) {
	std::cout << "강화 산소 포션 사용!\n";
	p->recoverOxygen(increaseAmount);
}
Item* MegaOxygenPotion::clone() const {
	return new MegaOxygenPotion(*this);
}
bool MegaOxygenPotion::hideInfo() const {
	return true;
}


//압력 해소
PressurePotion::PressurePotion(string name, int price, int pressure,int unlocklevel) 
:Item(name, price, pressure, unlocklevel){
} 
void PressurePotion::use(Player * character) {
    if (!character) return;
    cout << "압력 포션 사용!\n";
    character->recoverPressure(increaseAmount);
	character->resetSpeed();
}
Item* PressurePotion::clone() const {
	return new PressurePotion(*this);
}


//압력의 최대량 Up
MaxPressureUp::MaxPressureUp(string name, int price, int pressure,int unlocklevel)
: Item(name, price, pressure, unlocklevel){
}
void MaxPressureUp::use(Player* character) {
	if (!character) return;
	cout << "어느 물고기의 부례 사용!\n";
	character->IncreasePressure(increaseAmount);

}
Item* MaxPressureUp::clone() const {
	return new MaxPressureUp(*this);
}

//강화 압력 포션
MegaPressurePotion ::MegaPressurePotion()
	: Item("강화 압력 포션", 0, 100, 1) {}

void MegaPressurePotion::use(Player* p) {
		std::cout << "강화 압력 포션 사용! \n";
		p->recoverPressure(increaseAmount);
		p->resetSpeed();
	}

Item* MegaPressurePotion::clone() const {
		return new MegaPressurePotion(*this);
	}
bool MegaPressurePotion::hideInfo() const {
	return true;
}


//공격력 Up
AttackBoost::AttackBoost(string name, int price, int attack,int unlocklevel)
	: Item(name, price, attack, unlocklevel) {
}
void AttackBoost::use(Player* character) {
	if (!character) return;
	cout << "깨진 조개껍데기 목걸이 사용!\n";
	character->addTempAttack(increaseAmount);
}

Item* AttackBoost::clone() const {
 	return new AttackBoost(*this);
}


//무기 강화
WeaponUpgrade::WeaponUpgrade(string name, int price, int atk, int unlocklevel)
	: Item(name, price, atk, unlocklevel)
{
}

void WeaponUpgrade::use(Player* player) {
	if (!player) return;

	std::cout << "무기 강화 아이템 사용!\n";
	player->upgradeWeapon(increaseAmount);
}

Item* WeaponUpgrade::clone() const
{
	return new WeaponUpgrade(*this);
}

//스킬북 사용
SkillBook::SkillBook(string name, unique_ptr<Skill> skill, int unlockLevel)
	: Item(name, 0, unlockLevel)
	, containedSkill(move(skill))
{ }
void SkillBook::use(Player* player) {
	if (containedSkill) {
		player->learnSkill(move(containedSkill));
	}
}

