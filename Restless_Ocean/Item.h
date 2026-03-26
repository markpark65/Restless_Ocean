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

class AttackBoost : public Item {
public:
    AttackBoost(string name, int price, int attack);
    void use(Player* character) override;

private:
    int attackIncrease;
};

struct InventorySlot {
    Item* item;
    int quantity;
};

template<typename T>
class Inventory {
public:
    Inventory(int capacity = 10) : capacity_(capacity > 0 ? capacity : 1), size_(0) {
        slots_ = new InventorySlot[capacity_];
        for (int i = 0; i < capacity_; i++) {
            slots_[i].item = nullptr;
            slots_[i].quantity = 0;
        }
    }

    ~Inventory() {
        for (int i = 0; i < size_; i++) delete slots_[i].item;
        delete[] slots_;
    }

    void addItem(T item, int quantity = 1) {
        if (!item || quantity <= 0) return;

        for (int i = 0; i < size_; i++) {
            if (slots_[i].item->getName() == item->getName()) {
                slots_[i].quantity += quantity;
                delete item;
                return;
            }
        }

        if (size_ < capacity_) {
            slots_[size_].item = item;
            slots_[size_].quantity = quantity;
            size_++;
        }
        else {
            cout << "인벤토리가 꽉 찼습니다!" << endl;
            delete item;
        }
    }

    void useItem(int index, Player* character) {
        if (index < 0 || index >= size_) {
            cout << "잘못된 번호입니다." << endl;
            return;
        }

        slots_[index].item->use(character);
        slots_[index].quantity--;
        if (slots_[index].quantity == 0) removeItem(index);
    }

    void printAllItems() const {
        if (size_ == 0) { cout << "인벤토리가 비어있습니다." << endl; return; }
        for (int i = 0; i < size_; i++) {
            cout << i << "번: ";
            slots_[i].item->printInfo();
            cout << "  수량: " << slots_[i].quantity << endl;
        }
    }

private:
    InventorySlot* slots_;
    int capacity_;
    int size_;

    void removeItem(int index) {
        delete slots_[index].item;
        for (int i = index; i < size_ - 1; i++) slots_[i] = slots_[i + 1];
        slots_[size_ - 1].item = nullptr;
        slots_[size_ - 1].quantity = 0;
        size_--;
    }
};