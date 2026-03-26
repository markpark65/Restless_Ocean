#pragma once
#include <iostream>
#include"Item.h"
class Player;

template<typename T>
struct InventorySlot {
    T* item = nullptr;
    int quantity = 1;
};

template<typename T>
class Inventory {
public:
    Inventory(int capacity = 10)
        : capacity_(capacity > 0 ? capacity : 1), size_(0)
    {
        slots_ = new InventorySlot<T>[capacity_]();
    }

    ~Inventory() {
        for (int i = 0; i < size_; i++) {
            delete slots_[i].item;
        }
        delete[] slots_;
    }

    void addItem(T* item, int quantity = 1) {
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
            std::cout << "인벤토리가 꽉 찼습니다!" << endl;
            delete item;
        }
    }

    void useItem(int index, Player* character) {

        if (index < 0 || index >= size_) {
            std::cout << "잘못된 번호입니다." << endl;
            return;
        }
        slots_[index].item->use(character);
        slots_[index].quantity--;

        if (slots_[index].quantity <= 0)
            remove(index);
    }

    void printAll() const {
        if (size_ == 0) {
            std::cout << "인벤토리가 비어있습니다." << endl;
            return;
        }
        for (int i = 0; i < size_; i++) {
            std::cout << i << "번: ";
            slots_[i].item->printInfo();
            std::cout << "  수량: " << slots_[i].quantity << endl;
        }
    }

    void remove(int index) {
        if (index < 0 || index >= size_) return;
        delete slots_[index].item;
        for (int i = index; i < size_ - 1; i++)
            slots_[i] = slots_[i + 1];
        slots_[size_ - 1].item = nullptr;
        slots_[size_ - 1].quantity = 0;
        size_--;
    }

private:
    InventorySlot<T>* slots_;
    int capacity_;
    int size_;
};
