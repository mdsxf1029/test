#include "BackgroundManager.h"

USING_NS_CC;

BackgroundManager::BackgroundManager(cocos2d::Scene* scene) : _scene(scene)
{
    // 创建默认背景为白色
    _background = Sprite::create("BigMap.png");
    if (_background) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();
        _background->setAnchorPoint(Vec2(0.5f, 0.5f));
        _background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
        _scene->addChild(_background, 0, 100); // 设置背景的 tag 为 100
    }
    else {
        CCLOG("Error: Failed to create default background sprite.");
    }
}

void BackgroundManager::setBackground(const std::string& backgroundImage)
{
    // 从文件路径创建新背景精灵
    auto newBackground = Sprite::create(backgroundImage);
    if (newBackground) {
        // 设置新背景精灵的位置与旧背景一致
        newBackground->setAnchorPoint(Vec2(0.5f, 0.5f));
        newBackground->setPosition(_background->getPosition());

        // 将新背景添加到场景，替换旧背景
        _scene->addChild(newBackground, 0, 100); // 设置背景的 tag 为 100
        _scene->removeChild(_background); // 移除旧背景

        // 更新背景指针
        _background = newBackground;
    }
    else {
        // 如果加载失败，打印错误信息
        CCLOG("Error: Failed to create sprite with image %s", backgroundImage.c_str());
    }
}
