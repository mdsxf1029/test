#pragma once

#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <string.h>
#include "cocos2d.h" // 包含 Cocos2d-x 的所有基础设施
#include "math/Vec2.h" // 直接包含 Vec2 的定义

USING_NS_CC;
//命名
//武器 

const std::string  MAGIC_RING = "MAGIC_RING";//      魔法戒指 - Magic Ring
const std::string MAGIC_CRYSTAL = "MAGIC_CRYSTAL";// 魔法水晶 - Magic Crystal
const std::string MAGIC_SCROLL = "MAGIC_SCROLL";//   魔法卷轴 - Magic Scroll

//护具
const std::string HELMET = "HELMET";//头盔
const std::string ARMOR = "ARMOR";//盔甲
const std::string SHOES = "SHOES";//鞋子

//食品及杂物
const std::string FISH = "FISH";//鱼
const std::string FRUIT = "FRUIT";//水果
const std::string VEGETABLE = "VEGETABLE";//蔬菜
const std::string HERB = "HERB";//草药
const std::string MEAT = "MEAT";//肉
const std::string MUSHROOM = "MUSHROOM";//蘑菇
const std::string TREE = "TREE";//树
const std::string STONE = "STONE";//石头

//特殊物品
const std::string KEY = "KEY";//钥匙 
const std::string LETTER = "LETTER";//信件  可以是一个送信的任务物品


//数值
constexpr int SIDE_ATTACK = 10;//初始化攻击力 SIDE指武器技能方面
constexpr int SIDE_PROTECT = 5;//初始化防御力
constexpr int SIDE_UPGRADE_ATTACK = 5;//升级增加的攻击力
constexpr int SIDE_UPGRADE_PROTECT = 5;//升级增加的防御力

class Item : public Sprite {
public:

	Item()noexcept :inBag(false), isEquiped(false), num(0), id(0) {};//构造函数 默认不在背包内,数量为0
	virtual ~Item() {};//虚析构函数

	//如果不在背包中
	virtual void pick();//拾取
	virtual void drop(); //放下
	//如果在背包中
	virtual	void equip();//装备
	virtual void unequip();//卸下
	virtual void upgrade();//升级

	virtual void discard();//丢弃
	virtual void cook();//烹饪
	virtual void eat();//食用
	virtual void use();//使用
	int getNum() { return num; };//得到数量
	void setNum(int n) { num = n; };//设置数量
	//auto getTppe() { return type; };//得到类型
	virtual const std::string& getItemName() const { return "Item"; }

	virtual void setPosition(Vec2& position)
	{
		this->position = position;
	};//设置位置

	virtual const Vec2& getPosition() const
	{
		return position;
	}

protected:
	int id;
	bool inBag;//是否在背包中
	bool isEquiped;//是否装备
	int num;//数量
	Vec2 position;//位置
private:

};

//武器类
class Weapon : public Item {
public:
	Weapon() :name("Weapon"), attack(0), level(0), isEquiped(false), id(0) {};
	Weapon(const std::string& name) :name(name), attack(SIDE_ATTACK), level(0), isEquiped(false), id(0) {};
	~Weapon() {};

	void equip() override;//装备
	void unequip() override;//卸下
	void upgrade() override;//升级

	const std::string& getItemName() const override { return "Weapon"; }

protected:


private:
	int id;
	std::string name;
	int attack;
	int level;
	bool isEquiped;

};

//护具类
class Armor : public Item {
public:
	Armor(const std::string& name) :name(name), protect(SIDE_PROTECT), level(0), isEquiped(false), id(0) {};
	~Armor() override {};

	void equip() override;//装备
	void unequip() override;//卸下
	void upgrade() override;//升级
	const std::string& getItemName() const override { return "Armor"; };//得到名字

protected:

private:
	int id;
	std::string name;//名字
	int protect;//防御力
	int level;//等级
	bool isEquiped;//是否装备
};

//食品类
class Food : public Item {
public:
	Food(const std::string& name) :name(name), healHp(0), num(0), isEquiped(false), isCooked(false), isEaten(false), id(0) {};
	~Food() override {};
	void cook();//烹饪
	void eat();//食用
	const std::string& getItemName() const { return "Food"; };//得到名字

protected:

private:
	std::string name;//名字
	int healHp;//回复的血量
	bool isEquiped;//是否装备
	bool isCooked;//是否烹饪
	bool isEaten;//是否吃过
	int num;//数量
	int id;
};



//材料类 树 、石头等
class GameMaterial : public Item {
public:
	GameMaterial(const std::string& name) :name(name), is_used(false), num(0), id(0) {};
	~GameMaterial() override {};
	void use();//使用
	const std::string& getItemName() const { return "GameMaterial"; };//得到名字

protected:

private:
	std::string name;//名字
	bool is_used;//是否使用
	int num;//数量
	int id;
};

//任务物品类
class TaskItem : public Item {
public:
	TaskItem(const std::string& name) :name(name), id(0), isFinished(false) {};
	~TaskItem() {};
	void Finish();//完成
	const std::string& getItemName() const { return "TaskItem"; };//得到名字

protected:

private:
	std::string name;//名字 
	bool isFinished;//是否完成
	int id;
};


#endif
