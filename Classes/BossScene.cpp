#include "BossScene.h"
#include "BattleScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h" 
#include "Map/MiniMap.h"

std::shared_ptr<Player> rawPlayer1 = GlobalManager::getInstance().getPlayer();      // 获取智能指针指向的 Player 对象的指针
BossScene::BossScene() : _tileMap(nullptr), _currentDialogueBox(nullptr), _currentChoiceBox(nullptr){}
BossScene::~BossScene()                                                             // 析构函数
{
}
cocos2d::Scene* BossScene::createScene()										    // 创建场景
{
	return BossScene::create();												        // 返回创建的场景
}
bool BossScene::init()															    // 初始化函数
{
	const auto& task = GlobalManager::getInstance().getTasks().at(0);               // 获取任务
	const  auto visibleSize = Director::getInstance()->getVisibleSize();		    // 获取屏幕尺寸
	const  auto origin = Director::getInstance()->getVisibleOrigin();			    // 获取屏幕原点
    if (!Scene::init())                                                             //如果 初始化失败  返回false
    {
        return false;
    }

    // 加载 TMX 地图
	_tileMap = cocos2d::TMXTiledMap::create("smallmap/boss.tmx");                   //初始化地图
	_tileMap->setScale(2.5f);													    //设置地图缩放
	if (_tileMap == nullptr)														//如果地图为空
    {
		cocos2d::log("Failed to load map.");										//打印错误信息
		return false;														        //返回false
    }
    this->addChild(_tileMap);                                                       // 将地图添加到场景
    //设置缩放比例
    float scaleX = 3.0f;                                                            // 设置 X 轴缩放比例
    float scaleY = 3.0f;															// 设置 Y 轴缩放比例
    auto tileSize = _tileMap->getTileSize();                                        //获取size    

    // 计算瓦片缩放后大小
    auto playerSize = tileSize;														// 获取玩家的大小
    playerSize.width *= scaleX * 2;                                                 // 计算玩家的宽度
    playerSize.height *= scaleY * 2;												// 计算玩家的高度

    // 从地图的 objects 层中获取玩家和敌人的信息
	const cocos2d::TMXObjectGroup* objectGroup = _tileMap->getObjectGroup("Objects");    // 获取对象组
	if (objectGroup != nullptr)														     // 如果对象组不为空
    {
        cocos2d::ValueMap playerData = objectGroup->getObject("Player");                 // 获取玩家的信息  
		if (!playerData.empty())														 // 如果玩家数据不为空
        {
			float playerX = playerData["x"].asFloat();								     // 获取玩家的 x 坐标
			float playerY = playerData["y"].asFloat();								     // 获取玩家的 y 坐标
            try 
            {                                                                                    
                if (rawPlayer1 == nullptr) {                                             // 1. 空指针检查
					throw std::runtime_error("Player initialization failed: null pointer");// 抛出异常
                }
            }
			catch (const std::exception& e) {											// 捕获异常
				CCLOG("Exception during initialization: %s", e.what());					// 打印异常信息
				cleanup();																// 清理
                throw;                                                                  // 重新抛出异常给上层处理
            }
            rawPlayer1->initWithFile(rawPlayer1->getFileName());						// 初始化玩家
			rawPlayer1->setContentSize(playerSize);									    // 设置玩家的大小
			rawPlayer1->setPosition(Vec2(playerX * 2.5, playerY * 2.5));				// 更新玩家位置变量
			rawPlayer1->Sprite::setPosition(rawPlayer1->getPosition());                 // 设置玩家的位置
            this->addChild(rawPlayer1.get(), 10);                                       // 将玩家添加到场景中
        }

        // 获取敌人的信息 
		cocos2d::ValueMap enemyData = objectGroup->getObject("Boss");                   // 获取敌人的信息
		auto princessObj = objectGroup->getObject("Princess");						    // 获取公主的信息
		float princessX = princessObj["x"].asFloat();									// 获取公主的 x 坐标
		float princessY = princessObj["y"].asFloat();									// 获取公主的 y 坐标
		auto princess = cocos2d::Sprite::create("princess.png");						// 初始化公主
		princess->setPosition(princessX, princessY);									// 设置公主的位置
		this->addChild(princess, 9);													// 将公主添加到场景中
		princess->setContentSize(playerSize);											// 设置公主的大小

        if (!enemyData.empty())
        {
			float enemyX = enemyData["x"].asFloat();    					            // 获取敌人的 x 坐标   
			float enemyY = enemyData["y"].asFloat();					                // 获取敌人的 y 坐标

            auto boss = cocos2d::Sprite::create("enemyboss.png");                       // 初始化敌人
            boss->setContentSize(playerSize);                                           // 设置敌人的大小
            boss->setPosition(Vec2(enemyX * 2.5, enemyY * 2.5));					    // 设置敌人的位置                          
			this->addChild(boss, 10); 												    // 将敌人添加到场景中
			Boss.bossSprite = boss;                                                     // 设定敌人的精灵
			Boss.bossFunction = enemyData["npcData"].asString();						// 获取敌人的功能
			Boss.targetScene = enemyData["targetScene"].asString();						// 获取敌人的目标场景
			Boss.ppp = task;															// 获取任务
			Boss.index = enemyData["index"].asInt();									// 获取敌人的索引
			Boss.taskid = 0;															// 初始化任务id
           
        }
    }

    /*注册键盘事件*/ 
	auto keyListener = cocos2d::EventListenerKeyboard::create();                        // 创建键盘监听器
	keyListener->onKeyPressed = CC_CALLBACK_2(BossScene::onKeyPressed, this);		    // 设置按键按下的回调函数
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);	    // 添加键盘监听器到场景

	this->scheduleUpdate();															    // 调度更新函数
    return true;
}

void BossScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
    cocos2d::Vec2 moveDir;
	switch (keyCode)                                                                     // 根据按键设置移动方向（简略版）
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_W: moveDir = cocos2d::Vec2(0, 1); break;
        case cocos2d::EventKeyboard::KeyCode::KEY_S: moveDir = cocos2d::Vec2(0, -1); break;
        case cocos2d::EventKeyboard::KeyCode::KEY_A: moveDir = cocos2d::Vec2(-1, 0); break;
        case cocos2d::EventKeyboard::KeyCode::KEY_D: moveDir = cocos2d::Vec2(1, 0); break;
        default: return;
    }
	rawPlayer1->setPosition(rawPlayer1->getPosition() + moveDir * 100);				     // 更新坐标变量
	rawPlayer1->Sprite::setPosition(rawPlayer1->getPosition());                          // 更新图上位置
}
/*更新逻辑*/ 
bool BossScene::IsColliding(cocos2d::Vec2 position)
{
    // 获取主控精灵当前世界坐标
    auto playerPos = rawPlayer1->getPosition();                                          //获取坐标   
	auto x = position.x, y = position.y;												 // 获取npc的坐标
	auto tileSize = _tileMap->getTileSize();											 //获取size

    // 现在是npc坐标点为中心的四个瓦片范围，如果需要缩小，请自行/2
    if (playerPos.x >= x - tileSize.width && playerPos.x <= x + tileSize.width && playerPos.y >= y - tileSize.height && playerPos.y <= y + tileSize.height) {
        CCLOG("Collide npc");
        return true;
    }
    return false;
}

void BossScene::update(float delta)
{
    const cocos2d::TMXObjectGroup* objectGroup = _tileMap->getObjectGroup("Objects");

    cocos2d::ValueMap bossData = objectGroup->getObject("Boss");                                     // 获取tmx图上敌人的信息    

    if (!bossData.empty())
    {
		GlobalManager::getInstance().setBattleNpc(GlobalManager::getInstance().getEnemyNpcsBoss());  // 获取敌人的智能指针
		auto bos = Boss.bossSprite;																     // 获取敌人的精灵
		bool isColliding = rawPlayer1->getBoundingBox().intersectsRect(bos->getBoundingBox());	     // 判断玩家与 NPC 是否碰撞
		if (isColliding && !_currentDialogueBox && !_currentChoiceBox && !bos->getUserData())		 // 如果玩家与 NPC 碰撞并且没有对话框
        {
            bos->setUserData((void*)1);                                                              // 标记已交互
			CCLOG("Collide npc");
            displayChoice1(bos, "You can't save the princess!!!Hahahaha!!!\nDo you want to talk with me?", {
    {"Yes",[this, bos]() { {
            this->scheduleOnce([=](float) {                                                          // 延时显示下一个对话框，避免遮挡
                handleChatNPC(bos);
            }, 0.1f, "handleChatNPC");
        } }},
    {"No",[this, bos]() { {
            this->scheduleOnce([=](float) { 													     // 延时显示下一个对话框，避免遮挡                                        
                displayTaskPro(Boss);
            }, 0.1f, "displaybossNPC");
        } }}
                });
        }
        /* 如果玩家与 NPC 没有碰撞并且之前已经交互过，则重置交互状态*/
        else if (!isColliding && bos->getUserData() != nullptr)
        {
            bos->setUserData(nullptr);                                                               // 重置交互状态，允许再次触发
        }
    }
   
}

void BossScene::displayChoice1(cocos2d::Sprite* npc, const std::string& question,
    const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{
    if (_currentChoiceBox) {					    																             // 如果存在当前对话框，移除它
        _currentChoiceBox->removeFromParent();
        _currentChoiceBox = nullptr;
    }
	auto visibleSize = Director::getInstance()->getVisibleSize();												                // 获取可见区域的大小
	_currentChoiceBox = cocos2d::Sprite::create("smallmap/box.png");												            // 创建对话框
	_currentChoiceBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));									    // 设置对话框位置
	this->addChild(_currentChoiceBox);																							// 将对话框添加到场景
    _currentChoiceBox->setLocalZOrder(100);																        				// 让对话框处于较高的层级 
	auto label = cocos2d::Label::createWithTTF(question, "fonts/Marker Felt.ttf", 48);										    // 创建一个 Label 来显示对话框的问题
	label->setTextColor(cocos2d::Color4B::WHITE);																			    // 设置字体颜色
	label->setPosition(_currentChoiceBox->getContentSize().width / 2, _currentChoiceBox->getContentSize().height / 2 + 100);	// 设置 Label 位置
	_currentChoiceBox->addChild(label, 1);																						// 将 Label 添加到对话框中
	label->setLocalZOrder(101);																									// 让 Label 处于较高的层级

	float buttonY = 50;																											// 设置按钮的 Y 坐标
	for (size_t i = 0; i < choices.size(); ++i) 																				// 遍历选项
    {
		cocos2d::ui::Button* button;																							// 创建按钮
        if (i == 0) {
			button = cocos2d::ui::Button::create("Yes1.png", "Yes2.png");													    // 创建按钮
        }
        else if (i == 1) {
			button = cocos2d::ui::Button::create("No1.png", "No2.png");														    // 创建按钮
        }
        button->setPosition(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 4 + i * 300 + 30, _currentChoiceBox->getContentSize().height / 4));
		_currentChoiceBox->addChild(button);																					// 将按钮添加到对话框中

        button->addClickEventListener([=](cocos2d::Ref* sender) {
            if (choices[i].second) {
                choices[i].second();																						    // 执行选择后的回调
            }
                                                                                                                                // 重要：这里移除对话框后再添加新的对话框
            if (_currentChoiceBox) {
				_currentChoiceBox->removeFromParent();                                                                          // 移除对话框
                _currentChoiceBox = nullptr;
            }

            });
    }
}

void BossScene::handleChatNPC(cocos2d::Sprite* npc)
{

    /*显示新的对话框*/ 
    displayChoice2(npc, "Hello! How can I help you today?", {
        {"Tell me about the town", [this, npc]() { {                
				this->scheduleOnce([=](float) { 													  // 延时显示下一个对话框，避免遮挡                                        
                    displayTownInfo(npc);
                }, 0.1f, "handleChatNPC");
            } }},
{"I need a quest", [this, npc]() { {
		this->scheduleOnce([=](float) { 														      // 延时显示下一个对话框，避免遮挡                    
            displayQuestInfo(npc);
        }, 0.1f, "handleChatNPC");
    } }},
{"Nothing, just passing by", [this, npc]() { {
		this->scheduleOnce([=](float) { 														      // 延时显示下一个对话框，避免遮挡
            displayGoodbye(npc);
        }, 0.1f, "handleChatNPC");
    } }},
        });

}

void BossScene::displayChoice2(cocos2d::Sprite* npc, const std::string& question,
    const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{
    // 确保旧对话框被清除
    if (_currentChoiceBox) {
		_currentChoiceBox->removeFromParent();                                                         // 移除对话框
		_currentChoiceBox = nullptr;                                                                   // 设为空指针
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();									   // 获取可见区域的大小
	_currentChoiceBox = cocos2d::Sprite::create("smallmap/box.png");								   // 创建对话框
	_currentChoiceBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 3 / 4));		   // 设置对话框位置
	this->addChild(_currentChoiceBox, 1);															   // 将对话框添加到场景
	_currentChoiceBox->setLocalZOrder(100);														       // 让对话框处于较高的层级

	auto label = cocos2d::Label::createWithTTF(question, "fonts/Marker Felt.ttf", 48);				   // 创建一个 Label 来显示对话框的问题
	label->setTextColor(cocos2d::Color4B::BLACK);													   // 设置字体颜色
	label->setPosition(_currentChoiceBox->getContentSize().width / 2, _currentChoiceBox->getContentSize().height / 2); // 设置 Label 位置
	_currentChoiceBox->addChild(label, 1);															   // 将 Label 添加到对话框中
	label->setLocalZOrder(101);																		   // 让 Label 处于较高的层级

	float buttonY = 50;																				   // 设置按钮的 Y 坐标
	for (size_t i = 0; i < choices.size(); ++i) 													   // 遍历选项
    {
		auto button = cocos2d::ui::Button::create("button1.png", "button2.png");					   // 创建按钮
		button->setTitleText(choices[i].first);														   // 设置按钮标题
		button->setTitleFontName("fonts/Marker Felt.ttf");                                             // 设置按钮字体
		button->setTitleColor(cocos2d::Color3B::BLACK);												   // 设置按钮字体颜色
		button->setTitleFontSize(24);																   // 设置按钮字体大小
        button->setPosition(cocos2d::Vec2(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 2, buttonY + i * 150 -200)));
		_currentChoiceBox->addChild(button);														   // 将按钮添加到对话框中

        button->addClickEventListener([=](cocos2d::Ref* sender) {
            if (choices[i].second) {
                choices[i].second();                                                                   // 执行选择后的回调
            }
			_currentChoiceBox->removeFromParent();													   // 在回调后再移除对话框
			_currentChoiceBox = nullptr;															   // 设为空指针
            });
    }
}
/*NPC 回答关于城镇的情况*/ 
void BossScene::displayTownInfo(cocos2d::Sprite* npc)
{   
    displayChoice2(npc, "This is a peaceful town. You can find a shop, a tavern, and a blacksmith.", {
        {"I see, tell me more!", [this, npc]() { {                                                     // 延时显示下一个对话框，避免遮挡
                this->scheduleOnce([=](float) {
                    displayTownDetails(npc);
                }, 0.1f, "handleChatNPC");
            } }},
		{"That's enough, thanks!", [this, npc]() { {                                                    // 延时显示下一个对话框，避免遮挡
                this->scheduleOnce([=](float) {
                    displayGoodbye(npc);
                }, 0.1f, "handleChatNPC");
            } }}
        });
}

/*NPC 详细介绍城镇*/ 
void BossScene::displayTownDetails(cocos2d::Sprite* npc)
{
    displayDialogue(npc, "The shop sells potions, the tavern offers drinks and rumors, and the blacksmith can upgrade your gear.");
}

/*NPC 给出任务信息*/ 
void BossScene::displayQuestInfo(cocos2d::Sprite* npc)
{
    displayChoice2(npc, "I have a quest for you: Collect 10 herbs.", {

        {"Maybe later", [this, npc]() { }},
        {"Tell me more", [this, npc]() { displayQuestDetails(npc); }}
        });
}
void BossScene::displayTaskPro(bossDATA& npcData) {
    displayChoice1(npcData.bossSprite, npcData.ppp->getTaskName(), {
        {"YES", [this, &npcData]() {
            npcData.ppp->state = 0;                                                                     // 设置任务状态为已分配
			CCLOG("message", npcData.targetScene);                                                      // 打印信息
			rawPlayer1->removeFromParent();															    // 移除玩家
			GlobalManager::getInstance().setLastMap("smallmap/castle.tmx");							    // 设置上一个地图
			const auto& taskListbat = GlobalManager::getInstance().getTasks();                          // 获取任务列表
			taskListbat[0]->id = 0;																	    // 设置任务id
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, BattleScene::create())); // 跳转到 NPC 配置的目标场景
			npcData.ppp->state = 1;																	    // 设置任务状态为已完成

        }},
        {"NO", nullptr}
        });
}
/*NPC 详细任务信息*/ 
void BossScene::displayQuestDetails(cocos2d::Sprite* npc)
{
    displayDialogue(npc, "The herbs grow near the forest. Please bring them back to me once you've collected them.");
}

/*NPC 说“再见”*/ 
void BossScene::displayGoodbye(cocos2d::Sprite* npc)
{
    displayDialogue(npc, "Goodbye, and good luck on your adventures!");
}



void BossScene::displayDialogue(Sprite* npc, const std::string& text)
{
    /*如果存在当前对话框，移除它*/ 
    if (_currentDialogueBox) {
        _currentDialogueBox->removeFromParent();
        _currentDialogueBox = nullptr;
    }

    /* 创建对话框*/
    auto dialogueBox = Sprite::create("box3.png");
    if (!dialogueBox) {
        CCLOG("Failed to create dialogue box!");
        return;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();												// 获取可见区域的大小
	dialogueBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));								// 设置对话框位置
	this->addChild(dialogueBox);																				// 将对话框添加到场景

    /* 创建文本标签*/
	auto label = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 24);                                       // 创建一个 Label 来显示对话框的问题
	label->setTextColor(Color4B::BLACK);																		// 设置字体颜色
	label->setPosition(dialogueBox->getContentSize() / 2);														// 设置 Label 位置
	dialogueBox->addChild(label);																				// 将 Label 添加到对话框中

    /*设置当前对话框*/ 
	_currentDialogueBox = dialogueBox;                                                                          // 设置当前对话框

    /*自动消失对话框*/ 
    this->scheduleOnce([=](float) {
		dialogueBox->removeFromParent();                                                                        // 移除对话框
        _currentDialogueBox = nullptr;
		}, 3.0f, "closeDialogue");                                                                              // 3 秒后自动消失
}