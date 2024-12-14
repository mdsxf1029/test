#include "BattleScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"

// 构造函数和析构函数
BattleScene::BattleScene()
    : _battleState(BattleState::IDLE),
    _player(nullptr),
    _enemy(nullptr),
    _skillEffect(nullptr),
    _tileMap(nullptr),
    _skillDirection(cocos2d::Vec2::ZERO),
    _currentSkillState(SkillState::NONE), // 初始技能状态为NONE
    _skill1Effect(nullptr),
    _skill2Effect(nullptr),
    _enemyHealthLabel(nullptr)
{
}

BattleScene::~BattleScene() {}

cocos2d::Scene* BattleScene::createScene()
{
    return BattleScene::create();
}

bool BattleScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // 加载 TMX 地图
    _tileMap = cocos2d::TMXTiledMap::create("whole3.tmx");
    if (_tileMap == nullptr)
    {
        cocos2d::log("Failed to load map.");
        return false;
    }
    this->addChild(_tileMap);  // 将地图添加到场景

    // 从地图的 objects 层中获取玩家和敌人的信息
    cocos2d::TMXObjectGroup* objectGroup = _tileMap->getObjectGroup("Objects");
    if (objectGroup != nullptr)
    {
        // 获取玩家的信息（假设玩家的对象名为 "player"）
        cocos2d::ValueMap playerData = objectGroup->getObject("Player");
        if (!playerData.empty())
        {
            float playerX = playerData["x"].asFloat();
            float playerY = playerData["y"].asFloat();
            _player = new BattleCharacter(cocos2d::Sprite::create("NPC1.png"), "Player", 100, 20, PlayerState::NORMAL);
            _player->sprite->setPosition(playerX, playerY);
            this->addChild(_player->sprite);  // 将玩家添加到场景中
        }

        // 获取敌人的信息（假设敌人的对象名为 "enemy"）
        cocos2d::ValueMap enemyData = objectGroup->getObject("NPC");
        if (!enemyData.empty())
        {
            float enemyX = enemyData["x"].asFloat();
            float enemyY = enemyData["y"].asFloat();
            _enemy = new BattleCharacter(cocos2d::Sprite::create("NPCc.png"), "Enemy", 100, 15, PlayerState::NORMAL);
            _enemy->sprite->setPosition(enemyX, enemyY);
            this->addChild(_enemy->sprite);  // 将敌人添加到场景中
        }
    }

    // 创建技能粒子效果
    _skillEffect = cocos2d::ParticleSystemQuad::create("fire.plist");  // 二技能粒子效果
    _skillEffect->setVisible(false);  // 初始时隐藏
    this->addChild(_skillEffect, 10);

    _skill1Effect = cocos2d::ParticleSystemQuad::create("fire1.plist");  // 一技能粒子效果
    _skill1Effect->setVisible(false);  // 初始时隐藏
    this->addChild(_skill1Effect, 10);

    _skill2Effect = cocos2d::ParticleSystemQuad::create("fireball2.plist");  // 二技能粒子效果
    _skill2Effect->setVisible(false);  // 初始时隐藏
    this->addChild(_skill2Effect, 10);

    // 创建一个 Label 来显示敌人当前的生命值
    _enemyHealthLabel = cocos2d::Label::createWithTTF("Health: 100", "fonts/Marker Felt.ttf", 48);
    if (_enemyHealthLabel != nullptr)
    {
        _enemyHealthLabel->setPosition(cocos2d::Vec2(_enemy->sprite->getPosition().x, _enemy->sprite->getPosition().y + 50));
        this->addChild(_enemyHealthLabel, 1);  // 将 Label 添加到场景中
    }

    // 设置场景更新
    schedule([=](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    // 设置键盘和鼠标监听事件
    auto listenerKeyboard = cocos2d::EventListenerKeyboard::create();
    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(BattleScene::onKeyPressed, this);
    listenerKeyboard->onKeyReleased = CC_CALLBACK_2(BattleScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

    auto listenerMouse = cocos2d::EventListenerMouse::create();
    listenerMouse->onMouseDown = CC_CALLBACK_1(BattleScene::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);

    return true;
}

void BattleScene::update(float delta)
{
    if (_skillEffect->isVisible()) {

    }
    // 更新技能效果（如果有需要的话）
    if (_skill1Effect->isVisible()) {

    }

    if (_skill2Effect->isVisible()) {

    }

    // 更新敌人生命值的显示
    if (_enemy != nullptr && _enemyHealthLabel != nullptr)
    {
        // 更新显示的敌人生命值
        _enemyHealthLabel->setString("Health: " + std::to_string(_enemy->health));
        // 更新 Label 位置，使其始终跟随敌人
        _enemyHealthLabel->setPosition(cocos2d::Vec2(_enemy->sprite->getPosition().x, _enemy->sprite->getPosition().y + 50));
    }

    // 检查战斗是否结束
    checkBattleOver();
}

void BattleScene::onMouseDown(cocos2d::Event* event)
{
    // 将通用事件转换为鼠标事件
    cocos2d::EventMouse* mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
    if (mouseEvent)
    {
        // 获取鼠标点击的世界坐标
        cocos2d::Vec2 clickPosition = mouseEvent->getLocation();  // 使用 getLocation() 获取鼠标位置

        if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
        {
            _battleState = BattleState::ATTACKING;
            // 判断右键点击时，激活相应的技能
            if (_currentSkillState == SkillState::SKILL_1) {
                castSkill1();  // 执行一技能
            }
            else if (_currentSkillState == SkillState::SKILL_2) {
                castSkill2();  // 执行二技能
            }
        }
        else if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
        {
            // 普通攻击

            // 获取鼠标点击的世界坐标
            cocos2d::Vec2 clickPosition = mouseEvent->getLocation();  // 使用 getLocation() 获取鼠标位置

            // 计算从玩家到鼠标点击位置的方向向量
            _skillDirection = clickPosition - _player->sprite->getPosition();
            _skillDirection.normalize();  // 将方向向量归一化

            // 计算从玩家到鼠标点击位置的角度（弧度）
            float angle = std::atan2(_skillDirection.y, _skillDirection.x);  // atan2返回的是弧度

            // 将弧度转换为角度
            float angleInDegrees = CC_RADIANS_TO_DEGREES(angle);  // 转换为角度

            // 确保角度在 [0, 360) 范围内
            if (angleInDegrees < 0) {
                angleInDegrees += 360;  // 将负角度转换为正角度
            }

            // 更新粒子效果的发射角度
            _skillEffect->setAngle(angleInDegrees);  // 设置粒子的发射角度

            // 设置粒子系统的位置
            _skillEffect->setPosition(_player->sprite->getPosition());

            // 启用粒子效果并播放
            _skillEffect->setVisible(true);
            _skillEffect->resetSystem();  // 启动粒子系统

            // 设置技能持续时间（2秒）
            scheduleOnce([this](float dt) {
                // 2秒后停止粒子效果
                _skillEffect->stopSystem();  // 停止粒子系统
                _skillEffect->setVisible(false);  // 隐藏粒子系统
                }, 1.0f, "stop_skill_effect");  // 2秒后调用
            _battleState = BattleState::ATTACKING;
            playerAttack();
        }
    }
}

void BattleScene::playerAttack()
{
    // 普通攻击逻辑
    // 你可以在这里添加攻击逻辑，可能会涉及到伤害、范围等
    if (_battleState != BattleState::ATTACKING) return;

    // 设置粒子效果的位置
    _skillEffect->setPosition(_player->sprite->getPosition());
    _skillEffect->setVisible(true);

    // 播放技能粒子效果
    _skillEffect->resetSystem();

    // 获取敌人当前位置
    cocos2d::Vec2 enemyPosition = _enemy->sprite->getPosition();
    cocos2d::Vec2 playerPosition = _player->sprite->getPosition();

    // 计算敌人和玩家之间的距离
    float distance = playerPosition.distance(enemyPosition);

    // 攻击的最大范围半径
    float attackRadius = 1000.0f;  // 你可以设置为你想要的攻击半径
    if (distance > attackRadius) {
        return;  // 如果敌人超出攻击范围，直接返回
    }


    // 计算从玩家到敌人之间的角度（弧度）
    cocos2d::Vec2 direction = enemyPosition - playerPosition;
    float enemyAngle = std::atan2(direction.y, direction.x);  // atan2返回的是弧度

    // 将弧度转换为角度
    float enemyAngleInDegrees = CC_RADIANS_TO_DEGREES(enemyAngle);
    if (enemyAngleInDegrees < 0) {
        enemyAngleInDegrees += 360;  // 将负角度转换为正角度
    }

    // 攻击扇形的角度范围
    float attackAngle = 360.0f;  // 例如 45 度扇形
    float attackRange = attackAngle / 2;  // 扇形角度的半径

    // 计算玩家的攻击角度
    float playerAngleInDegrees = std::atan2(_skillDirection.y, _skillDirection.x);  // 使用玩家的攻击方向
    if (playerAngleInDegrees < 0) {
        playerAngleInDegrees += 360;  // 将负角度转换为正角度
    }

    // 计算敌人与玩家攻击方向的角度差
    float angleDifference = std::abs(playerAngleInDegrees - enemyAngleInDegrees);
    if (angleDifference > 180) {
        angleDifference = 360 - angleDifference;  // 确保角度差不超过 180 度
    }

    // 判断敌人是否在攻击扇形范围内
    if (angleDifference <= attackRange) {
        // 如果敌人在攻击范围内
        // 你可以在这里执行攻击逻辑
        _enemy->health -= 20;  // 假设伤害计算是 20
        cocos2d::log("Enemy hit! Health: %d", _enemy->health);

        // 更新敌人生命值显示
        if (_enemyHealthLabel != nullptr)
        {
            _enemyHealthLabel->setString("Health: " + std::to_string(_enemy->health));
        }

        // 如果敌人死亡
        if (_enemy->health <= 0)
        {
            _battleState = BattleState::GAME_OVER;
            cocos2d::log("You win!");

            // 弹出对话框显示战斗结束
            ::MessageBoxA(NULL, "Game Over! You win!", "Battle Ended", MB_OK);  // 使用 Windows API

        }
    }

    // 改变战斗状态回到待机
    _battleState = BattleState::IDLE;
    cocos2d::log("Player is attacking!");
}

void BattleScene::castSkill1()
{
    // 一技能的效果
    if (_battleState != BattleState::ATTACKING) return;

    _skill1Effect->setPosition(_player->sprite->getPosition());
    _skill1Effect->setVisible(true);
    _skill1Effect->resetSystem();  // 播放粒子效果

    // 设置技能持续时间（2秒）
    scheduleOnce([this](float dt) {
        // 2秒后停止粒子效果
        _skill1Effect->stopSystem();  // 停止粒子系统
        _skill1Effect->setVisible(false);  // 隐藏粒子系统
        }, 1.0f, "stop_skill1_effect");  // 2秒后调用

    // 获取敌人当前位置
    cocos2d::Vec2 enemyPosition = _enemy->sprite->getPosition();
    cocos2d::Vec2 playerPosition = _player->sprite->getPosition();

    // 计算敌人和玩家之间的距离
    float distance = playerPosition.distance(enemyPosition);

    // 攻击的最大范围半径
    float attackRadius = 1000.0f;  // 你可以设置为你想要的攻击半径
    if (distance > attackRadius) {
        return;  // 如果敌人超出攻击范围，直接返回
    }


    // 计算从玩家到敌人之间的角度（弧度）
    cocos2d::Vec2 direction = enemyPosition - playerPosition;
    float enemyAngle = std::atan2(direction.y, direction.x);  // atan2返回的是弧度

    // 将弧度转换为角度
    float enemyAngleInDegrees = CC_RADIANS_TO_DEGREES(enemyAngle);
    if (enemyAngleInDegrees < 0) {
        enemyAngleInDegrees += 360;  // 将负角度转换为正角度
    }

    // 攻击扇形的角度范围
    float attackAngle = 90.0f;  // 例如 45 度扇形
    float attackRange = attackAngle / 2;  // 扇形角度的半径

    // 计算玩家的攻击角度
    float playerAngleInDegrees = std::atan2(_skillDirection.y, _skillDirection.x);  // 使用玩家的攻击方向
    if (playerAngleInDegrees < 0) {
        playerAngleInDegrees += 360;  // 将负角度转换为正角度
    }

    // 计算敌人与玩家攻击方向的角度差
    float angleDifference = std::abs(playerAngleInDegrees - enemyAngleInDegrees);
    if (angleDifference > 180) {
        angleDifference = 360 - angleDifference;  // 确保角度差不超过 180 度
    }

    // 判断敌人是否在攻击扇形范围内
    if (angleDifference <= attackRange) {
        // 如果敌人在攻击范围内
        // 你可以在这里执行攻击逻辑
        _enemy->health -= 20;  // 假设伤害计算是 20
        cocos2d::log("Enemy hit! Health: %d", _enemy->health);

        // 更新敌人生命值显示
        if (_enemyHealthLabel != nullptr)
        {
            _enemyHealthLabel->setString("Health: " + std::to_string(_enemy->health));
        }

        // 如果敌人死亡
        if (_enemy->health <= 0)
        {
            _battleState = BattleState::GAME_OVER;
            cocos2d::log("You win!");

            // 弹出对话框显示战斗结束
            ::MessageBoxA(NULL, "Game Over! You win!", "Battle Ended", MB_OK);  // 使用 Windows API

        }
    }

    // 改变战斗状态回到待机
    _battleState = BattleState::IDLE;
    // 你可以在这里添加一技能的特殊攻击逻辑
    cocos2d::log("Casting Skill 1!");
}

void BattleScene::castSkill2()
{
    // 二技能的效果
    if (_battleState != BattleState::ATTACKING) return;

    _skill2Effect->setPosition(_player->sprite->getPosition());
    _skill2Effect->setVisible(true);
    _skill2Effect->resetSystem();  // 播放粒子效果
    // 设置技能持续时间（2秒）
    scheduleOnce([this](float dt) {
        // 2秒后停止粒子效果
        _skill2Effect->stopSystem();  // 停止粒子系统
        _skill2Effect->setVisible(false);  // 隐藏粒子系统
        }, 1.0f, "stop_skil2_effect");  // 2秒后调用

    // 获取敌人当前位置
    cocos2d::Vec2 enemyPosition = _enemy->sprite->getPosition();
    cocos2d::Vec2 playerPosition = _player->sprite->getPosition();

    // 计算敌人和玩家之间的距离
    float distance = playerPosition.distance(enemyPosition);

    // 攻击的最大范围半径
    float attackRadius = 1000.0f;  // 你可以设置为你想要的攻击半径
    if (distance > attackRadius) {
        return;  // 如果敌人超出攻击范围，直接返回
    }


    // 计算从玩家到敌人之间的角度（弧度）
    cocos2d::Vec2 direction = enemyPosition - playerPosition;
    float enemyAngle = std::atan2(direction.y, direction.x);  // atan2返回的是弧度

    // 将弧度转换为角度
    float enemyAngleInDegrees = CC_RADIANS_TO_DEGREES(enemyAngle);
    if (enemyAngleInDegrees < 0) {
        enemyAngleInDegrees += 360;  // 将负角度转换为正角度
    }

    // 攻击扇形的角度范围
    float attackAngle = 90.0f;  // 例如 45 度扇形
    float attackRange = attackAngle / 2;  // 扇形角度的半径

    // 计算玩家的攻击角度
    float playerAngleInDegrees = std::atan2(_skillDirection.y, _skillDirection.x);  // 使用玩家的攻击方向
    if (playerAngleInDegrees < 0) {
        playerAngleInDegrees += 360;  // 将负角度转换为正角度
    }

    // 计算敌人与玩家攻击方向的角度差
    float angleDifference = std::abs(playerAngleInDegrees - enemyAngleInDegrees);
    if (angleDifference > 180) {
        angleDifference = 360 - angleDifference;  // 确保角度差不超过 180 度
    }

    // 判断敌人是否在攻击扇形范围内
    if (angleDifference <= attackRange) {
        // 如果敌人在攻击范围内
        // 你可以在这里执行攻击逻辑
        _enemy->health -= 20;  // 假设伤害计算是 20
        cocos2d::log("Enemy hit! Health: %d", _enemy->health);

        // 更新敌人生命值显示
        if (_enemyHealthLabel != nullptr)
        {
            _enemyHealthLabel->setString("Health: " + std::to_string(_enemy->health));
        }

        // 如果敌人死亡
        if (_enemy->health <= 0)
        {
            _battleState = BattleState::GAME_OVER;
            cocos2d::log("You win!");

            // 弹出对话框显示战斗结束
            ::MessageBoxA(NULL, "Game Over! You win!", "Battle Ended", MB_OK);  // 使用 Windows API

        }
    }

    // 改变战斗状态回到待机
    _battleState = BattleState::IDLE;// 你可以在这里添加二技能的特殊攻击逻辑
    cocos2d::log("Casting Skill 2!");
}

void BattleScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (_player == nullptr) return;

    // 通过 Z 键切换为一技能，X 键切换为二技能
    switch (keyCode)
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_Z:
            _currentSkillState = SkillState::SKILL_1;  // 切换到一技能
            cocos2d::log("Skill 1 selected.");
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_X:
            _currentSkillState = SkillState::SKILL_2;  // 切换到二技能
            cocos2d::log("Skill 2 selected.");
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_W:
            _player->sprite->setPositionY(_player->sprite->getPositionY() + 5);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_S:
            _player->sprite->setPositionY(_player->sprite->getPositionY() - 5);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_A:
            _player->sprite->setPositionX(_player->sprite->getPositionX() - 5);
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_D:
            _player->sprite->setPositionX(_player->sprite->getPositionX() + 5);
            break;
        default:
            break;
    }
}

void BattleScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_Z || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_X) {
        _currentSkillState = SkillState::NONE;  // 释放技能键后将技能状态设置为NONE
    }
}

void BattleScene::checkBattleOver()
{
    // 检查战斗是否结束
    if (_enemy != nullptr && _enemy->health <= 0)
    {
        endBattle();
    }
}

void BattleScene::endBattle()
{
    // 战斗结束后的逻辑
    cocos2d::log("Battle Over!");
}