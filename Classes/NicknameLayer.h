#ifndef __NICKNAMELAYER_H__
#define __NICKNAMELAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class NicknameLayer : public LayerColor {
public:
    NicknameLayer();
    ~NicknameLayer();
    virtual bool init();                                                            // 创建初始化方法 
	static NicknameLayer* create(); 											    // 创建静态创建方法
	std::string getNickname() const { return _textField->getString(); }			    // 获取昵称
    bool isValidCharacter(const char32_t ch);                                       // 添加验证字符的函数 
	bool isValidString(const std::string& str);									    // 添加验证字符串的函数
private:
    ui::TextField* _textField;                                                      // 输入框
};

#endif                                                                              // __NICKNAMELAYER_H__
#pragma once
