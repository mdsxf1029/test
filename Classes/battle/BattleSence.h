#pragma once

#ifndef BATTELSENCE_H
#define BATTLESENCE_H

#include "cocos2d.h"
#include "Player.h"
#include "npc.h"
class BattleSence {
public:
    static cocos2d::Scene* createScene();//创建场景  地图 
    virtual bool init(); 
    void update(float delta);
    void handleInput(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

protected:

private:
	Player* player;//玩家
	EnemyNpc* enemy;//敌人

};




#endif 
