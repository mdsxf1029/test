#include "npc.h"
#include "tasks.h"
#include"sets_variables.h"
#include"skills.h"
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
EnemyNpc::EnemyNpc(ElementType element, int level, LowLevelSkill& skill) : element(element), level(level), isAlive(true), skill(&skill)
{
	hp = ENEMY_HP * level;
	maxHp = hp;
	basic_attack = ENEMY_ATTACK * level;
	attack = basic_attack + skill.attack;
};

EnemyNpc::EnemyNpc(ElementType element, int level, MidLevelSkill& skill) : element(element), level(level), isAlive(true), skill(&skill)
{
	hp = ENEMY_HP * level;
	maxHp = hp;
	basic_attack = ENEMY_ATTACK * level;
	attack = basic_attack + skill.attack;
};


EnemyNpc::EnemyNpc(ElementType element, int level, HighLevelSkill& skill) : element(element), level(level), isAlive(true), skill(&skill)
{
	hp = ENEMY_HP * level;
	maxHp = hp;
	basic_attack = ENEMY_ATTACK * level;
	attack = basic_attack + skill.attack;
};

//敌人受到伤害
void EnemyNpc::TakeDamage(int damage)
{
	if ((hp - damage) > 0)
	{
		hp -= damage;
	}
	else
	{
		hp = 0;
		isAlive = false;
	}
}

//敌人半血 狂暴
void EnemyNpc::Frenzy()
{
	if (hp <= maxHp * 0.5)
	{
		attack += 10;
	}
};//狂暴