#ifndef __POPUP_LAYER_H__
#define __POPUP_LAYER_H__

#include "cocos2d.h"

class PopupLayer : public cocos2d::LayerColor {
public:
    PopupLayer();
    ~PopupLayer();
    static PopupLayer* create(const std::string& message);              // 创建方法
	bool init(const std::string& message);  					        // 初始化方法   
private:
	cocos2d::Label* _messageLabel;									    // 消息标签
};

#endif // __POPUP_LAYER_H__
#pragma once
