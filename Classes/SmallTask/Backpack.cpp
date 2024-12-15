#include "Backpack.h"
#include "items.h"
#include <memory>

Backpack::Backpack() = default;
Backpack::~Backpack() = default;

void Backpack::addItem(const std::string& itemName) {
    // Check if the item already exists in the backpack
    for (auto& existingItem : _items) {
        if (existingItem->getItemName() == itemName) {
            // Increment the quantity of the existing item
            existingItem->setNum(existingItem->getNum() + 1);
            return;
        }
    }

    //_items.push_back(newItem);
}

const std::vector<std::shared_ptr<Item>>& Backpack::getItems() const {
    return _items;
}
