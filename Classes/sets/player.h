// Creator : 冯俊财 2353924
// Description: 玩家类的声明

#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <string.h>
#include "elements.h"
#include "inventory.h"
#include "items.h"
#include "tasks.h"
const int PLAYER_UPGRADE_HP = 25;//升级增加的血量
const int PLAYER_UPGRADE_ATTACK = 5;//升级增加的攻击力 
/******************************************************************************************
 class Player
 代表游戏中的玩家角色。

 class Player包含角色的基本属性，如名字、等级、血量、元素属性以及攻击力。
 此处的 初始化的 攻击力是不包含武器技能等的攻击力，只是基础攻击力。
 该类提供了构造函数以初始化玩家的名字，并默认初始化其他属性。

属性：
 - name: 玩家名字
 - level: 玩家等级
 - hp: 玩家当前血量
 - player_element: 玩家元素属性
 - attack: 玩家攻击力
 - inventory: 玩家背包

*******************************************************************************************/
//hero
class Player {

    friend class Inventory;
    friend class Item;
    friend class Weapon;
    friend class Armor;
    friend class BackgroundManager;
    friend class Food;
    friend class Task;
    friend class NPC;
    friend class FriendNpc;
    friend class EnemyNpc;
    friend class Skill;
    friend class LowLevelSkill;
    friend class MidLevelSkill;
    friend class HighLevelSkill;
    friend class Elements;


public:
    
    Player(const std::string& filename);//含参

    //升级
    void Upgrade();
    //互动
    void Interact(FriendNpc& fnpc) 
    { };//还没有具体写

    // 玩家攻击敌人
    void AttackEnemy(EnemyNpc& enemy);

    // 玩家受到伤害
    void TakeDamage(int damage);

    // 玩家治疗
    void Heal(int heal_hp);

    // 获取玩家的当前血量
    int GetHp() const;

    // 获取玩家的名字
    std::string GetName() const;

    // 获取玩家的等级
    int GetLevel() const;

    //移动 需要坐标
    void Move();
    //创建文件
    Player* initWithFile(const std::string& filename);

	//获取玩家元素属性
    ElementType getPlayerElement() const { return player_element; }


protected:


private:
    std::string name; //名字
    int level;  //等级
    bool isAlive; //是否存活
    int max_hp;  //最大血量
    int hp;      //血量
    ElementType player_element;//元素属性
    int basic_attack;  //攻击力(根据等级)
    int attack;//最终攻击力
    Inventory bag;//背包

    //装备
    Armor* my_armor;//护甲
    Armor* my_helmet;//头盔
    Armor* my_shoes;//鞋子
    //武器
    Weapon* weapon;//武器为空

};

#endif