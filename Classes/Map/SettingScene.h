// SettingScene.h  
#ifndef __SETTING_SCENE_H__  
#define __SETTING_SCENE_H__  

#include "cocos2d.h"  
#include "BackgroundManager.h"  
#include "MiniMap.h"
class Setting : public cocos2d::Scene
{
public:


    static cocos2d::Scene* createScene();
    virtual bool init();
    void createButton();
    CREATE_FUNC(Setting);

private:
    BackgroundManager* _backgroundManager;
    void onMouseScroll(cocos2d::Event* event);
    void menuItemCallback1(cocos2d::Ref* sender, const std::string& backgroundImage);
    void disableBigMapScrolling();
    void openBackpack();
    // 确保这里有函数声明  
    cocos2d::MenuItemLabel* createTextButton(const std::string& text,
        const std::string& fontFile,
        int fontSize,
        const std::string& backgroundImage);
};

#endif // __SETTING_SCENE_H__