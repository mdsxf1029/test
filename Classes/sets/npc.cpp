#include "npc.h"
//基类 NPC类

//构造函数 传入名称
NPC::NPC(const std::string& name) : name(name) {};
//析构函数
NPC::~NPC() {};

//子类
//友方NPC
//构造函数 传入task
FriendNpc::FriendNpc(){
	switch (name)
	{
		case King:
			task = mainTask; //主任务
			break; 
		//以下为副任务
		//可以更换为其他任务 重新设定
		case ClothesProvider:
			task = sideTaskThree;
			break;
		case WeaponProvider:
			task = sideTaskFour;
			break;
		case FoodProvider:
			task = sideTaskFive;
			break;
		case SkillProvider:
			task = sideTaskSix;
			break;
		default:
			task = nontask;
			break;
	}
}

void FriendNpc::GiveTask()
{
	//给任务
//界面设置什么的。。
}


//敌方NPC   
//构造函数 传入元素类型和等级
EnemyNpc::EnemyNpc(ElemntType& element, int level) : element(element), level(level)
{
	hp = HP * level;
	basic_attack = ATTACK * level;
	attack = basic_attack;
}