 
#include "elements.h"
#include"sets_variables.h"


// 构造函数
Element::Element(ElementType type) {
	this->type = type;
};
//

// 获取元素名称
std::string Element::getElementName(ElementType type) {
	switch (type) {
		case Gold: return "Gold";   // 金
		case Wood: return "Wood";   // 木
		case Water: return "Water"; // 水
		case Fire: return "Fire";   // 火
		case Earth: return "Earth"; // 土
		default: return "Unknown";
	}
}



// 打印元素信息  有点不确定 可能会用上面的函数表达相同效果，看看后期怎么处理
void Element::printElement() const {
    std::cout << "Element: " << this->type << std::endl;
}

// 比较元素大小   运算符重载
// 金>木>土>水>火>金
// e为敌方元素
bool Element::operator>(const Element& e) const {
	if (type == Gold && e.type == Wood) return true;
	else if (type == Wood && e.type == Earth) return true;
	else if (type == Earth && e.type == Water) return true;
	else if (type == Water && e.type == Fire) return true;
	else if (type == Fire && e.type == Gold) return true;
	return false;
}
