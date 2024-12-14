
#include "tasks.h" 
#include"skills.h"
#include "npc.h"
#include<manager/manager.h>
//前置声明
class Skill;
class LowLevelSkill;
class MidLevelSkill;
class HighLevelSkill;

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
	/*
	if (name == "KING")
		task = mainTask; //主任务
	//以下为副任务
	//可以更换为其他任务 重新设定
	else if (name == "FishStoreManager")						//鱼店
		task = sideTaskThree;
	else if (name == "WeaponStoreManager")						//武器店
		task = sideTaskFour;
	else if (name == "VegetableStoreManager")					//蔬菜店
		task = sideTaskFive;
	else if (name == "OreStoreManager")							//矿石店
		task = sideTaskSix;
	else
		task = nonTask;
	*/
}

void FriendNpc::GiveTask()
{
	//给任务
//界面设置什么的。。
}


//敌方NPC   
//构造函数 传入元素类型和等级
 
EnemyNpc::EnemyNpc(ElementType element, int level, std::shared_ptr<LowLevelSkill>skill) : element(element), level(level), isAlive(true), skill(skill)
{
	hp = ENEMY_HP * level;
	maxHp = hp;
	basic_attack = ENEMY_ATTACK * level;
	attack = basic_attack + skill->attack;
};

EnemyNpc::EnemyNpc(ElementType element, int level, std::shared_ptr<MidLevelSkill> skill) : element(element), level(level), isAlive(true), skill(skill)
{
	hp = ENEMY_HP * level;
	maxHp = hp;
	basic_attack = ENEMY_ATTACK * level;
	attack = basic_attack + skill->attack;
};


EnemyNpc::EnemyNpc(ElementType element, int level, std::shared_ptr<HighLevelSkill> skill) : element(element), level(level), isAlive(true), skill(skill)
{
	hp = ENEMY_HP * level;
	maxHp = hp;
	basic_attack = ENEMY_ATTACK * level;
	attack = basic_attack + skill->attack;
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

//敌人移动
void EnemyNpc::Move()
{
	//移动
}

const Vec2& EnemyNpc::getPosition() const { return this->position; };
const void EnemyNpc::setPosition(Vec2 position)
{
	this->position = position;
	Sprite::setPosition(position);
};