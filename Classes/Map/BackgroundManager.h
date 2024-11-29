#ifndef _BACKGROUND_MANAGER_H_
#define _BACKGROUND_MANAGER_H_

#include "cocos2d.h"

class BackgroundManager
{
public:
	//构造函数
	BackgroundManager(cocos2d::Scene* scene);

	void BackgroundManager::setBackground(const std::string& backgroundImage);

private:

	cocos2d::Node* _background;//背景精灵
	cocos2d::Scene* _scene;//当前背景引用

};

#endif