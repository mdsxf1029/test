#include "items.h"
#include "player.h" 

class Player;                               //前置声明

//基类
void Item::pick()                           //拾取
{
	if (!inBag)								//如果不在背包中
		inBag = true;						//拾取
}

void  Item::drop()                          //放下
{
	if (!inBag)								//如果不在背包中
		inBag = false;						//放下  不放入背包
}

void Item::equip()                          //装备
{
	if (inBag && isEquiped == false)		//如果在背包中
		isEquiped = true;					//装备	
}

void Item::unequip()                        //卸下
{
	if (inBag && isEquiped)					//如果在背包中 且 装备
		isEquiped = false;					//卸下	
}

void Item::upgrade() {}                     //升级，后面通过覆盖实现 对于武器和护具

void Item::discard()                        //丢弃
{
	if (inBag)								//如果在背包中
	{
		inBag = false;						//丢弃
		num = 0;							//数量为0
	}
}

bool Item::initwithFile(const std::string& filename)
{
	if (!Sprite::initWithFile(filename)) {
		std::cerr << "无法加载文件：" << filename << std::endl;
		return false;
	}
	return true;
}

//武器类 函数
void Weapon::equip()                        //装备
{
	Item::equip();							//调用基类的装备函数 
}

void Weapon::unequip()                      //卸下
{
	Item::unequip();						//调用基类的卸下函数 
}

void Weapon::upgrade()                      //升级
{
	if (inBag && level <= 3)
	{
		level++;							//升级
		attack += SIDE_UPGRADE_ATTACK;		//增加杀伤力
	}
}

//装备类 函数
void Armor::equip()                         //装备
{
	if (inBag && !isEquiped)
	{
		isEquiped = true;					//装备
	}
}

void Armor::unequip()                       //卸下
{
	if (inBag && isEquiped)
	{
		isEquiped = false;					//卸下
	}
}

void Armor::upgrade()                       //升级
{
	if (inBag && level <= 3)				//如果在背包中 且 等级小于等于3
	{
		level++;							//升级
		protect += SIDE_UPGRADE_PROTECT;	//增加防御力
	}
}

//食物类 函数
void Food::cook()                           //烹饪
{
	if (inBag && !isCooked)
	{
		isCooked = true;					//烹饪
		name = "Cooked " + name;			//名字改变
		value = BASIC_VALUE * 8;			//价值改变
	}
}

void Food::eat()                            //食用
{
	if (inBag && num != 0)
	{
		num--;								//数量减少
		if (num == 0){}                     //不显示图像
	}
}

//材料类
void GameMaterial::use()					//使用
{
	if (inBag)	
	{
		num--;						  	    //数量减少
		if (num == 0) {}                    //不显示图像
	}
}

//任务物品类
void TaskItem::Finish()                     //完成任务
{
	if (num == 5)							//如果数量为5
	{
											//完成任务
		num = 0;							//数量清零 
		isFinished = true;					//完成 
	}
}


