#pragma once
#ifndef __BOSSMAP_INTERACTION_H__
#define __BOSSMAP_INTERACTION_H__

#include "cocos2d.h"  
#include "Map/Map.h"
#include "Sets/items.h"
#include "Sets/npc.h"

class BossMapInteraction : public cocos2d::Scene
{
public:
    virtual bool init();
    virtual void loadMapData();
    CREATE_FUNC(BossMapInteraction);

    void onEnter();  // 监听鼠标点击事件
    void onExit();   // 退出时移除监听
    void PickUpInteraction(Item* item);
private:
    void checkItemClick(const cocos2d::Vec2& touchLocation);  // 检查物品是否被点击
    bool checkPlayerPosition(const cocos2d::Vec2& playerPosition);

    Map map;  // 地图对象
    std::vector<Item*> items;  // 存储所有可以交互的物品
    Item* selectedItem;  // 被选中的物品

    // 定义一个结构体来存储碰撞对象的信息
    struct CollisionItem
    {
        int id;          // 碰撞对象的 ID
        cocos2d::Vec2 position;  // 碰撞对象的位置
    };

    // 存储碰撞对象的容器
    std::vector<CollisionItem> collisionItems;
    // 存储物品的容器
    std::vector<Item> goldoreItems;

    // 碰撞检测阈值，单位：像素
    float collisionThreshold = 50.0f;  // 根据实际情况调整阈值
};

#endif // __BOSSMAP_INTERACTION_H__
