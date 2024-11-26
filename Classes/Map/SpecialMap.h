#ifndef SPECIAL_MAP_H
#define SPECIAL_MAP_H

#include "BaseMap.h"

class SpecialMap : public BaseMap {
public:
    // 构造函数和析构函数
    SpecialMap();
    virtual ~SpecialMap();

    // 重写加载地图函数
    virtual void loadMap(const std::string& mapFile) override;

    // 重写交互处理函数
    virtual void handleInteraction(const cocos2d::Vec2& position) override;

    // 增加迷宫生成逻辑
    void generateMaze();

    // 增加战斗触发逻辑
    void triggerBattle(const cocos2d::Vec2& position);
};

#endif // SPECIAL_MAP_H
#pragma once
