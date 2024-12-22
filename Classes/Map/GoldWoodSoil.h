// SoilWaterGold.h  
#ifndef __SOIL_WATER_GOLD_H__  
#define __SOIL_WATER_GOLD_H__  

#include "cocos2d.h"  
#include "BackgroundManager.h"  

class Setting3 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();                                                                       // 创建场景
	virtual bool init();																						// 初始化
	CREATE_FUNC(Setting3);																					    // 创建方法

private:
	BackgroundManager* _backgroundManager;																		// 背景管理器
	void onMouseScroll(cocos2d::Event* event);																	// 鼠标滚轮事件
	void menuItemCallback1(cocos2d::Ref* sender, const std::string& backgroundImage);							// 菜单项回调函数
	void disableBigMapScrolling();																				// 禁用大地图滚动
    // 确保这里有函数声明  
    cocos2d::MenuItemLabel* createTextButton(const std::string& text,
        const std::string& fontFile,
        int fontSize,
        const std::string& backgroundImage);
};

#endif // __SOIL_WATER_GOLD_H__#pragma once
