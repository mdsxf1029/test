#include "BattleSence.h"
#include "cocos2d.h"

#include <sets/inventory.h>
#include <sets/npc.h>
#include <sets/player.h>
#include <sets/items.h>
#include <sets/elements.h>

USING_NS_CC;//cococs2d 命名空间 可以直接调用cocos2d-x的函数

//玩家初始位置
const int PLAYER_BEGIN_X = 200;
const int PLAYER_BEGIN_Y = 300;
//敌人初始位置
const int ENEMY_BEGIN_X = 400;
const int ENEMY_BEGIN_Y = 300;

//Sence 场景   创建场景
Scene* BattleSence::createScene() {
    return BattleSence::create();
    //是通过继承自 Node 类间接获得的功能。
}

bool BattleSence::init(EnemyNpc& enemy_now) {
    if (!Scene::init()) {//初始化 场景
        return false;
    }

    // 设置背景
    auto background = Sprite::create("battle_background.png");//创建背景精灵
    background->setPosition(Director::getInstance()->getVisibleSize() / 2);//设置位置为中心
    this->addChild(background);//添加到场景中
    /*这段代码的目的是为场景设置视觉背景，
    使玩家在游戏中看到一个具体的图像，而不是空白的场景。*/

    // 设置玩家和敌人 
    //玩家
    player = &hero;
    player->setPosition(Vec2(PLAYER_BEGIN_X, PLAYER_BEGIN_Y));//设置位置
    this->addChild(player);//添加到场景中
    //敌人
    enemy = &enemy_now;
    enemy->setPosition(Vec2(ENEMY_BEGIN_X, ENEMY_BEGIN_X));//设置位置
    this->addChild(player);//添加到场景中

    // 初始化攻击状态
    isAttacking = false;

    // 设置键盘事件监听器
    auto listener = EventListenerKeyboard::create();//创建键盘事件监听器
    listener->onKeyPressed = CC_CALLBACK_2(BattleSence::keyPressed, this);//按键按下时调用handleInput函数
    listener->onKeyReleased = CC_CALLBACK_2(BattleSence::keyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//添加到事件分发器中

    this->scheduleUpdate(); // 每帧更新
    return true;
}
//每帧更新
void BattleSence::update(float delta)
{
    player->update(delta);
    enemy->update(delta);
    // 检查生命值
    if (!player->isAlive) {
        CCLOG("Player defeated!");
        // 处理玩家失败的逻辑


    }
    if (!enemy->isAlive) {
        if (enemy->level == 2)
			(player->level)++;//敌人等级为2时，玩家升级
        CCLOG("Enemy defeated!");
        // 处理enemy失败的逻辑
    }
    //移动  
}
//处理键盘输入--按下
void BattleSence::keyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            player->isMoving = true;
            player->Move(EventKeyboard::KeyCode::KEY_UP_ARROW);
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            player->isMoving = true;
            player->Move(EventKeyboard::KeyCode::KEY_DOWN_ARROW);
            break;
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            player->isMoving = true;
            player->Move(EventKeyboard::KeyCode::KEY_LEFT_ARROW);
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            player->isMoving = true;
            player->Move(EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
            break;
        case EventKeyboard::KeyCode::KEY_0:
			player->AttackEnemy(*enemy, EventKeyboard::KeyCode::KEY_0);
			break;
    } 
}

//处理键盘输入--释放
void BattleSence::keyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_UP_ARROW://如果是上键
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW://如果是下键
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW://如果是左键
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW://如果是右键
            player->isMoving = false; // 停止移动
            break;
        case EventKeyboard::KeyCode::KEY_A:
            CCLOG("Player stops attacking!");
            break;
        case EventKeyboard::KeyCode::KEY_L:
            CCLOG("Enemy stops attacking!");
            break;
    }
}


// 战斗
void BattleSence::battle()
{

   
}