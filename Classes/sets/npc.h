#pragma once
#ifndef NPC_H
#define NPC_H

#include <string>
#include <string.h>
#include "elements.h"
#include "inventory.h"
#include "tasks.h"
#include "sets_variables.h"
#include "player.h"
#include "skills.h"
//友方
const std::string PRINCESS = "PRINCESS";//公主
const std::string KING = "KING";//国王
const std::string MINISTER = "MINISTER";//大臣

const std::string ClothesProvider = "ClothesProvider";//服装商
const std::string WeaponProvider = "WeaponProvider";//武器商
const std::string FoodProvider = "FoodProvider";//食品商
const std::string SkillProvider = "SkillProvider";//技能商

//`ClothesProvider` `WeaponProvider ` `FoodProvider ` `SkillProvider`

//敌方
const std::string HIGH_LEVEL_MONSTER = "HIGH_LEVEL_MONSTER";
const std::string LOW_LEVEL_MONSTER = "LOW_LEVEL_MONSTER";
const int ENEMY_ATTACK = 10;//初始化攻击力
const int ENEMY_HP = 25;//初始化防御力
//NPC类
class NPC
{
public:
	NPC()noexcept {};//默认构造函数
	NPC(const std::string name);//含参构造函数
	virtual ~NPC() {}; 
protected:

private:
	std::string name;
};

//友方NPC
class FriendNpc : public NPC
{
public:
	FriendNpc(const std::string name);
	 
	void GiveTask()  ;//给任务

protected:

private:
	std::string name;
	Task task;
};

//敌方NPC
class EnemyNpc : public NPC
{
	friend class Player;
	friend class Elements;
	friend class Skill;
	friend class LowLevelSkill;
	friend class MidLevelSkill;
	friend class HighLevelSkill;

public:
	friend class Player;
	friend class Elements;
	EnemyNpc(ElementType element, int level, LowLevelSkill& skill);//含参构造函数
	EnemyNpc(ElementType element, int level, MidLevelSkill& skill);//含参构造函数
	EnemyNpc(ElementType element, int level, HighLevelSkill& skill);//含参构造函数
	void Attack() 
	{
		//动画？
		//攻击
	};//攻击

	//受到伤害
	void TakeDamage(int damage);
	
	//狂暴
	void Frenzy();
protected:

private:
	std::string name;
	ElementType element;
	int maxHp;
	int hp;
	int basic_attack;
	int attack;
	int level;
	bool isAlive;
	Skill * skill;
};



#endif