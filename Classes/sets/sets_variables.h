#pragma once
#ifndef SET_VARIABLES_H
#define SET_VARIABLES_H

#include<string>
#include<string.h>

#include "player.h"

//前置声明
class Player;
class Task;
class LowLevelSkill;
class MidLevelSkill;
class HighLevelSkill;
class Weapon;
class Armor;
class Food;
class GameMaterial;
class TaskItem;
class FriendNpc;
class EnemyNpc;
	

//玩家类 
extern Player hero;

//任务

extern Task mainTask;//主线任务
extern Task sideTaskOne;//副任务1
extern Task sideTaskTwo;//副任务2	
extern Task sideTaskThree;//副任务3
extern Task sideTaskFour;//副任务4
extern Task sideTaskFive;//副任务5
extern Task sideTaskSix;//副任务6
extern Task sideTaskSeven;//副任务7
extern Task nonTask;//无任务

//技能

extern LowLevelSkill elementSurge;//元素冲击
extern MidLevelSkill elementalTorrent;//元素洪流
extern HighLevelSkill energyVortex;//能量漩涡
//组合技能
extern HighLevelSkill arcaneBlast;//奥术爆发


//NPC

//友方NPC
extern FriendNpc princess;//公主
extern FriendNpc king;//国王
extern FriendNpc minister;//大臣

extern FriendNpc clothesProvider;//服装商
extern FriendNpc weaponProvider;//武器商
extern FriendNpc foodProvider;//食品商
extern FriendNpc skillProvider;//技能商


//怪物数量后期看看怎么处理
extern EnemyNpc highLevelFireMonster;//高级火怪物
extern EnemyNpc lowLevelFireMonster;//低级火怪物

extern EnemyNpc highLevelWaterMonster;//高级水怪物
extern EnemyNpc lowLevelWaterMonster;//低级水怪物

extern EnemyNpc highLevelWoodMonster;//高级木怪物
extern EnemyNpc lowLevelWoodMonster;//低级木怪物

extern EnemyNpc highLevelGoldMonster;//高级金怪物
extern EnemyNpc lowLevelGoldMonster;//低级金怪物

extern EnemyNpc highLevelEarthMonster;//高级土怪物
extern EnemyNpc lowLevelEarthMonster;//低级土怪物

extern EnemyNpc BOSS;//高级怪物
//物品

//武器 变量
extern Weapon  magicRing;
extern Weapon  magicCrystal;
extern Weapon  magicScroll;

//护具 变量
extern Armor helmet;
extern Armor armor;
extern Armor shoes;

//食品 变量
extern Food fish;
extern Food fruit;
extern Food vegetable;
extern Food herb;
extern Food meat;
extern Food mushroom;
//材料 变量
extern GameMaterial tree;
extern GameMaterial stone;

//特殊物品 变量
extern TaskItem key;
extern TaskItem letter;


#endif // !SET_VARIABLES_H
