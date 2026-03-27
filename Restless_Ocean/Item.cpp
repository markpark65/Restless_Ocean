#include "Item.h"

Item::Item(string name, int price) : name(name), price(price) {}
Item::~Item() {}
string Item::getName() const { return name; }
int Item::getPrice() const { return price; }
void Item::clear() { name = ""; price = 0; }
void Item::printInfo() const { cout << "[이름: " << name << ", 가격: " << price << "G]" << endl; }

//체력 회복
HealthPotion::HealthPotion(string name, int price, int heal)
    : Item(name, price), healthRestore(heal) {
}
void HealthPotion::use(Player* character) {
    if (!character) return;
    cout << "체력 포션 사용! \n";
    character->recoverDamage(healthRestore);
}


//체력 최대량 Up
MaxHpUp::MaxHpUp(string name, int price, int heal)
	: Item(name, price), maxHpIncrease(heal) {
}
void MaxHpUp::use(Player* character) {
	if (!character) return;
	cout << "방수가 잘 되어있는 초코과자 사용! \n" ;
	character->increaseMaxHp(maxHpIncrease);
}


//산소 회복
OxygenPotion::OxygenPotion(string name, int price, int oxygen) 
:Item(name, price), oxygenIncrease(oxygen) {
}
void OxygenPotion::use(Player* character) {
    if (!character) return;
    cout << "산소 포션 사용! \n";
    character->recoverOxygen(oxygenIncrease);
}


//산소 최대량 Up
MaxOxygenUp::MaxOxygenUp(string name, int price, int oxygen)
: Item(name, price), maxIncrease(oxygen) {
}
void MaxOxygenUp::use(Player* character){
	if (!character) return;
	cout << "1000년 전의 스노클 사용!\n" ;
	character->IncreaseOxygen(maxIncrease);
}


//압력 해소
PressurePotion::PressurePotion(string name, int price, int pressure) 
:Item(name, price), pressurePotion(pressure) {
} 
void PressurePotion::use(Player * character) {
    if (!character) return;
    cout << "압력 포션 사용!\n";
    character->recoverPressure(pressurePotion);

}


//압력의 최대량 Up
MaxPressureUp::MaxPressureUp(string name, int price, int pressure)
: Item(name, price), maxIncrease(pressure) {
}
void MaxPressureUp::use(Player* character) {
	if (!character) return;
	cout << "어느 물고기의 부례 사용!\n";
	character->IncreasePressure(maxIncrease);

}


//공격력 Up
AttackBoost::AttackBoost(string name, int price, int attack)
	: Item(name, price), attackIncrease(attack) {
}
void AttackBoost::use(Player* character) {
	if (!character) return;
	cout << "깨진 조개껍데기 목걸이 사용!\n";
	character->addTempAttack(attackIncrease);
}


//클리어 아이템
Artifact ::Artifact(string name)
	: Item(name, 0) {
}

void Artifact::use(Player* character){
		cout << "유적 아이템은 사용할 수 없습니다.\n" ;
	}


