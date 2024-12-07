#pragma once

#ifndef BATTELSENCE_H
#define BATTLESENCE_H

#include "cocos2d.h"
#include <sets/inventory.h>
#include <sets/npc.h>
#include <sets/player.h>
#include <sets/items.h>
#include <sets/elements.h>
class BattleSence :public cocos2d::Scene {
public:
    friend class Player;
    friend class EnemyNpc;
    static cocos2d::Scene* createScene();//创建场景  地图 

    virtual bool init(EnemyNpc& enemy_now);//初始化
    void update(float delta);//每帧更新
    void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void battle();//战斗
protected:

private:
    Player* player;//玩家
    EnemyNpc* enemy;//敌人
    bool isAttacking; // 攻击状态标志
};




#endif 
