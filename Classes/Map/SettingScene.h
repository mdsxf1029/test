#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"
#include "BackgroundManager.h"

class Setting : public cocos2d::Scene
{
public:
    // 创建方法
    static cocos2d::Scene* createScene();
    // 初始化方法
    virtual bool init();
    // 声明小地图放大缩小的回调函数
    void onMouseScroll(cocos2d::Event* event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Setting);

private:
    BackgroundManager* _backgroundManager; // 背景管理实例

    // 设置按钮的回调函数
    void menuItemCallback1(Ref* sender, const std::string& backgroundImage);
    //
    cocos2d::MenuItemLabel* Setting::createTextButton(const std::string& text, const std::string& fontFile, int fontSize, const std::string& backgroundImage);


};
#endif // __HELLOWORLD_SCENE_H__