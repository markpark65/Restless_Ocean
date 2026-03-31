#include "Player.h"
#include "Item.h"
#include "Skill.h"
#include "GlobalVal.h"

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
	cout << "G, 필요 레벨: " << unlocklevel << "]";
}

std::string Item::tostring() const {
	std::string str = "[" + name;
	if (hideInfo()) {
		str += "]";
		return str;
	}else
		str += ", 가격" + std::to_string(price) + "G, 필요 레벨 : " + std::to_string(unlocklevel) + "]";
	return str;
}

//체력 회복
HealthPotion::HealthPotion(string name, int price, int heal,int unlocklevel)
	: Item(name, price, heal, unlocklevel) {
}
void HealthPotion::use(Player* character) {
    if (!character) return;
	g_sceneData.description += "체력 포션 사용! \n ";
    //cout << "체력 포션 사용! \n";
    character->recoverDamage(increaseAmount);
}
void HealthPotion::printInfo() const {
	std::cout << "[이름: " << name
		<< ", 가격: " << price << "G"
		<< ", 체력 회복량: +" << increaseAmount
		<< ", 필요 레벨: " << unlocklevel
		<< "]";
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
	g_sceneData.description += "방수가 잘 되어있는 초코과자 사용! \n ";
	//cout << "방수가 잘 되어있는 초코과자 사용! \n" ;
	character->increaseMaxHp(increaseAmount);
}
void MaxHpUp::printInfo() const {
	std::cout << "[이름: " << name
		<< ", 가격: " << price << "G"
		<< ", 최대 체력량 증가: +" << increaseAmount
		<< ", 필요 레벨: " << unlocklevel
		<< "]";
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
		g_sceneData.description += "강화 체력 포션 사용! \n ";
		//std::cout << "강화 체력 포션 사용!\n";
		player->recoverDamage(increaseAmount);
	}
void MegaHealthPotion::printInfo() const {
	std::cout << "[강화 체력 포션"
		<< ", 체력 회복량: +" << increaseAmount
		<< "]";
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
	g_sceneData.description += "산소 포션 사용! \n ";
    //cout << "산소 포션 사용! \n";
    character->recoverOxygen(increaseAmount);
}
void OxygenPotion::printInfo() const {
	std::cout << "[이름: " << name
		<< ", 가격: " << price << "G"
		<< ", 산소 회복량: +" << increaseAmount
		<< ", 필요 레벨: " << unlocklevel
		<< "]";
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
	g_sceneData.description += "1000년 전의 스노클 사용! \n ";
	//cout << "1000년 전의 스노클 사용!\n" ;
	character->IncreaseOxygen(increaseAmount);
}
void MaxOxygenUp::printInfo() const {
	std::cout << "[이름: " << name
		<< ", 가격: " << price << "G"
		<< ", 최대 산소량 증가: +" << increaseAmount
		<< ", 필요 레벨: " << unlocklevel
		<< "]";
}
Item* MaxOxygenUp::clone() const {
	return new MaxOxygenUp(*this);
}

//강화 산소 아이템
MegaOxygenPotion::MegaOxygenPotion()
	: Item("강화 산소 포션", 0, 100, 1){
}
void MegaOxygenPotion::use(Player* p) {
	g_sceneData.description += "강화 산소 포션 사용! \n ";
	//std::cout << "강화 산소 포션 사용!\n";
	p->recoverOxygen(increaseAmount);
}
Item* MegaOxygenPotion::clone() const {
	return new MegaOxygenPotion(*this);
}
void MegaOxygenPotion::printInfo() const {
	std::cout << "[강화 산소 포션"
		<< ", 산소 회복량: +" << increaseAmount
		<< "]";
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
	g_sceneData.description += "압력 포션 사용! \n ";
    //cout << "압력 포션 사용!\n";
    character->recoverPressure(increaseAmount);
	character->resetSpeed();
}
void PressurePotion::printInfo() const {
	std::cout << "[이름: " << name
		<< ", 가격: " << price << "G"
		<< ", 압력 회복량: -" << increaseAmount
		<< ", 필요 레벨: " << unlocklevel
		<< "]";
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
	g_sceneData.description += "어느 물고기의 부례 사용! \n ";
	//cout << "어느 물고기의 부례 사용!\n";
	character->IncreasePressure(increaseAmount);

}
void MaxPressureUp::printInfo() const {
	std::cout << "[이름: " << name
		<< ", 가격: " << price << "G"
		<< ", 최대 압력량 증가: +" << increaseAmount
		<< ", 필요 레벨: " << unlocklevel
		<< "]";
}
Item* MaxPressureUp::clone() const {
	return new MaxPressureUp(*this);
}

//강화 압력 포션
MegaPressurePotion ::MegaPressurePotion()
	: Item("강화 압력 포션", 0, 100, 1) {}

void MegaPressurePotion::use(Player* p) {
	g_sceneData.description += "강화 압력 포션 사용! \n ";
		//std::cout << "강화 압력 포션 사용! \n";
		p->recoverPressure(increaseAmount);
		p->resetSpeed();
	}
void MegaPressurePotion::printInfo() const {
	std::cout << "[강화 압력 포션"
		<< ", 최대 압력량: +" << increaseAmount
		<< "]";
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
	g_sceneData.description += "깨진 조개껍데기 목걸이 사용! \n ";
	//cout << "깨진 조개껍데기 목걸이 사용!\n";
	character->addTempAttack(increaseAmount);
}
void AttackBoost::printInfo() const {
	std::cout << "[이름: " << name
		<< ", 가격: " << price << "G"
		<< ", 공격력 증가: +" << increaseAmount
		<< ", 필요 레벨: " << unlocklevel
		<< "]";
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

	g_sceneData.description += "무기 강화 아이템 사용! \n ";
	//std::cout << "무기 강화 아이템 사용!\n";
	player->upgradeWeapon(increaseAmount);
}
void WeaponUpgrade::printInfo() const {
	std::cout << "[이름: " << name
		<< ", 가격: " << price << "G"
		<< ", 무기 강화: +" << increaseAmount
		<< ", 필요 레벨: " << unlocklevel
		<< "]";
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

