#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>

class Item;//前置声明

constexpr int BAG_SIZE = 10;
//背包类
class Inventory {
public: 
	//界面
	void showInventory();//展示背包
	//操作
	bool addItem(Item* item);//添加物品
	void removeItem(Item* item);//移除物品
	void useItem(Item* item);//使用物品


	int getSize() const;//得到大小
	bool isFull();//是否满了
protected:

private:
	friend class Player;
	friend class Item;

	std::vector<Item*> items;//物品 指针 (items类定义内有数量)
	int size=BAG_SIZE;//背包大小
	int item_num=0;//物品数量
};


#endif