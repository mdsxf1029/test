// GoldWoodSoilWater.h  
#ifndef __GOLD_WOOD_SOIL_WATER_H__  
#define __GOLD_WOOD_SOIL_WATER_H__  


#include "cocos2d.h"  
#include "BackgroundManager.h"  

class Setting4 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Setting4);

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

#endif // __GOLD_WOOD_SOIL_WATER_H__  
