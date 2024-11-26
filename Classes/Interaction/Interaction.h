#pragma once
#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <string>
#include <memory>
using namespace std;

// 抽象交互类
class Interactable 
{
public:
    virtual ~Interactable() = default;        // 虚析构函数
    virtual void Interact() = 0;              // 定义交互接口
    virtual bool IsInteractable() const = 0;  // 判断是否可以交互
    virtual string GetType() const = 0;       // 获取类型
    virtual string GetName() const = 0;       // 获取对象名称
};

#endif // INTERACTABLE_H