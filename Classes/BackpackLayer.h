#ifndef __BACKPACK_LAYER_H__
#define __BACKPACK_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Backpack.h"  // 引入背包类
#include "Sets/items.h"      

USING_NS_CC;

class BackpackLayer : public Layer
{
public:
    // 构造和析构函数
    BackpackLayer();
    ~BackpackLayer();
     
    virtual bool init();                // 初始化函数
	static BackpackLayer* create();     // 创建静态的 create 方法，简化创建对象的过程
    void createBackpackUI();             // 创建并显示背包内容的函数
    void setBackpack(Backpack* backpack);// 设置背包数据（物品）

private:
    // 背包数据
    Backpack* _backpack;
    std::vector<Item*> _items;  // 存储物品的容器

};

#endif // __BACKPACK_LAYER_H__
