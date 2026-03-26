#pragma once
#include <string>
#include <iostream>
#include "Player.h"
using namespace std;

class Item {
public:
    Item(string name, int price);
    virtual ~Item();

    string getName() const;
    int getPrice() const;

    virtual void use(Player* character) = 0;
    void clear();
    void printInfo() const;

protected:
    string name;
    int price;
};


class HealthPotion : public Item {
public:
    HealthPotion(string name, int price, int heal);
    void use(Player* character) override;

private:
    int healthRestore;
};

class OxygenPotion : public Item {
public:
    OxygenPotion(string name, int price, int oxygen);
    void use(Player* character) override;

private:
    int oxygenIncrease;
};

class PressurePotion : public Item {
public:
    PressurePotion(string name, int price, int pressure);
    void use(Player* character) override;

private:
    int pressurePotion;
};

class AttackBoost : public Item {
public:
    AttackBoost(string name, int price, int attack);
    void use(Player* character) override;

private:
    int attackIncrease;
};

