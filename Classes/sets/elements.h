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
// 元素类
class Element {
public:
    // 构造函数
    Element(ElementType type);
	// 析构函数
	~Element() {};

	// 获取元素名称    也许不定义为成员函数更好。
    static std::string getElementName(ElementType type);

    // 打印元素信息
    void printElement() const;

	// 比较元素大小
    // 金>木>土>水>火>金  
	bool operator>(const Element& e) const;

private:
    ElementType type; // 存储元素类型
};

#endif // ELEMENTS_H
