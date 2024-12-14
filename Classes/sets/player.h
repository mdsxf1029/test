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
#include "npc.h"
<<<<<<< HEAD
#include "cocos2d.h"
#include <Classes/battle/BattleSence.h>
=======
#include "cocos2d.h" 
>>>>>>> b63e711c7b7e90fb33041d65212f90826e208538

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
//图片名字
const std::string hero1 = "try1.png";
const std::string hero2 = "try1.png";
const std::string hero3 = "try1.png";

//hero
enum SkillState
{
    NONE,   // 没有技能激活
    SKILL_1,  // 一技能
    SKILL_2   // 二技能
};
// 玩家角色的状态，可能用于角色属性管理
enum PlayerState {
    NORMAL,
    STUNNED,
    DEAD
};
class Player : public Sprite {

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
    friend class BattleSence;


public:

    Player();//含参

    //升级
    void Upgrade();

    //互动  -交给其他组员。
    void Interact(FriendNpc& fnpc)
    {
    };

    // 玩家攻击敌人
    void AttackEnemy(EnemyNpc& enemy, EventKeyboard::KeyCode KEY);

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
    Vec2 Move(EventKeyboard::KeyCode keyCode);

    //创建文件
    bool initWithFile(const std::string& filename);

    //获取玩家元素属性
    constexpr ElementType getPlayerElement() { return player_element; }

    //设定坐标
    void setPosition(const Vec2& newPosition) override;

    //获取坐标
    const cocos2d::Vec2& getPosition() const override { return position; }

    //玩家货币增加
    void AddMoney(int getmoney) { money += getmoney; };

private:

    //设定面板
    std::string name;                                       //名字
    int level;                                              //等级
    int max_hp;                                             //最大血量
    int hp;                                                 //当前血量
    int basic_attack;                                       //攻击力(根据等级)
    int attack;                                             //最终攻击力
    int money = 0;                                            //金钱

    std::string file;									    //文件名
    ElementType player_element;							    //元素属性
    Inventory bag;                                          //背包
    Vec2 position;                                          //位置

    //状态
    bool isAlive;                                           //是否存活   
    bool isMoving = false;                                  //是否 移动
    bool isAttacking = false;                               //是否攻击 普通攻击
    PlayerState state;                                      //状态
    //装备
    Armor* my_armor;                                        //护甲
    Armor* my_helmet;                                       //头盔
    Armor* my_shoes;                                        //鞋子
    //武器
    Weapon* weapon;                                         //武器为空  
};

#endif