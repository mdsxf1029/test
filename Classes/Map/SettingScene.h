// SettingScene.h  
#ifndef __SETTING_SCENE_H__  
#define __SETTING_SCENE_H__  

#include "cocos2d.h"  
#include "BackgroundManager.h" 
#include "Map/MiniMap.h"
USING_NS_CC;

class Setting : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();                                                                // 创建场景
	virtual bool init();																				 // 初始化场景
	void onBigMapButtonClicked(cocos2d::Ref* sender);													 // 大地图按钮点击事件
	CREATE_FUNC(Setting);																				 

private:
	BackgroundManager* _backgroundManager;																 // 背景管理器
	void onMouseScroll(cocos2d::Event* event);															 // 鼠标滚轮事件
	void menuItemCallback1(cocos2d::Ref* sender, const std::string& backgroundImage);				     // 菜单项回调函数
	void disableBigMapScrolling();																		 // 禁用大地图滚动

	cocos2d::MenuItemLabel* createTextButton(const std::string& text,							  		 // 创建文字按钮
        const std::string& fontFile,
        int fontSize,
        const std::string& backgroundImage);
};

#endif // __SETTING_SCENE_H__