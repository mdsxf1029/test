#include "BattleSence.h"
#include "Player.h"
#include "npc.h"
#include "cocos2d.h"
#include"sets_variables.h"
#include"skills.h"
USING_NS_CC;//cococs2d 命名空间 可以直接调用cocos2d-x的函数

//Sence 场景   创建场景
Scene* BattleScene::createScene() {
    return BattleScene::create();
}

bool BattleScene::init(Enemy & enemy_now) {
    if (!Scene::init()) {
        return false;
    }

    player = hero;
    player ->setPosition(Vec2(200, 300));
    this->addChild(player1);

	enemy = enemy_now;                      
    player2->setPosition(Vec2(400, 300));
    this->addChild(player2);

    // 设置键盘事件监听器
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(BattleScene::handleInput, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->scheduleUpdate(); // 每帧更新
    return true;
}


/*#include "BattleScene.h"

USING_NS_CC;

Scene* BattleScene::createScene() {
    return BattleScene::create();
}

bool BattleScene::init() {
    if (!Scene::init()) {
        return false;
    }

    player1 = Player::create("player1.png");
    player1->setPosition(Vec2(200, 300));
    this->addChild(player1);

    player2 = Player::create("player2.png");
    player2->setPosition(Vec2(400, 300));
    this->addChild(player2);

    // 设置键盘事件监听器
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(BattleScene::handleInput, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->scheduleUpdate(); // 每帧更新
    return true;
}

void BattleScene::update(float delta) {
    player1->update(delta);
    player2->update(delta);

    // 检查生命值
    if (!player1->isAlive()) {
        CCLOG("Player 1 defeated!");
        // 处理玩家1失败的逻辑
    }
    if (!player2->isAlive()) {
        CCLOG("Player 2 defeated!");
        // 处理玩家2失败的逻辑
    }
}

void BattleScene::handleInput(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        player1->attack(player2);
        CCLOG("Player 1 attacks Player 2!");
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_L) {
        player2->attack(player1);
        CCLOG("Player 2 attacks Player 1!");
    }
}
*/