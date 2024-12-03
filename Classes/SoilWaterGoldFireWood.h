// SoilWaterGoldFireWood.h  
#ifndef __SOIL_WATER_GOLD_FIRE_WOOD_H__  
#define __SOIL_WATER_GOLD_FIRE_WOOD_H__  

#include "cocos2d.h"  
#include "BackgroundManager.h"  

class Setting5 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Setting5);

private:
    BackgroundManager* _backgroundManager;
    void onMouseScroll(cocos2d::Event* event);
    void menuItemCallback1(cocos2d::Ref* sender, const std::string& backgroundImage);
    void disableBigMapScrolling();
    // 确保这里有函数声明  
    cocos2d::MenuItemLabel* createTextButton(const std::string& text,
        const std::string& fontFile,
        int fontSize,
        const std::string& backgroundImage);
};

#endif // __SOIL_WATER_GOLD_FIRE_WOOD_H__#pragma once
