#pragma once
#include <iostream>
#include"InputSystem.h"
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

	int getSize() { return size_; }

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
            std::cout << "인벤토리가 꽉 찼습니다!\n" ;
            delete item;
        }
    }

	int selectItem() const {
		if (size_ == 0) {
			std::cout << "인벤토리가 비어있습니다.\n";
			return -1;
		}
		printAll();
		std::cout << "사용할 아이템 번호 선택 (-1: 취소)\n";
		int choice = InputSystem::getInputInt(-1, size_ - 1);
		if (choice == -1) {
			std::cout << "취소했습니다.\n";
			return -1;
		}

		return choice;
	}

    void useItem(int index, Player* player) {

        if (index < 0 || index >= size_) {
            std::cout << "잘못된 번호입니다.\n" ;
            return;
        }
        slots_[index].item->use(player);
        slots_[index].quantity--;

        if (slots_[index].quantity <= 0)
            remove(index);

    }

    void printAll() const {
        if (size_ == 0) {
            std::cout << "인벤토리가 비어있습니다.\n" ;
            return;
        }
        for (int i = 0; i < size_; i++) {
            std::cout << i << "번: ";
            slots_[i].item->printInfo();
			std::cout << "수량: " << slots_[i].quantity << "\n";
        }
    }

	T* getItem(int index) const {
		if (index < 0 || index >= size_) return nullptr;
		return slots_[index].item;
	}

	int getItemCount(int index) const {
		if (index < 0 || index >= size_) return 0;
		return slots_[index].quantity;
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

	void removeItem(int index, int quantity) {
		if (index < 0 || index >= size_ || quantity <= 0) return;

		if (slots_[index].quantity > quantity) {
			slots_[index].quantity -= quantity;
		}
		else {
			remove(index);
		}
	}

private:
    InventorySlot<T>* slots_;
    int capacity_;
    int size_;
};
