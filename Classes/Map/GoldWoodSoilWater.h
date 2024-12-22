// GoldWoodSoilWater.h  
#ifndef __GOLD_WOOD_SOIL_WATER_H__  
#define __GOLD_WOOD_SOIL_WATER_H__  


#include "cocos2d.h"  
#include "BackgroundManager.h"  

class Setting4 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();                                                                 // 创建场景
	virtual bool init();																				  // 初始化
	CREATE_FUNC(Setting4);																				  // 创建方法

private:
	BackgroundManager* _backgroundManager;																 // 背景管理器
	void onMouseScroll(cocos2d::Event* event);															 // 鼠标滚轮事件
	void menuItemCallback1(cocos2d::Ref* sender, const std::string& backgroundImage);					 // 菜单项回调函数
	void disableBigMapScrolling();																		 // 禁用大地图滚动
    // 确保这里有函数声明  
    cocos2d::MenuItemLabel* createTextButton(const std::string& text,
        const std::string& fontFile,
        int fontSize,
        const std::string& backgroundImage);
};

#endif // __GOLD_WOOD_SOIL_WATER_H__  
