#pragma once

#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <string.h>

//命名
//武器 

const string  MAGIC_RING = "MAGIC_RING";//      魔法戒指 - Magic Ring
const string MAGIC_CRYSTAL = "MAGIC_CRYSTAL";// 魔法水晶 - Magic Crystal
const string MAGIC_SCROLL = "MAGIC_SCROLL";//   魔法卷轴 - Magic Scroll

//护具
const string HELMET = "HELMET";//头盔
const string ARMOR = "ARMOR";//盔甲
const string SHOES = "SHOES";//鞋子
 
//食品及杂物
const string TREE = "TREE";//树
const string STONE = "STONE";//石头

const string FISH = "FISH";//鱼
const string FRUIT = "FRUIT";//水果
const string HERB = "HERB";//草药

//特殊物品
const string KEY = "KEY";//钥匙 
const string LETTER = "LETTER";//信件  可以是一个送信的任务物品


//数值
const int ATTACK = 10;//初始化攻击力
const int PROTECT = 5;//初始化防御力
const int UPGRADE_ATTACK = 5;//升级增加的攻击力
const int UPGRADE_PROTECT = 5;//升级增加的防御力

class Item {
public: 

	Item() :in_bag(false) {};//构造函数 默认不在背包内
	virtual ~Item() {};//虚析构函数

	//如果不在背包中
	virtual void pick() = 0 ;//拾取
	virtual void drop() = 0; //放下
	//如果在背包中
	virtual void discard() = 0;//丢弃
	virtual void equip() = 0; //装备
	virtual void unequip() = 0; //卸下
	virtual void upgrade() = 0; //升级
	virtual void use() = 0;//使用
	
protected:
	
	bool in_bag;//是否在背包中

private: 

};

//武器类
class Weapon : public Item {
public:
	Weapon(const std::string& name):name(name),attack(ATTACK),level(0),is_equiped(false) {};
	~Weapon() {};
	virtual void upgrade() override ;//升级
	virtual void equip() override;//拾取

protected: 

	
private:
	string name;
	int attack;
	int level;
	bool is_equiped;

};

//护具类
class Armor : public Item {
public:
	Armor(const std::string& name) :name(name), protect(PROTECT), level(0), is_equiped(false) {};
	~Armor() {};
	virtual void upgrade() override;//升级
protected:

private:

	string name;//名字
	int protect;//防御力
	int level;//等级
	bool is_equiped;//是否装备
};

//食品类
class Food : public Item {
public:


protected:

private:
	string name;//名字
	int heal_hp;//回复的血量
	int level;//等级
	bool is_equiped;//是否装备
	bool is_eaten;//是否吃过

};



//材料类 树 、石头等
class Material : public Item {
public:

protected:

private:
	string name;//名字
	int level;//等级
	bool is_equiped;//是否装备
};

//任务物品类
class TaskItem : public Item {
public:

protected:

private:
	string name;//名字 
	int num;//数量
};


#endif
