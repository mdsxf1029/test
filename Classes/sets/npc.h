#pragma once
#ifndef NPC_H
#define NPC_H

#include <string>
#include <string.h>
#include "elements.h"
#include "inventory.h"
 
//友方
const string PRINCESS = "PRINCESS";//公主
const string KING = "KING";//国王
const string MINISTER = "MINISTER";//大臣

const string ClothesProvider = "ClothesProvider";//服装商
const string WeaponProvider = "WeaponProvider";//武器商
const string FoodProvider = "FoodProvider";//食品商
const string SkillProvider = "SkillProvider";//技能商

//`ClothesProvider` `WeaponProvider ` `FoodProvider ` `SkillProvider`

//敌方
const stirng HIGH_LEVEL_MONSTER = "HIGH_LEVEL_MONSTER";
const stirng LOW_LEVEL_MONSTER = "LOW_LEVEL_MONSTER";
const int ATTACK = 10;//初始化攻击力
const int HP = 25;//初始化防御力
//NPC类
class NPC
{
public:
	NPC(const string& name) :name{ name } {};
	virtual ~NPC() {};

protected:

private:
	string name;
};

//友方NPC
class FriendNpc : public NPC
{
public:
	FriendNpc(const string& name) :name{ name } {};
	~FriendNpc() {};
	void GiveTask() {};//给任务

protected:

private:
	string name;

};

//敌方NPC
class EnemyNpc : public NPC
{
public:
	EnemyNpc(ElemntType & element,int level ) :element(element),level(level)
	{
		hp = HP*level;
		basic_attack = ATTACK * level;
		attack = basic_attack;
	};
	void Attack() 
	{
		//攻击
	};//攻击
	~EnemyNpc() {};
protected:

private:
	string name;
	ElementType element;
	int hp;
	int basic_attack;
	int attack;
	int level;

};

//友方NPC
FriendNpc princess(PRINCESS);//公主
FriendNpc king(KING);//国王
FriendNpc minister(MINISTER);//大臣

FriendNpc clothesProvider(ClothesProvider);//服装商
FriendNpc weaponProvider(WeaponProvider);//武器商
FriendNpc foodProvider(FoodProvider);//食品商
FriendNpc skillProvider(SkillProvider);//技能商


//怪物数量后期看看怎么处理
EnemyNpc highLevelFireMonster(ElementType::Fire, 2);//高级火怪物
EnemyNpc lowLevelFireMonster(ElementType::Fire, 1);//低级火怪物

EnemyNpc highLevelWaterMonster(ElementType::Water, 2);//高级水怪物
EnemyNpc lowLevelWaterMonster(ElementType::Water, 1);//低级水怪物

EnemyNpc highLevelWoodMonster(ElementType::Wood, 2);//高级木怪物
EnemyNpc lowLevelWoodMonster(ElementType::Wood, 1);//低级木怪物

EnemyNpc highLevelGoldMonster(ElementType::Gold, 2);//高级金怪物
EnemyNpc lowLevelGoldMonster(ElementType::Gold, 1);//低级金怪物

EnemyNpc highLevelEarthMonster(ElementType::Earth, 2);//高级土怪物
EnemyNpc lowLevelEarthMonster(ElementType::Earth, 1);//低级土怪物


#endif