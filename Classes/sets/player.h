// Creator : 冯俊财 2353924
// Description: 玩家类的声明

#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <string.h>
#include "elements.h" 
#include "items.h"
#include "tasks.h"
#include "npc.h"
#include "cocos2d.h" 

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

*******************************************************************************************/

constexpr int PLAYRT_BASE_HP = 100;														//玩家初始血量
constexpr int PLAYER_UPGRADE_HP = 25;													//升级增加的血量
constexpr int PLAYRR_BASE_ATTACK = 10;													//玩家初始攻击力
constexpr int PLAYER_UPGRADE_ATTACK = 5;												//升级增加的攻击力
constexpr int SPEED = 1000;																//移动速度

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
class Player : public cocos2d::Sprite {
    CREATE_FUNC(Player); 
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
    friend class Elements;
    friend class BattleSence;


public:
    Player();                                                                            //构造函数
    void Player::clone(Player& hero); 										            //克隆函数
    bool initWithFile(const std::string& filename);									     //初始化图像文件
    void setPlayerElement(ElementType element) { player_element = element; }			 //设置玩家的元素属性
    std::string getFileName() { return filename; }                                       //获取初始化图像文件名
    void setCharacterImage(const std::string& imageName) { filename = imageName; }	     //设置人物形象
    
    void setHp(int hp) { this->hp = hp; }												 //设置血量
    void setMaxHp(int maxHp) {this->max_hp = maxHp;};			    					 //设置最大血量               
    void setAttack(int attack) { this->attack = attack; }								 //设置攻击力
    void setLevel(int level) { this->level = level; }									 //设置等级
    void setName(const std::string& name) { this->name = name; }						 //设置名字
    void setElement(ElementType element) { player_element = element; }					 //设置元素属性
    void setMoney(int money) { this->money = money; }									 //设置金钱
    void setArmor(Armor* armor) { my_armor = armor; }									 //设置护甲
    void setHelmet(Armor* helmet) { my_helmet = helmet; }								 //设置头盔
    void setShoes(Armor* shoes) { my_shoes = shoes; }									 //设置鞋子
    void setWeapon(Weapon* weapon) { this->weapon = weapon; }							 //设置武器
    void setAlive(bool isAlive) { this->isAlive = isAlive; }							 //设置是否存活
    void setState(PlayerState state) { this->state = state; }							 //设置状态
    void setMoving(bool isMoving) { this->isMoving = isMoving; }						 //设置是否移动
    void setMovingUp(bool isMovingUp) { this->isMovingUp = isMovingUp; }				 //设置是否向上移动
    void setMovingDown(bool isMovingDown) { this->isMovingDown = isMovingDown; }		 //设置是否向下移动
    void setMovingLeft(bool isMovingLeft) { this->isMovingLeft = isMovingLeft; }		 //设置是否向左移动
    void setMovingRight(bool isMovingRight) { this->isMovingRight = isMovingRight; }	 //设置是否向右移动
    void setSpeed(int speed) { this->speed = speed; }									 //设置速度

    void Upgrade(); 																     // 玩家升级                               
    void TakeDamage(int damage);                                                         // 玩家受到伤害
    void Heal(int heal_hp);															     // 玩家治疗                               
    Vec2 Move(EventKeyboard::KeyCode keyCode);  								         // 玩家移动                        
    void setPosition(const Vec2& newPosition) override;								     //设置坐标
    const cocos2d::Vec2& getPosition() const override { return position; }  	         //获取坐标
    void AddMoney(int getmoney) { money += getmoney; }; 							     //玩家货币增加

    int getHp() const;																     // 获取玩家的当前血量
    int getMaxHp() const;               											     // 获取玩家的最大血量
    int getAttack() const;	                                                             // 获取玩家的攻击力
    int GetLevel() const;                                                                // 获取玩家的等级
    int getSpeed() const;


    std::string GetName() const;                                                         // 获取玩家的名字

    constexpr ElementType getElement() { return player_element; }                       //获取玩家元素属性

    bool isMoving = false;                                  //是否 移动 bool
    bool isMovingUp = false;
    bool isMovingDown = false;
    bool isMovingLeft = false;
    bool isMovingRight = false;
    
private:

    //设定面板
    std::string filename;                                   //玩家图像名
    std::string name;                                       //名字
    int level;                                              //等级
    int max_hp=100;                                         //最大血量
    int hp;                                                 //当前血量
    int basic_attack;                                       //攻击力(根据等级)
    int attack;                                             //最终攻击力
    int money = 0;                                          //金钱
    int speed = SPEED;									    //速度
    ElementType player_element;							    //元素属性
    Vec2 position;                                          //位置

    //状态
    bool isAlive;                                           //是否存活   
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