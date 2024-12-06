#pragma once
#ifndef SET_VARIABLES_H
#define SET_VARIABLES_H

#include<string>
#include<string.h>

#include"items.h"
#include"player.h"
#include"tasks.h"
#include"skills.h"
#include"npc.h"
#include"elements.h"
#include"inventory.h"


//玩家类
std::string spritetry="try.png";
Player hero(spritetry);//玩家

//任务

Task mainTask(MAIN_TASK, MAIN_TASK_DESCRIPTION);//主线任务
Task sideTaskOne(SIDE_TASK_ONE, SIDE_TASK_ONE_DESCRIPTION);//副任务1
Task sideTaskTwo(SIDE_TASK_TWO, SIDE_TASK_TWO_DESCRIPTION);//副任务2	
Task sideTaskThree(SIDE_TASK_THREE, SIDE_TASK_THREE_DESCRIPTION);//副任务3
Task sideTaskFour(SIDE_TASK_FOUR, SIDE_TASK_FOUR_DESCRIPTION);//副任务4
Task sideTaskFive(SIDE_TASK_FIVE, SIDE_TASK_FIVE_DESCRIPTION);//副任务5
Task sideTaskSix(SIDE_TASK_SIX, SIDE_TASK_SIX_DESCRIPTION);//副任务6
Task sideTaskSeven(SIDE_TASK_SEVEN, SIDE_TASK_SEVEN_DESCRIPTION);//副任务7
Task nonTask(NON_TASK, NON_TASK_DESCRIPTION);//无任务

//技能

LowLevelSkill elementSurge(ELEMENT_SURGE);//元素冲击
MidLevelSkill elementalTorrent(Elemental_Torrent);//元素洪流
HighLevelSkill energyVortex(Energy_Vortex);//能量漩涡
//组合技能
HighLevelSkill arcaneBlast(Arcane_Blast);//奥术爆发


//NPC

//友方NPC
FriendNpc princess(PRINCESS);//公主
FriendNpc king(KING);//国王
FriendNpc minister(MINISTER);//大臣

FriendNpc clothesProvider(ClothesProvider);//服装商
FriendNpc weaponProvider(WeaponProvider);//武器商
FriendNpc foodProvider(FoodProvider);//食品商
FriendNpc skillProvider(SkillProvider);//技能商


 
//怪物数量后期看看怎么处理
EnemyNpc highLevelFireMonster(ElementType::Fire, 2, elementalTorrent);//高级火怪物
EnemyNpc lowLevelFireMonster(ElementType::Fire, 1, elementSurge);//低级火怪物

EnemyNpc highLevelWaterMonster(ElementType::Water, 2,elementalTorrent);//高级水怪物
EnemyNpc lowLevelWaterMonster(ElementType::Water, 1, elementSurge);//低级水怪物

EnemyNpc highLevelWoodMonster(ElementType::Wood, 2, elementalTorrent);//高级木怪物
EnemyNpc lowLevelWoodMonster(ElementType::Wood, 1, elementSurge);//低级木怪物

EnemyNpc highLevelGoldMonster(ElementType::Gold, 2, elementalTorrent);//高级金怪物
EnemyNpc lowLevelGoldMonster(ElementType::Gold, 1, elementSurge);//低级金怪物

EnemyNpc highLevelEarthMonster(ElementType::Earth, 2, elementalTorrent);//高级土怪物
EnemyNpc lowLevelEarthMonster(ElementType::Earth, 1, elementSurge);//低级土怪物

ElementType playerElement = hero.getPlayerElement();
EnemyNpc BOSS(playerElement, 3, energyVortex);//boss 与玩家元素相同 等级为3  //或者相克更好 暂且这样
//物品

//武器 变量
Weapon  magicRing(MAGIC_RING);
Weapon  magicCrystal(MAGIC_CRYSTAL);
Weapon  magicScroll(MAGIC_SCROLL);

//护具 变量
Armor helmet(HELMET);
Armor armor(ARMOR);
Armor shoes(SHOES);

//食品 变量
Food fish(FISH);
Food fruit(FRUIT);
Food vegetable(VEGETABLE);
Food herb(HERB);
Food meat(MEAT);

//材料 变量
Material tree(TREE);
Material stone(STONE);

//特殊物品 变量
TaskItem key(KEY);
TaskItem letter(LETTER);

//元素 变量
Element gold(ElementType::Gold);
Element wood(ElementType::Wood);
Element water(ElementType::Water);
Element fire(ElementType::Fire);
Element earth(ElementType::Earth);

//背包
Inventory bag;//背包

#endif // !SET_VARIABLES_H
