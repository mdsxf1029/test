#ifndef __BACKPACK_H__
#define __BACKPACK_H__

#include <vector>
#include <string>
#include "Sets/manager.h"
struct item {
    int num;
    std::string name;
};
class Backpack
{
public:
    Backpack();
    ~Backpack();

    
	void addItem(const std::string& item);  // 添加物品

    std::vector<item>& getItems() ;         // 获取背包中的所有物品
 
    std::vector<item> _items;                // 存储物品
};

#endif // __BACKPACK_H__
