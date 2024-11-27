#pragma once

#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <string>
#include <iostream>

// 枚举表示元素类型
enum ElementType {
    Gold,
    Wood,
    Water,
    Fire,
    Earth,
    Count // 用于计算枚举的数量
};

class Element {
public:
    
    // 获取元素名称
    static std::string getElementName(ElementType type) {
        switch (type) {
            case Gold: return "Gold";   // 金
            case Wood: return "Wood";   // 木
            case Water: return "Water"; // 水
            case Fire: return "Fire";   // 火
            case Earth: return "Earth"; // 土
            default: return "Unknown";
        }
    }

    // 构造函数
    Element(ElementType type) : type(type) {}

    // 打印元素信息
    void printElement() const {
        std::cout << "Element: " << getElementName(type) << std::endl;
    }

private:
    ElementType type; // 存储元素类型
};

#endif // ELEMENTS_H
