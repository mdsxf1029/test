#ifndef __BACKPACK_H__
#define __BACKPACK_H__

#include <vector>
#include <string>
#include <memory>  // For shared_ptr

// Forward declaration of Item class
class Item;

class Backpack {
public:
    // Constructor and Destructor
    Backpack();
    ~Backpack();

    // Add an item to the backpack
    void addItem(const std::string& item);

    // Get all items in the backpack
    const std::vector<std::shared_ptr<Item>>& getItems() const;

private:
    std::vector<std::shared_ptr<Item>> _items;  // Stores items in the backpack
};

#endif // __BACKPACK_H__
