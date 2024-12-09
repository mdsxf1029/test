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
const std::string PRINCESS = "PRINCESS";								//公主
const std::string KING = "KING";										//国王
const std::string MINISTER = "MINISTER";								//大臣
         

// 鱼店  ，矿石店，蔬菜水果店，武器店  店长
const std::string FishStoreManager = "FishStoreManager";				//鱼店
const std::string OreStoreManager = "OreStoreManager";					//矿石店
const std::string VegetableStoreManager = "VegetableStoreManager";		//蔬菜店
const std::string WeaponStoreManager = "WeaponStoreManager";			//武器店


//`FishStoreManager` `WeaponStoreManager ` `VegetableStoreManager ` `OreStoreManager`

//敌方

const int ENEMY_ATTACK = 10;											//初始化攻击力
const int ENEMY_HP = 25;												//初始化防御力
//NPC类
class NPC : public Sprite
{
public:
	NPC()noexcept {
		position = Vec2(0, 0);
	};//默认构造函数
	NPC(const std::string name);//含参构造函数
	virtual ~NPC() {};
	//virtual void setPosition(Vec2 position) { this->position = position; };//设置位置

	//获取位置
	virtual const Vec2& getPosition() const { return this->position; };

protected:
	Vec2 position;//位置
private:
	std::string name;

};

//友方NPC
class FriendNpc : public NPC
{
public:
	FriendNpc(const std::string name);

	void GiveTask();//给任务

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
	friend class BattleSence;
public:
	friend class Player;
	friend class Elements;
	EnemyNpc(ElementType element, int level, LowLevelSkill& skill);//含参构造函数
	EnemyNpc(ElementType element, int level, MidLevelSkill& skill);//含参构造函数
	EnemyNpc(ElementType element, int level, HighLevelSkill& skill);//含参构造函数


	//受到伤害
	void TakeDamage(int damage);

	//狂暴
	void Frenzy();

	//攻击玩家
	void AttackPlayer(Player& player)
	{
		//动画？
	}
	void Move();

private:
	std::string name;
	ElementType element;
	int maxHp;
	int hp;
	int basic_attack;
	int attack;
	int level;
	bool isAlive;
	bool isFrenzy = false;//初始化为非狂暴状态
	bool isMoving = false;//初始化为不在移动状态
	Skill* skill;
};



#endif