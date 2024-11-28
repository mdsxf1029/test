#include "items.h"
#include"player.h"
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
	{
		in_bag = false;//丢弃
		num = 0;//数量为0
		//不显示图像
	}
}//丢弃

virtual void item::equip() = 0 {
	if (in_bag && is_equiped == false)//如果在背包中
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
	if (in_bag&&is_equiped==false)
	{
		is_equiped = true;//装备
	}
}

/*************************************************************************/

//装备类 函数
//升级
virtual void Armor::upgrade() override
{
	if (in_bag && level <= 3)//如果在背包中 且 等级小于等于3
	{
		level++;//升级
		protect += UPGRADE_PROTECT;//增加防御力
	}
}

/*************************************************************************/

//食物类 函数

//烹饪
virtual void Food::cook() override
{
	if (in_bag && !is_cooked)
	{
	//	烹饪
		is_cooked = true;//烹饪
	}
}

//食用
virtual void Food::eat() override
{
	if (in_bag)
	{
		hero.heal(healHp);//回复
		num--;//数量减少
		if (num == 0)
		{
			//不显示图像
		}
		//使用食物
	}
}

/*************************************************************************/

//材料类

//使用
virtual void Material::use() override
{
	//我想的是木头和石头可以用来生火  钻木取火吧，算是。
	if (in_bag)
	{
		//使用  
		num--;//数量减少
		if (num == 0)
		{
			//不显示图像
		}
	}
}


/**************************************************************************/

//任务物品类

//完成任务
virtual void Task::finish() override
{
	if (num == 5)//如果数量为5
	{
		//完成任务
		num = 0;//数量清零
		this->discard();//丢弃 
		//替换成另一个标志物

		//对话
		//最终决战
	}
}


