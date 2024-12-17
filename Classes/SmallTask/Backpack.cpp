#include "Backpack.h"

Backpack::Backpack() {}

Backpack::~Backpack() {}

void Backpack::addItem(const std::string& item)
{
    _items.push_back({ 1,item });
}

std::vector<item>& Backpack::getItems() 
{
    return _items;
}
