
#ifndef __OVER_MAP_H__  

#include "cocos2d.h"  

class Setting6 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();                                           // 创建场景  
	virtual bool init();															// 初始化
	CREATE_FUNC(Setting6);															// 创建方法

private:

	void onMouseScroll(cocos2d::Event* event);											// 鼠标滚轮事件
	void menuItemCallback1(cocos2d::Ref* sender, const std::string& backgroundImage);   // 菜单项回调函数
	void disableBigMapScrolling();														// 禁用大地图滚动
	// 确保这里有函数声明  
	cocos2d::MenuItemLabel* createTextButton(const std::string& text,
		const std::string& fontFile,
		int fontSize,
		const std::string& backgroundImage);											// 创建文字按钮
};

#endif // __SOIL_WATER_GOLD_FIRE_WOOD_H__#pragma once
#pragma once
