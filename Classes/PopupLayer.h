#ifndef __POPUP_LAYER_H__
#define __POPUP_LAYER_H__

#include "cocos2d.h"

class PopupLayer : public cocos2d::LayerColor {
public:
    PopupLayer();
    ~PopupLayer();

    // 创建方法
    static PopupLayer* create(const std::string& message);

    // 初始化
    bool init(const std::string& message);

private:
    cocos2d::Label* _messageLabel;
};

#endif // __POPUP_LAYER_H__
#pragma once
