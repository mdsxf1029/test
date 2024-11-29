#include "npc.h"
#include "tasks.h"
#include"sets_variables.h"
//基类 NPC类

//构造函数 传入名称
NPC::NPC(const std::string name) : name(name) 
{

} 

//子类
//友方NPC
//构造函数 传入task
FriendNpc::FriendNpc(const std::string name) : name(name)
{	 
	if (name == "KING")
		task = mainTask; //主任务
	//以下为副任务
	//可以更换为其他任务 重新设定
	else if (name == "ClothesProvider")
		task = sideTaskThree;
	else if (name == "WeaponProvider")
		task = sideTaskFour;
	else if (name == "FoodProvider")
		task = sideTaskFive;
	else if (name == "SkillProvider")
		task = sideTaskSix;
	else
		task = nonTask;
			
	
}

void FriendNpc::GiveTask()
{
	//给任务
//界面设置什么的。。
}


//敌方NPC   
//构造函数 传入元素类型和等级
EnemyNpc::EnemyNpc(ElementType element, int level) : element(element), level(level)
{
	hp = ENEMY_HP * level;
	basic_attack = ENEMY_ATTACK * level;
	attack = basic_attack;
}