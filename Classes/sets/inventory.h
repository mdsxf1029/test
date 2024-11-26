#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>
#include "items.h"

class Inventory {
public:
	Inventory();
	~Inventory();
	void addItem(Item* item);
	void removeItem(Item* item);
	void removeItem(int index);
	Item* getItem(int index);
	int getSize();
	void clear();
	void showInventory();
protected:

private:
	std::vector<Item*> items;
};

#endif