#pragma once

#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <functional>

// 战斗状态枚举，可能用于管理战斗流程
enum class BattleState {
    IDLE,           // 待机状态
    ATTACKING,      // 攻击状态
    GAME_OVER       // 游戏结束
};
enum class SkillState
{
    NONE,   // 没有技能激活
    SKILL_1,  // 一技能
    SKILL_2   // 二技能
};
// 玩家角色的状态，可能用于角色属性管理
enum class PlayerState {
    NORMAL,
    STUNNED,
    DEAD
};

struct BattleCharacter {
    cocos2d::Sprite* sprite;        // 角色精灵
    std::string name;               // 角色名称
    int health;                     // 角色生命值
    int attack;                     // 角色攻击力
    PlayerState state;              // 当前状态

    BattleCharacter(cocos2d::Sprite* sprite, const std::string& name, int health, int attack, PlayerState state)
        : sprite(sprite), name(name), health(health), attack(attack), state(state) {
    }
};

class BattleScene : public cocos2d::Scene
{
public:
    BattleScene();
    virtual ~BattleScene();

    static cocos2d::Scene* createScene();
    virtual bool init();                      // 初始化场景
    void update(float delta) override;        // 更新逻辑
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onMouseDown(cocos2d::Event* event);  // 鼠标点击事件

    CREATE_FUNC(BattleScene);

private:
    cocos2d::TMXTiledMap* _tileMap;
    BattleState _battleState;                 // 当前战斗状态
    BattleCharacter* _player;                 // 玩家角色
    BattleCharacter* _enemy;                  // 敌人角色

    // 战斗回合数据
    int _turnCounter;                         // 回合计数器
    bool _isPlayerTurn;                       // 判断是否轮到玩家行动
    cocos2d::Vec2 _skillDirection;            // 技能方向
    cocos2d::Label* _enemyHealthLabel;
    // 粒子系统，用于显示技能效果
    // 当前技能状态
    SkillState _currentSkillState;

    cocos2d::ParticleSystemQuad* _skillEffect;
    // 技能效果
    cocos2d::ParticleSystemQuad* _skill1Effect;
    cocos2d::ParticleSystemQuad* _skill2Effect;

    void startBattle();                       // 开始战斗
    void endBattle();                         // 结束战斗
    void playerAttack();                      // 玩家攻击
    void enemyAttack();                       // 敌人攻击

    void castSkill1();
    void castSkill2();

    void displayBattleInfo();                 // 显示战斗信息（血量、状态等）
    void displayAttackAnimation();            // 播放攻击动画

    // 处理战斗状态的变化
    void handleBattleState();

    // 显示对话框、状态等界面
    void displayDialogue(const std::string& text);

    // 用于检测战斗结束条件
    void checkBattleOver();

    // 玩家移动控制
    void movePlayer(cocos2d::Vec2 direction); // 控制玩家移动
};

#endif // __BATTLE_SCENE_H__

