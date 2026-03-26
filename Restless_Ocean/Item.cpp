#include "Item.h"

Item::Item(string name, int price) : name(name), price(price) {}
Item::~Item() {}
string Item::getName() const { return name; }
int Item::getPrice() const { return price; }
void Item::clear() { name = ""; price = 0; }
void Item::printInfo() const { cout << "[이름: " << name << ", 가격: " << price << "G]" << endl; }

HealthPotion::HealthPotion(string name, int price, int heal)
    : Item(name, price), healthRestore(heal) {
}

void HealthPotion::use(Player* character) {
    if (!character) return;
    cout << "체력 포션 사용! 체력 +" << healthRestore << endl;
    character->recoverDamage(healthRestore);
}

AttackBoost::AttackBoost(string name, int price, int attack)
    : Item(name, price), attackIncrease(attack) {
}

void AttackBoost::use(Player* character) {
    if (!character) return;
    cout << "공격력 증가! 공격력 +" << attackIncrease << endl;
    character->addAttack(attackIncrease);
}
