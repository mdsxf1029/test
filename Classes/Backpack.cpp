#include "Backpack.h"

Backpack::Backpack() {}

Backpack::~Backpack() {}



void Backpack::addItem(const std::string& item)             //添加物品
{
    _items.push_back({ 1,item });
}

std::vector<item>& Backpack::getItems() 				   //获取物品
{
    return _items;
}
