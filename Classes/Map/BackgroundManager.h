#ifndef __BACKGROUND_MANAGER_H__
#define __BACKGROUND_MANAGER_H__

#include "cocos2d.h"

class BackgroundManager {
public:
	explicit BackgroundManager(cocos2d::Node* parentNode);                                                      // 构造函数
	void setBackground(const std::string& backgroundImage);														// 设置背景

private:
    cocos2d::Node* _parentNode;																					// 用于存放背景的父节点
    cocos2d::Sprite* _background;																				// 当前背景精灵
};

#endif // __BACKGROUND_MANAGER_H__
