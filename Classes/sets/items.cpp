#include "items.h"
#include"player.h" 
//前置声明
class Player;

//基类
//拾取
void Item::pick()
{
	if (!inBag)								//如果不在背包中
		inBag = true;						//拾取
}

//放下
void  Item::drop()
{
	if (!inBag)								//如果不在背包中
		inBag = false;						//放下  不放入背包
}

//装备
void Item::equip()
{
	if (inBag && isEquiped == false)		//如果在背包中
		isEquiped = true;					//装备	

}

//卸下
void Item::unequip()
{
	if (inBag && isEquiped)					//如果在背包中 且 装备
		isEquiped = false;					//卸下	

}
//升级										//后面通过覆盖实现 对于武器和护具
void Item::upgrade() {}


//丢弃
void Item::discard()
{
	if (inBag)								//如果在背包中
	{
		inBag = false;						//丢弃
		num = 0;							//数量为0
		//不显示图像
	}
}

/*************************************************************************/

//武器类 函数

//装备
void Weapon::equip()
{
	Item::equip();							//调用基类的装备函数 
}

//卸下
void Weapon::unequip()
{
	Item::unequip();						//调用基类的卸下函数 
}

//升级
void Weapon::upgrade()
{
	if (inBag && level <= 3)
	{
		level++;							//升级
		attack += SIDE_UPGRADE_ATTACK;		//增加杀伤力
	}
}


/*************************************************************************/

//装备类 函数
//升级

// 装备
void Armor::equip()
{
	if (inBag && !isEquiped)
	{
		isEquiped = true;					//装备
	}
}
//卸下
void Armor::unequip()
{
	if (inBag && isEquiped)
	{
		isEquiped = false;					//卸下
	}
}
//升级
void Armor::upgrade()
{
	if (inBag && level <= 3)				//如果在背包中 且 等级小于等于3
	{
		level++;							//升级
		protect += SIDE_UPGRADE_PROTECT;	//增加防御力
	}
}

/*************************************************************************/

//食物类 函数

//烹饪
void Food::cook()
{
	if (inBag && !isCooked)
	{
		isCooked = true;					//烹饪
		name = "Cooked " + name;			//名字改变
		value = BASIC_VALUE * 8;			//价值改变
	}
}

//食用
void Food::eat()
{
	if (inBag && num != 0)
	{
		num--;								//数量减少
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
void GameMaterial::use()					//我想的是木头和石头可以用来生火  钻木取火吧，算是。
{
	if (inBag)
	{
		//使用  
		num--;								//数量减少
		if (num == 0)
		{
			//不显示图像
		}
	}
}


/**************************************************************************/

//任务物品类

//完成任务
void TaskItem::Finish()
{
	if (num == 5)							//如果数量为5
	{
		//完成任务
		num = 0;							//数量清零
		this->discard();					//丢弃 
		//替换成另一个标志物
		isFinished = true;//完成
		//对话
		//最终决战
	}
}


