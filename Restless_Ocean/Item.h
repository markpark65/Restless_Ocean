#pragma once
#include <string>

class Player;

class Item {
public:
    virtual std::string getName() = 0;
    virtual void use(Player* character) = 0;

    virtual ~Item() {}
};


class HealthPotion : public Item {
public:
    HealthPotion();
    std::string getName()override;
    void use(Player* character)override;

private:
    std::string name;
    int healthRestore;

};

class AttackBoost : public Item {
public:
    AttackBoost();
    std::string getName()override;
    void use(Player* character)override;
private:
    std::string name;
    int attackincrease;

};