#ifndef __BACKPACK_H__
#define __BACKPACK_H__

#include <vector>
#include <string>
#include "manager.h"
struct item {
    int num;
    std::string name;
};
class Backpack
{
public:
    Backpack();
    ~Backpack();

    // 添加物品到背包
    void addItem(const std::string& item);

    // 获取背包中的所有物品
    std::vector<item>& getItems() ;


    std::vector<item> _items; // 存储物品
};

#endif // __BACKPACK_H__
