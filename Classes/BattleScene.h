#pragma once

#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <functional>
#include "sets/manager.h"
#include "Map/MiniMap.h"

// 战斗状态枚举，可能用于管理战斗流程
enum class BattleState {
    IDLE,           // 待机状态
    ATTACKING,      // 攻击状态
    GAME_OVER       // 游戏结束
};


class BattleScene : public cocos2d::Scene
{
public:
    BattleScene();
    virtual ~BattleScene();
     
    virtual bool init();                                                                                // 初始化场景
    void update(float delta) override;                                                                  // 更新逻辑
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);                  // 键盘按下事件  
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);                 // 键盘释放事件   
    void onMouseDown(cocos2d::Event* event);                                                            // 鼠标点击事件
	void enemyMove();                                                                                   // 敌人移动
    void endBattle();                                                                                   // 结束战斗
    void checkBattleOver();                                                                             // 用于检测战斗结束条件
    void BattleScene::EnemyAttack();
    CREATE_FUNC(BattleScene);

private:
	cocos2d::TMXTiledMap* _tileMap;		                                                                // 地图
    BattleState _battleState;                                                                           // 当前战斗状态
    std::shared_ptr<EnemyNpc> rawEnemy ;                                                                //敌人
	std::vector<std::shared_ptr<Skill>>askillList = GlobalManager::getInstance().getSkills();			//技能
	std::shared_ptr<Skill>enemyskill;                       											//敌人技能

    // 战斗数据
    bool _isPlayerTurn;                                                                                 // 判断是否轮到玩家行动
    cocos2d::Vec2 _skillDirection;                                                                      // 技能方向
    cocos2d::Label* _enemyHealthLabel;		                                                            // 敌人生命值显示
    cocos2d::Label* _playerHealthLabel;		                                                            // 玩家生命值显示
	SkillState _currentSkillState;			                                                            // 当前技能状态
	float _coolDownTime = 3.0f;			                                                                // 技能冷却时间
	bool _ableToAttack = true;                                                                          //能够攻击  
    bool gameOver = false;                                                                              //战斗结束初始化为false
	float cooldownTime = 2.0f;                                                                          //冷却时间
    

};

#endif // __BATTLE_SCENE_H__

