#include "BackgroundManager.h"

USING_NS_CC;

BackgroundManager::BackgroundManager(cocos2d::Node* parentNode) : _parentNode(parentNode), _background(nullptr) {
    // 创建初始背景精灵
    _background = Sprite::create("black.png");
    if (_background) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();
        _background->setAnchorPoint(Vec2(0.5f, 0.5f));
        _background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

        // 将背景添加到传入的父节点中
        _parentNode->addChild(_background, -1); // 确保背景位于最底层
    }
    else {
        CCLOG("Error: Failed to create default background sprite.");
    }
}

void BackgroundManager::setBackground(const std::string& backgroundImage) {
    // 创建新的背景精灵
    auto newBackground = Sprite::create(backgroundImage);
    if (newBackground) {
        newBackground->setAnchorPoint(Vec2(0.5f, 0.5f));
        newBackground->setPosition(_background->getPosition());

        // 替换背景
        _parentNode->addChild(newBackground, 0); // 将新背景添加到同一父节点
        _parentNode->removeChild(_background);   // 移除旧背景

        // 更新背景指针
        _background = newBackground;
    }
    else {
        CCLOG("Error: Failed to create sprite with image %s", backgroundImage.c_str());
    }
}
