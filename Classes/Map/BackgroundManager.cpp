#include "BackgroundManager.h"

USING_NS_CC;

BackgroundManager::BackgroundManager(cocos2d::Node* parentNode) : _parentNode(parentNode), _background(nullptr) {
    // 创建初始背景精灵
	_background = Sprite::create("black.png");                                                                        // 创建背景精灵
    if (_background) {
		auto visibleSize = Director::getInstance()->getVisibleSize();                                                 // 获取可见区域的大小
		auto origin = Director::getInstance()->getVisibleOrigin();													  // 获取可见区域的原点
		_background->setAnchorPoint(Vec2(0.5f, 0.5f));																  // 设置锚点
		_background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));		  // 设置位置

        // 将背景添加到传入的父节点中
        _parentNode->addChild(_background, -1);                                                                       // 确保背景位于最底层
    }
    else {
		CCLOG("Error: Failed to create default background sprite.");                                                   // 输出错误信息
    }
}

void BackgroundManager::setBackground(const std::string& backgroundImage) {
    // 创建新的背景精灵
	auto newBackground = Sprite::create(backgroundImage);                                                              // 创建新背景精灵
    if (newBackground) {                                                                                
		newBackground->setAnchorPoint(Vec2(0.5f, 0.5f));															   // 设置锚点
		newBackground->setPosition(_background->getPosition());													       // 设置位置
        // 替换背景
        _parentNode->addChild(newBackground, 0);                                                                       // 将新背景添加到同一父节点
        _parentNode->removeChild(_background);                                                                         // 移除旧背景
		_background = newBackground;																				   // 更新背景指针
    }
    else {
		CCLOG("Error: Failed to create sprite with image %s", backgroundImage.c_str());								// 输出错误信息
    }
}
