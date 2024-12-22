#include "BattleScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h" 
#include<random>
#include<cstdlib>
#include"Map/MiniMap.h"
#include"SmallTask/QuizGame.h"
std::shared_ptr<Player> rawPlayer = GlobalManager::getInstance().getPlayer();

const float NEARESTLENGTH = 100.0f;//最近距离
// 获取智能指针指向的 Player 对象的指针

// 构造函数和析构函数
BattleScene::BattleScene()
    : _battleState(BattleState::IDLE),  
    _tileMap(nullptr),
	_skillDirection(cocos2d::Vec2::ZERO),										    // 初始化技能方向为 0
    _currentSkillState(SkillState::NONE),                                           // 初始技能状态为NONE
	_enemyHealthLabel(nullptr),                                                     // 初始化敌人生命值的 Label 为 nullptr
	_playerHealthLabel(nullptr)                                                     // 初始化玩家生命值的 Label 为 nullptr
{
}

BattleScene::~BattleScene() {}

bool BattleScene::init()
{
	const  auto visibleSize = Director::getInstance()->getVisibleSize();			    //获取size
	const  auto origin = Director::getInstance()->getVisibleOrigin();				    //获取原点
     
	if (!Scene::init())                                                                 //如果 初始化失败  返回false
    {
        return false;
    }

    /*加载 TMX 地图*/ 
	_tileMap = cocos2d::TMXTiledMap::create("smallmap/battlefeild.tmx");			    // 加载地图
	_tileMap->setScale(8.0f);														    // 设置地图缩放比例
	if (_tileMap == nullptr)														    //如果地图为空
    {
        cocos2d::log("Failed to load map.");
        return false;
    }
    this->addChild(_tileMap);                                                           // 将地图添加到场景
     
    /*设置缩放比例*/
	float scaleX = 3.0f;                                                                // 设置 X 轴缩放比例
	float scaleY = 3.0f;																// 设置 Y 轴缩放比例
    auto tileSize = _tileMap->getTileSize();                                            //获取size    

    /*计算瓦片缩放后大小*/ 
	auto playerSize = tileSize;														    // 获取玩家的大小
	playerSize.width *= scaleX * 2;                                                     // 计算玩家的宽度
	playerSize.height *= scaleY * 2;													// 计算玩家的高度

    /*从地图的 objects 层中获取玩家和敌人的信息*/ 
    const cocos2d::TMXObjectGroup* objectGroup = _tileMap->getObjectGroup("Objects");
    if (objectGroup != nullptr)
    { 
        cocos2d::ValueMap playerData = objectGroup->getObject("Player");                                // 获取玩家的信息  
        if (!playerData.empty())
        {
            float playerX = playerData["x"].asFloat();
            float playerY = playerData["y"].asFloat();
            try {  
                                                                                                        //  空指针检查
                if (rawPlayer == nullptr) {
                    throw std::runtime_error("Player initialization failed: null pointer");
                } 
            }
            catch (const std::exception& e) {
                CCLOG("Exception during initialization: %s", e.what());
                cleanup(); 
				throw;                                                                                  // 重新抛出异常给上层处理
            } 
			rawPlayer->initWithFile(rawPlayer->getFileName());											// 初始化玩家
			rawPlayer->setContentSize(playerSize);														// 设置玩家的大小
			rawPlayer->setPosition(Vec2(playerX * 8, playerY * 8));										// 设置玩家位置变量
			rawPlayer->Sprite::setPosition(rawPlayer->getPosition());									// 设置玩家图上位置
			this->addChild(rawPlayer.get(), 10);                                                        // 将玩家添加到场景中
        }
		cocos2d::ValueMap enemyData = objectGroup->getObject("NPC");									// 获取敌人的信息

        if (!enemyData.empty())
        {
			float enemyX = enemyData["x"].asFloat();                                                    // 获取敌人的 x 坐标
			float enemyY = enemyData["y"].asFloat();													// 获取敌人的 y 坐标
            
            try {
				rawEnemy = GlobalManager::getInstance().getBattleNpc();                                 // 获取敌人
                // 1. 空指针检查
                if (rawEnemy == nullptr) {
                    throw std::runtime_error("Player initialization failed: null pointer");
                }

                // 2. 初始化检查
                if (!rawEnemy->init()) {
                    throw std::runtime_error("Player initialization failed");
                }
            }
            catch (const std::exception& e) {
                CCLOG("Exception during initialization: %s", e.what());
                cleanup();
                // 重新抛出异常给上层处理
                throw;
            }
			rawEnemy->initWithFile();                                                                   // 初始化敌人
			rawEnemy->setContentSize(playerSize);                                                       // 设置敌人的大小
			rawEnemy->setPosition(Vec2(enemyX * 8, enemyY * 8));					                    // 设置敌人的位置
			enemyskill = rawEnemy->getSkill();                                                          // 获取敌人的技能
            this->addChild(rawEnemy.get(), 10);                                                         // 将敌人添加到场景中
        }
    } 
    // 创建技能粒子效果
    askillList.at(0)->_effect = cocos2d::ParticleSystemQuad::create(askillList.at(0)->_info.particleFile);//初始化特效
    askillList.at(0)->_effect->setVisible(false);                                                         //初始时隐藏 
	this->addChild(askillList.at(0)->_effect, 10);                                                        //将特效添加到场景中
    askillList.at(1)->_effect = cocos2d::ParticleSystemQuad::create(askillList.at(1)->_info.particleFile);//初始化特效
    askillList.at(1)->_effect->setVisible(false);                                                         //初始时隐藏
    this->addChild(askillList.at(1)->_effect, 10);                                                        //将特效添加到场景中  
    askillList.at(2)->_effect = cocos2d::ParticleSystemQuad::create(askillList.at(2)->_info.particleFile);//初始化特效
    askillList.at(2)->_effect->setVisible(false);                                                         //初始时隐藏
	this->addChild(askillList.at(2)->_effect, 10);														  //将特效添加到场景中

    enemyskill->_effect = cocos2d::ParticleSystemQuad::create(enemyskill->_info.particleFile);            //初始化特效
    enemyskill->_effect->setVisible(false);                                                               //初始时隐藏
	this->addChild(enemyskill->_effect, 10);															  //将特效添加到场景中

	askillList.at(0)->setColor(rawPlayer->getElement());                                                  //设置技能颜色
    askillList.at(1)->setColor(rawPlayer->getElement());
    askillList.at(2)->setColor(rawPlayer->getElement());
    enemyskill->setColor(rawEnemy->getElement());
    
    _playerHealthLabel = cocos2d::Label::createWithTTF("Health: 100", "fonts/Marker Felt.ttf", 48);       // 创建一个 Label 来显示玩家当前的生命值 
    if (_playerHealthLabel != nullptr)
    {
		_playerHealthLabel->setPosition(cocos2d::Vec2(rawPlayer->getPosition().x, rawPlayer->getPosition().y + 150));// 设置 Label 的位置
        this->addChild(_playerHealthLabel, 1);                                                            // 将 Label 添加到场景中
    }         
	_enemyHealthLabel = cocos2d::Label::createWithTTF("Health: 100", "fonts/Marker Felt.ttf", 48);        // 创建一个 Label 来显示敌人当前的生命值
    if (_enemyHealthLabel != nullptr)
    {
		_enemyHealthLabel->setPosition(cocos2d::Vec2(rawEnemy->getPosition().x, rawEnemy->getPosition().y + 150));// 设置 Label 的位置
        this->addChild(_enemyHealthLabel, 1);                                                             // 将 Label 添加到场景中
    }

    // 设置场景更新
    schedule([=](float deltaTime) 
    {
        update(deltaTime);
    }, "update_key");

    // 设置键盘和鼠标监听事件
	auto listenerKeyboard = cocos2d::EventListenerKeyboard::create();                               // 创建键盘监听器
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(BattleScene::onKeyPressed, this);                // 设置按键按下的回调函数
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(BattleScene::onKeyReleased, this);  	        // 设置按键释放的回调函数
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);			    // 添加键盘监听器到场景

	auto listenerMouse = cocos2d::EventListenerMouse::create();									    // 创建鼠标监听器
	listenerMouse->onMouseDown = CC_CALLBACK_1(BattleScene::onMouseDown, this);					    // 设置鼠标按下的回调函数
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);				    // 添加鼠标监听器到场景

    return true;
}

void BattleScene::update(float delta)
{
    if (!gameOver)
    {    // 更新技能效果  的位置
		cooldownTime -= delta;                                                                 // 更新冷却时间
        if(cooldownTime<=0)
			cooldownTime = 0;                                                                  // 冷却时间小于0时，设置为0
        if (askillList.at(0)->_effect->isVisible())
        {
            askillList.at(0)->_effect->setPosition(rawPlayer->getPosition());                   // 设置粒子系统的位置
        } 
        if (askillList.at(1)->_effect->isVisible())
        {
            askillList.at(1)->_effect->setPosition(rawPlayer->getPosition());                   // 设置粒子系统的位置
        } 
        if (askillList.at(2)->_effect->isVisible())
        {
            askillList.at(2)->_effect->setPosition(rawPlayer->getPosition());                   // 设置粒子系统的位置
        }
        if (enemyskill->_effect->isVisible())
        {
            enemyskill->_effect->setPosition(rawEnemy->getPosition());                          // 设置粒子系统的位置    
        }
        enemyMove();                                                                            // 敌人移动
        EnemyAttack();  														    		    // 敌人攻击 
        if (rawEnemy != nullptr)                                                                // 更新敌人生命值的显示
        {
            _enemyHealthLabel->setString("Health: " + std::to_string(rawEnemy->getHp()));       // 更新显示的敌人生命值
            _enemyHealthLabel->setPosition(cocos2d::Vec2(rawEnemy->getPosition().x, rawEnemy->getPosition().y + 150)); // 更新 Label 位置，使其始终跟随敌人
        }
        if (rawPlayer != nullptr)   												            // 更新玩家生命值的显示                                                
        {
            _playerHealthLabel->setString("Health: " + std::to_string(rawPlayer->getHp()));     // 更新显示的玩家生命值
            _playerHealthLabel->setPosition(cocos2d::Vec2(rawPlayer->Sprite::getPosition().x, rawPlayer->Sprite::getPosition().y + 150)); // 更新 Label 位置，使其始终跟随敌人
        }
		checkBattleOver();																	    // 检查战斗是否结束
    }
}

void BattleScene::onMouseDown(cocos2d::Event* event)
{
	cocos2d::EventMouse* mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);				// 获取鼠标事件   
    if (mouseEvent&&!gameOver)
    {
        float degrees;
        // 获取鼠标点击的世界坐标
        cocos2d::Vec2 clickPosition = mouseEvent->getLocation();                                // 使用 getLocation() 获取鼠标位置
		CCLOG("Mouse clicked at (%f, %f)", clickPosition.x, clickPosition.y);                   // 输出鼠标点击的位置
		Vec2 mapclickPosition = Vec2(clickPosition.x, 1000 - clickPosition.y);                  // 获取地图点击的位置
		CCLOG("mapclickPosition at (%f, %f)", mapclickPosition.x, mapclickPosition.y);          // 输出地图点击的位置
		if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)     // 右键点击
        {
			_battleState = BattleState::ATTACKING;                                              // 设置战斗状态为攻击
            if (_currentSkillState == SkillState::SKILL_1) {
                degrees = askillList.at(1)->cast(rawPlayer.get(), mapclickPosition);            // 执行一技能 角度获取
                askillList.at(1)->_effect->setAngle(degrees);                                  // 设置粒子的发射角度 
				askillList.at(1)->_effect->setPosition(rawPlayer->getPosition());              // 设置粒子系统的位置 
                askillList.at(1)->_effect->setVisible(true);                                    // 启用粒子效果并播放
                askillList.at(1)->_effect->resetSystem();                                       // 启动粒子系统 
                scheduleOnce([this](float dt) {                                                 // 设置技能持续时间（2秒）
                    // 2秒后停止粒子效果
                    askillList.at(1)->_effect->stopSystem();                                    // 停止粒子系统
                    askillList.at(1)->_effect->setVisible(false);                               // 隐藏粒子系统
                    }, 1.0f, "stop_skill_effect");                                              // 2秒后调用
                _battleState = BattleState::ATTACKING;
                if (askillList.at(1)->isInRange(rawPlayer->getPosition(), rawEnemy->getPosition(), mapclickPosition))//判断是否在攻击范围内
                {
                    if (rawEnemy->getElement() > rawPlayer->getElement())                                               //判断敌人的元素是否克制玩家的元素
                        rawEnemy->TakeDamage((askillList.at(1)->getAttack() + rawPlayer->getAttack()) / 2);             //敌人受到伤害减半
                    else if (rawEnemy->getElement() > rawPlayer->getElement())  						                //判断玩家的元素是否克制敌人的元素
                        rawEnemy->TakeDamage((askillList.at(1)->getAttack() + rawPlayer->getAttack()) * 2);             //敌人受到伤害翻倍
                    else
                        rawEnemy->TakeDamage(askillList.at(1)->getAttack() + rawPlayer->getAttack());                   //普通攻击伤害
                    CCLOG("Enemy is HURT!");
                }
            }
            else if (_currentSkillState == SkillState::SKILL_2) {
                degrees = askillList.at(2)->cast(rawPlayer.get(), mapclickPosition);            // 执行一技能  
                askillList.at(2)->_effect->setAngle(degrees);                                   // 设置粒子的发射角度
                CCLOG("degrees:%f", degrees);
                
                askillList.at(2)->_effect->setPosition(rawPlayer->getPosition());               // 设置粒子系统的位置
                 
				askillList.at(2)->_effect->setVisible(true);									// 启用粒子效果并播放
                askillList.at(2)->_effect->resetSystem();                                       // 启动粒子系统
                 
                scheduleOnce([this](float dt) {
                                                                                                // 1秒后停止粒子效果
                    askillList.at(2)->_effect->stopSystem();                                    // 停止粒子系统
                    askillList.at(2)->_effect->setVisible(false);                               // 隐藏粒子系统
                    }, 1.0f, "stop_skill_effect");                                              // 1秒后调用
                _battleState = BattleState::ATTACKING;
                if (askillList.at(2)->isInRange(rawPlayer->getPosition(), rawEnemy->getPosition(), mapclickPosition))//判断是否在攻击范围内
                {
                    if (rawEnemy->getElement() > rawPlayer->getElement())                                               //判断敌人的元素是否克制玩家的元素
                        rawEnemy->TakeDamage((askillList.at(2)->getAttack() + rawPlayer->getAttack()) / 2);             //敌人受到伤害减半
                    else if (rawEnemy->getElement() > rawPlayer->getElement())  						                //判断玩家的元素是否克制敌人的元素
                        rawEnemy->TakeDamage((askillList.at(2)->getAttack() + rawPlayer->getAttack()) * 2);             //敌人受到伤害翻倍
                    else
                        rawEnemy->TakeDamage(askillList.at(2)->getAttack() + rawPlayer->getAttack());                   //普通攻击伤害
                    CCLOG("Enemy is HURT!");
                }
            }
        }
        else if (mouseEvent->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
        {// 普通攻击
            degrees = askillList.at(0)->cast(rawPlayer.get(), mapclickPosition);                            // 执行普通攻击特效 
            askillList.at(0)->_effect->setAngle(degrees);                                                   // 设置粒子的发射角度 
			askillList.at(0)->_effect->setPosition(rawPlayer->getPosition());							    // 设置粒子系统的位置  
			askillList.at(0)->_effect->setVisible(true);												    // 启用粒子效果并播放
            askillList.at(0)->_effect->resetSystem();                                                       // 启动粒子系统

            // 设置技能持续时间（2秒）
            scheduleOnce([this](float dt) {
                // 2秒后停止粒子效果
                askillList.at(0)->_effect->stopSystem();                                                    // 停止粒子系统
                askillList.at(0)->_effect->setVisible(false);                                               // 隐藏粒子系统
                }, 1.0f, "stop_skill_effect");                                                              // 1秒后调用
            _battleState = BattleState::ATTACKING;
            if (askillList.at(0)->isInRange(rawPlayer->getPosition(), rawEnemy->getPosition(), mapclickPosition))
            {
                if (rawEnemy->getElement() > rawPlayer->getElement())                                               //判断敌人的元素是否克制玩家的元素
                    rawEnemy->TakeDamage((askillList.at(0)->getAttack() + rawPlayer->getAttack()) / 2);             //敌人受到伤害减半
                else if (rawEnemy->getElement() > rawPlayer->getElement())  						                //判断玩家的元素是否克制敌人的元素
                    rawEnemy->TakeDamage((askillList.at(0)->getAttack() + rawPlayer->getAttack()) * 2);             //敌人受到伤害翻倍
                else
                    rawEnemy->TakeDamage(askillList.at(0)->getAttack() + rawPlayer->getAttack());                   //普通攻击伤害
                CCLOG("Enemy is HURT!");
            }
        }
    }

    // 改变战斗状态回到待机
    _battleState = BattleState::IDLE;
    cocos2d::log("Player is attacking!");
}




void BattleScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (rawPlayer == nullptr) return;

    // 通过 Z 键切换为一技能，X 键切换为二技能
    Vec2 nextpos = rawPlayer->getPosition();
    CCLOG("Key with keycode %d pressed", keyCode);
    switch (keyCode)
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_SHIFT:
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_Z:
            _currentSkillState = SkillState::SKILL_1;  // 切换到一技能
            cocos2d::log("Skill 1 selected.");
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_X:
            _currentSkillState = SkillState::SKILL_2;  // 切换到二技能
            cocos2d::log("Skill 2 selected.");
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_W:
            nextpos.y = rawPlayer->getPosition().y + rawPlayer->getSpeed() * Director::getInstance()->getDeltaTime();
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_S:
            nextpos.y = rawPlayer->getPosition().y - rawPlayer->getSpeed() * Director::getInstance()->getDeltaTime();
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_A:
            nextpos.x = rawPlayer->getPosition().x - rawPlayer->getSpeed() * Director::getInstance()->getDeltaTime();
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_D:
            nextpos.x = rawPlayer->getPosition().x + rawPlayer->getSpeed() * Director::getInstance()->getDeltaTime();
            break;
        default:
            break;
    }
	rawPlayer->setPosition(nextpos);                                                                            // 设置玩家的位置
	rawPlayer->Sprite::setPosition(nextpos);																	// 设置玩家的图像位置
	CCLOG("next_position:%f %f", nextpos.x, nextpos.y);                                                         // 输出玩家的位置
}

void BattleScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_Z || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_X) {
        _currentSkillState = SkillState::NONE;                                                                  // 释放技能键后将技能状态设置为NONE
    }
    else {
        switch (keyCode)
        {
            case EventKeyboard::KeyCode::KEY_W:
                rawPlayer->isMovingUp = false;
                break;
            case EventKeyboard::KeyCode::KEY_S:
                rawPlayer->isMovingUp = false;
                break;
            case EventKeyboard::KeyCode::KEY_A:
                rawPlayer->isMovingUp = false;
                break;
            case EventKeyboard::KeyCode::KEY_D:
                rawPlayer->isMovingUp = false;
                break;
        }
    }
}

void BattleScene::checkBattleOver()
{
    // 检查战斗是否结束 
     // 检查战斗是否结束
	if (rawEnemy->getHp() == 0 && rawEnemy->getLevel() >= 2)                            //判断任务是否完成         
    {
        ElementType type = rawEnemy->getElement();
        std::vector <std::shared_ptr< Task >> tasklist = GlobalManager::getInstance().getTasks();
        switch (type)
        {
            case ElementType::Gold:
                tasklist.at(1)->state = 1;
                break;
            case ElementType::Wood:
                tasklist.at(2)->state = 1;
                break;
            case ElementType::Earth:
                tasklist.at(3)->state = 1;
                break;
            case ElementType::Water:
                tasklist.at(4)->state = 1;
                break;
            case ElementType::Fire:
                tasklist.at(5)->state = 1;
                break;
        }
        if(rawEnemy->getLevel()==3)                                                     //boss
		{
			tasklist.at(0)->state = 1;                                                  //标记主任务完成
		}
    }
    if (rawPlayer->getHp() == 0)                                                        //如果我输了
    { 
        auto winLabel = Label::createWithTTF("YOU LOSE", "fonts/arial.ttf", 80);        // 创建文字标签
        Size visibleSize = Director::getInstance()->getVisibleSize();                   //获取visibleSize
        winLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));     //定位到中央
        winLabel->setColor(Color3B::YELLOW);                                            // 设置颜色
        this->addChild(winLabel);                                                       //加入child
    }
    else if (rawEnemy->getHp() == 0)                                                    //如果我赢了
    { 
        auto winLabel = Label::createWithTTF("YOU WIN!", "fonts/arial.ttf", 80);        // 创建文字标签
        Size visibleSize = Director::getInstance()->getVisibleSize();                  //获取visibleSize
        winLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));    //定位到中央
        winLabel->setColor(Color3B::RED);                                              // 设置颜色
		this->addChild(winLabel, 99);												   //加入child
        rawEnemy->dead(); 
    }
	if (rawPlayer->getHp() == 0 || rawEnemy->getHp() == 0)
	{
		rawPlayer->setHp(rawPlayer->getMaxHp());									  //重置玩家生命值
		const auto& taskListbat = GlobalManager::getInstance().getTasks();			  //获取任务列表
		int id = taskListbat[0]->getid();											  //获取任务id
		taskListbat[id]->state = 1;													  //标记任务完成
		gameOver = true;															  //游戏结束
		endBattle();																  //结束战斗
	}
}

void BattleScene::endBattle()
{
	auto exitButton = cocos2d::ui::Button::create("CloseNormal.png", "CloseSelected.png"); // 创建按钮
    if (!exitButton)
    {
        CCLOGERROR("Failed to create exit button.");
        return;
    }

    /*设置按钮位置（屏幕右上角）*/ 
    auto visibleSize = Director::getInstance()->getVisibleSize();                                   // 获取屏幕尺寸
    auto origin = Director::getInstance()->getVisibleOrigin();				                        // 获取屏幕原点
    exitButton->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2-100));	    // 设置按钮位置

    /*设置按钮点击事件*/  
    exitButton->addClickEventListener([](Ref* sender) {
		CCLOG("Exit button clicked. Exiting game.");							                    // 输出信息
		rawPlayer->removeFromParent();											                    // 移除玩家
		auto newScene = MiniMap::createWithMap(GlobalManager::getInstance().getLastMap(), false);   // 创建新场景
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, newScene));              // 退出游戏
        }); 
    this->addChild(exitButton, 10);                                                                 // 添加按钮到场景
}


void BattleScene::enemyMove()
{ 
	Vec2 playerPos = rawPlayer->getPosition();                                                      //获取玩家位置
	Vec2 enemyPos = rawEnemy->getPosition();														//获取敌人位置
	float thedistance = playerPos.distance(enemyPos);											    //获取距离
	if (thedistance > NEARESTLENGTH)																//如果距离大于最近距离
    {
        if (playerPos.y < enemyPos.y) {                                                             //如果玩家得y坐标小于敌人的y坐标
			enemyPos.y -= 50 * Director::getInstance()->getDeltaTime();							    //敌人向下移动
        }
        else
			enemyPos.y += 50 * Director::getInstance()->getDeltaTime();							    //否则敌人向上移动

		if (playerPos.x < enemyPos.x) {                                                             //如果玩家得x坐标小于敌人的x坐标
			enemyPos.x -= 50 * Director::getInstance()->getDeltaTime();                             //敌人向左移动
        }
        else
			enemyPos.x += 50 * Director::getInstance()->getDeltaTime();							    //否则敌人向右移动
		CCLOG("enemy position:%f %f", enemyPos.x, enemyPos.y);                                      //输出敌人位置
		CCLOG("player position:%f %f", playerPos.x, playerPos.y);								    //输出玩家位置
    }
    rawEnemy->setPosition(enemyPos);

}

void BattleScene::EnemyAttack()
{// 敌人攻击逻辑
    std::srand(std::time(0));                                                                       // 设置随机数种子
    Vec2 rawplayerpos = rawPlayer->getPosition();                                                   //玩家位置
    Vec2 rawenemypos = rawEnemy->getPosition();                                                     //敌人位置  
    float thedistance = rawplayerpos.distance(rawenemypos);                                         //距离
    float degrees = askillList.at(0)->cast(rawEnemy.get(), rawplayerpos);                           // 执行攻击 的角度求解 
    enemyskill->_effect->setAngle(degrees);                                                         // 设置粒子的发射角度 
	enemyskill->_effect->setPosition(rawEnemy->getPosition());			                            // 设置粒子系统的位置
    int randomnum1 = std::rand() % 100 + 1;                                                         // 生成 1 到 100 之间的随机数
    
	if (enemyskill->isInRange(rawPlayer->getPosition(), rawEnemy->getPosition()))                   //判断是否在攻击范围内
    {
		if (randomnum1 > 50&&cooldownTime==0)                                                       // 50%的概率使用技能
        {
			cocos2d::log("Enemy is attacking!");                                                    // 输出敌人正在攻击
            enemyskill->_effect->setVisible(true);  						                        // 启用粒子效果并播放                                
            enemyskill->_effect->resetSystem();                                                     // 启动粒子系统
            scheduleOnce([this](float dt) {
                enemyskill->_effect->stopSystem();                                                  // 停止粒子系统
                enemyskill->_effect->setVisible(false);                                             // 隐藏粒子系统
				}, 2.0f, "stop_skill_effect");                                                      // 2s后调用
            _battleState = BattleState::ATTACKING;                                                  //更改战斗状态    
        }
        int randomnum = std::rand() % 100 + 1;                                                      // 生成 1 到 100 之间的随机数
        if (randomnum > 50&& cooldownTime == 0)                                                     //50%的击中概率
        {
			// 判断敌人元素与玩家元素的关系
            if (rawEnemy->getElement() > rawPlayer->getElement())                                   //判断敌人的元素是否克制玩家的元素
                rawPlayer->TakeDamage((askillList.at(1)->getAttack() + rawPlayer->getAttack()) * 2);//玩家受到伤害加倍
            else if (rawEnemy->getElement() > rawPlayer->getElement())  						    //判断玩家的元素是否克制敌人的元素
                rawPlayer->TakeDamage((askillList.at(1)->getAttack() + rawPlayer->getAttack()) / 2);//晚间受到伤害减半
            else
                rawPlayer->TakeDamage(rawEnemy->getAttack() + enemyskill->getAttack());             //玩家受到普通伤害    
            cooldownTime = 2.0f;    								                                // 重置冷却时间       
        }
    
        CCLOG("Player is HURT!");
    } 
	_battleState = BattleState::IDLE;															   // 更改战斗状态为待机

}

