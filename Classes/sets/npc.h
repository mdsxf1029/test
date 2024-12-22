#pragma once
#ifndef NPC_H
#define NPC_H

#include <string>
#include <string.h>
#include "elements.h"
#include "tasks.h"

#include "player.h"
#include "skills.h"
//友方
const std::string PRINCESS = "PRINCESS";									//公主
const std::string KING = "KING";											//国王
const std::string MINISTER = "MINISTER";									//大臣


// 鱼店  ，矿石店，蔬菜水果店，武器店  店长
const std::string FishStoreManager = "FishStoreManager";					//鱼店
const std::string OreStoreManager = "OreStoreManager";						//矿石店
const std::string VegetableStoreManager = "VegetableStoreManager";			//蔬菜店
const std::string WeaponStoreManager = "WeaponStoreManager";				//武器店

 
//敌方

constexpr int ENEMY_ATTACK = 10;											//初始化攻击力
constexpr int ENEMY_HP = 50;												//初始化血量
//NPC类
class NPC : public Sprite
{
public:
	NPC()noexcept {
		position = Vec2(0.0f, 0.0f);
	};//默认构造函数
	NPC(const std::string name);//含参构造函数
	virtual ~NPC() {};

	virtual const Vec2& getPosition() const { return this->position; };		//获取位置

protected:
	Vec2 position;															//位置
	std::string name;														//名字
};

//友方NPC
class FriendNpc : public NPC
{
public:
	FriendNpc(const std::string name);										//含参构造函数
	void GiveTask();														//给予任务
private:
	std::string name;														//名字
	Task task;																//任务
};

//敌方NPC
class EnemyNpc : public NPC
{
	friend class Player;
	friend class Elements;
	friend class Skill;
	friend class BattleSence;
public:
	EnemyNpc(ElementType element, int level, std::shared_ptr<Skill> skill, std::string filename);//含参构造函数 
	void TakeDamage(int damage);										//受到伤害
	void setPosition(Vec2 position);									//设置位置 
	bool initWithFile();												//加载图像

	int getHp() { return hp; }											//获取血量
	int getAttack() { return attack; }									//获取攻击力	
	int getLevel() { return level; }									//获取等级
	ElementType getElement() { return element; }						//获取元素属性
	std::shared_ptr<Skill> getSkill() { return skill; }					//获取技能
	std::string getFileName() { return filename; }						//获取文件名
	const Vec2& EnemyNpc::getPosition() { return this->position; };		//得到位置
	void dead() { isAlive = false; }									//死亡
private:
	//设定
	std::string name;													//名字
	ElementType element;												//元素属性
	int maxHp;															//最大血量
	int hp;																//血量
	int basic_attack;													//基础攻击力
	int attack;															//攻击力
	int level;															//等级
	std::string filename;												//文件名
	Vec2 position = Vec2(0.0f, 0.0f);									//位置
	//状态
	bool isAlive = true;												//初始化为存活状态
	bool isMoving = false;												//初始化为不在移动状态
	std::shared_ptr<Skill> skill;										//技能	
};



#endif