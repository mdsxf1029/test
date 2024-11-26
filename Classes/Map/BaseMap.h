#ifndef BASE_MAP_H
#define BASE_MAP_H

#include "cocos2d.h"
#include <map>
#include <string>

class BaseMap : public cocos2d::Node {
public:
    // 构造函数和析构函数
    BaseMap();
    virtual ~BaseMap();

    // 加载地图文件
    virtual void loadMap(const std::string& mapFile);

    // 处理交互（虚函数，子类可以重写）
    virtual void handleInteraction(const cocos2d::Vec2& position);

    // 更新探索状态（虚函数，子类可以重写）
    virtual void updateExploration(const cocos2d::Vec2& position);

    // 设置角色在地图中的位置
    void setPlayerPosition(const cocos2d::Vec2& position);

    // 获取角色当前位置
    cocos2d::Vec2 getPlayerPosition() const;

protected:
    cocos2d::TMXTiledMap* tiledMap;                // 当前地图的瓦片地图
    std::map<std::string, cocos2d::Vec2> locationPoints; // 地图上的交互点
    bool isExplored;                               // 是否已探索
    cocos2d::Vec2 playerPosition;                 // 角色当前位置
};

#endif // BASE_MAP_H

#pragma once
#pragma once
