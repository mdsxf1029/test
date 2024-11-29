#include "items.h"

//基类
/
virtual void item::pick() = 0 {
	if (!in_bag)//如果不在背包中
		in_bag = true;//拾取
};//拾取

virtual void item::drop() = 0 {
	if (!in_bag)//如果不在背包中
		in_bag = false;//放下
//不放入背包
};//放下

virtual void item::discard() = 0 {
	if (in_bag)//如果在背包中
		in_bag = false;//丢弃
};//丢弃

virtual void item::equip() = 0 {
	if (in_bag)//如果在背包中
	{
		is_equiped = true;
	}
};//装备

virtual void item::unequip() = 0 {
	if (in_bag && is_equiped)//如果在背包中 且 装备
	{
		is_equiped = false;
	}
};//卸下

/*************************************************************************/

//武器类 函数

//升级
virtual void Weapon::upgrade() override 
{ 
	if(in_bag)
	{
		level++; //升级
		attack += UPGRADE_ATTACK;//增加杀伤力
	}
} 

//装备
virtual void Weapon::equip() override
{
	if (in_bag)
	{
		is_equiped = true;//装备
	}
}

/*************************************************************************/

//装备类 函数

virtual void upgrade() override
{
	if (in_bag && level <= 3)//如果在背包中 且 等级小于等于3
	{
		level++;//升级
		protect += UPGRADE_PROTECT;//增加防御力
	}
}

/*************************************************************************/

//食物类 函数

//食物类不需要升级
virtual void use() override
{
	if (in_bag)
	{
		//使用食物
	}
}

