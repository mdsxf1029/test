#pragma once

#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <string>
#include <iostream>

// 枚举表示元素类型
enum ElementType {
    Gold,
    Wood,
    Earth,
    Water,
    Fire,
    Count       // 用于枚举的数量
};
// 元素类
class Element {
public:
    //友元类
    friend class Player;
    friend class EnemyNpc;
    friend class Item;

    Element(ElementType type);                                                  // 构造函数
	std::string getElementName(ElementType type);								// 获取元素名称
	bool operator>(const Element& e) const; 									// 比较元素大小   金>木>土>水>火>金  
private:
    ElementType type;                                                           // 存储元素类型
};

#endif // ELEMENTS_H
