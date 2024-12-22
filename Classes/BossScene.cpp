#include "BossScene.h"
#include "BattleScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h" 
#include "Map/MiniMap.h"

std::shared_ptr<Player> rawPlayer1 = GlobalManager::getInstance().getPlayer();
BossScene::BossScene() : _tileMap(nullptr), _currentDialogueBox(nullptr), _currentChoiceBox(nullptr){}
BossScene::~BossScene() 
{

}
cocos2d::Scene* BossScene::createScene()
{
    return BossScene::create();
}
bool BossScene::init()

{

    const auto& task = GlobalManager::getInstance().getTasks().at(0);
    const  auto visibleSize = Director::getInstance()->getVisibleSize();
    const  auto origin = Director::getInstance()->getVisibleOrigin();

    if (!Scene::init())                                                             //如果 初始化失败  返回false
    {
        return false;
    }

    // 加载 TMX 地图
    _tileMap = cocos2d::TMXTiledMap::create("smallmap/boss.tmx");
    _tileMap->setScale(2.5f);
    if (_tileMap == nullptr)
    {
        cocos2d::log("Failed to load map.");
        return false;
    }
    this->addChild(_tileMap);  // 将地图添加到场景

    //设置缩放比例
    float scaleX = 3.0f;                                                                // 设置 X 轴缩放比例
    float scaleY = 3.0f;																// 设置 Y 轴缩放比例
    auto tileSize = _tileMap->getTileSize();                                            //获取size    

    // 计算瓦片缩放后大小
    auto playerSize = tileSize;														    // 获取玩家的大小
    playerSize.width *= scaleX * 2;                                                     // 计算玩家的宽度
    playerSize.height *= scaleY * 2;													// 计算玩家的高度

    // 从地图的 objects 层中获取玩家和敌人的信息
    const cocos2d::TMXObjectGroup* objectGroup = _tileMap->getObjectGroup("Objects");
    if (objectGroup != nullptr)
    {
        cocos2d::ValueMap playerData = objectGroup->getObject("Player");                 // 获取玩家的信息  
       
        if (!playerData.empty())
        {
            float playerX = playerData["x"].asFloat();
            float playerY = playerData["y"].asFloat();
            try 
            {                                                                                    // 1. 空指针检查
                if (rawPlayer1 == nullptr) {
                    throw std::runtime_error("Player initialization failed: null pointer");
                }
            }
            catch (const std::exception& e) {
                CCLOG("Exception during initialization: %s", e.what());
                cleanup();
                throw;                                                                                  // 重新抛出异常给上层处理
            }
            rawPlayer1->initWithFile(rawPlayer1->getFileName());											// 初始化玩家
            //rawPlayer1->initWithFile("Tree.png");
            rawPlayer1->setContentSize(playerSize);
            rawPlayer1->setPosition(Vec2(playerX * 2.5, playerY * 2.5));
            rawPlayer1->Sprite::setPosition(rawPlayer1->getPosition());
            this->addChild(rawPlayer1.get(), 10);  // 将玩家添加到场景中
        }

        // 获取敌人的信息 
        cocos2d::ValueMap enemyData = objectGroup->getObject("Boss");
        auto princessObj = objectGroup->getObject("Princess");
		float princessX = princessObj["x"].asFloat();
		float princessY = princessObj["y"].asFloat();
		auto princess = cocos2d::Sprite::create("princess.png");
		princess->setPosition(princessX, princessY);
		this->addChild(princess, 9);
		princess->setContentSize(playerSize);



        if (!enemyData.empty())
        {
            float enemyX = enemyData["x"].asFloat();
            float enemyY = enemyData["y"].asFloat();

            auto boss = cocos2d::Sprite::create("enemyboss.png");                                // 初始化敌人
            boss->setContentSize(playerSize);                                   // 设置敌人的大小
            boss->setPosition(Vec2(enemyX * 2.5, enemyY * 2.5));					// 设置敌人的位置                                     // 获取敌人的技能
            this->addChild(boss, 10); 
            Boss.bossSprite = boss;
            Boss.bossFunction = enemyData["npcData"].asString();
			Boss.targetScene = enemyData["targetScene"].asString();
            Boss.ppp = task;
			Boss.index = enemyData["index"].asInt();
            Boss.taskid = 0;
          
            // 将敌人添加到场景中
        }
    }

    // 注册键盘事件
    auto keyListener = cocos2d::EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(BossScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    
    this->scheduleUpdate();
    return true;

    return true;
}

void BossScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
    cocos2d::Vec2 moveDir;
    switch (keyCode)
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_W: moveDir = cocos2d::Vec2(0, 1); break;
        case cocos2d::EventKeyboard::KeyCode::KEY_S: moveDir = cocos2d::Vec2(0, -1); break;
        case cocos2d::EventKeyboard::KeyCode::KEY_A: moveDir = cocos2d::Vec2(-1, 0); break;
        case cocos2d::EventKeyboard::KeyCode::KEY_D: moveDir = cocos2d::Vec2(1, 0); break;
        default: return;
    }
    rawPlayer1->setPosition(rawPlayer1->getPosition() + moveDir * 100);
	rawPlayer1->Sprite::setPosition(rawPlayer1->getPosition());
}
// 更新逻辑
bool BossScene::IsColliding(cocos2d::Vec2 position)
{
    // 获取主控精灵当前世界坐标
    auto playerPos = rawPlayer1->getPosition();
    auto x = position.x, y = position.y;

    // 获取瓦片地图的瓦片大小
    auto tileSize = _tileMap->getTileSize();

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
    // 获取敌人的信息 
    cocos2d::ValueMap bossData = objectGroup->getObject("Boss");

    if (!bossData.empty())
    {
        GlobalManager::getInstance().setBattleNpc(GlobalManager::getInstance().getEnemyNpcsBoss());
        auto bos = Boss.bossSprite;
        bool isColliding = rawPlayer1->getBoundingBox().intersectsRect(bos->getBoundingBox());

        if (isColliding && !_currentDialogueBox && !_currentChoiceBox && !bos->getUserData())
        {
            bos->setUserData((void*)1); // 标记已交
			CCLOG("Collide npc");
            displayChoice1(bos, "You can't save the princess!!!Hahahaha!!!\nDo you want to talk with me?", {
    {"Yes",[this, bos]() { {
            // 延时显示下一个对话框，避免遮挡
            this->scheduleOnce([=](float) {
                handleChatNPC(bos);
            }, 0.1f, "handleChatNPC");
        } }},
    {"No",[this, bos] () { {
            // 延时显示下一个对话框，避免遮挡
            this->scheduleOnce([=](float) {
                displayTaskPro(Boss);
            }, 0.1f, "displaybossNPC");
        } }}
                });
        }
        // 如果玩家与 NPC 没有碰撞并且之前已经交互过，则重置交互状态
        else if (!isColliding && bos->getUserData() != nullptr)
        {
            bos->setUserData(nullptr);  // 重置交互状态，允许再次触发
        }
    }
   
}

void BossScene::displayChoice1(cocos2d::Sprite* npc, const std::string& question,
    const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{
    if (_currentChoiceBox) {																					           		  // 如果存在当前对话框，移除它
        _currentChoiceBox->removeFromParent();
        _currentChoiceBox = nullptr;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    _currentChoiceBox = cocos2d::Sprite::create("smallmap/box.png");
    //_currentChoiceBox->setPosition(npc->getPosition() + cocos2d::Vec2(0, 80)); 
    _currentChoiceBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(_currentChoiceBox);
    _currentChoiceBox->setLocalZOrder(100);																        				 // 让对话框处于较高的层级 
    auto label = cocos2d::Label::createWithTTF(question, "fonts/Marker Felt.ttf", 48);
    label->setTextColor(cocos2d::Color4B::WHITE);
    label->setPosition(_currentChoiceBox->getContentSize().width / 2, _currentChoiceBox->getContentSize().height / 2 + 100);
    _currentChoiceBox->addChild(label, 1);
    label->setLocalZOrder(101);

    float buttonY = 50;
    for (size_t i = 0; i < choices.size(); ++i)
    {
        cocos2d::ui::Button* button;
        if (i == 0) {
            button = cocos2d::ui::Button::create("Yes1.png", "Yes2.png");
        }
        else if (i == 1) {
            button = cocos2d::ui::Button::create("No1.png", "No2.png");
        }
        //button->setTitleText(choices[i].first);
        //button->setTitleFontName("fonts/Marker Felt.ttf");
        //button->setTitleFontSize(24);
        button->setPosition(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 4 + i * 300 + 30, _currentChoiceBox->getContentSize().height / 4));
        _currentChoiceBox->addChild(button);

        button->addClickEventListener([=](cocos2d::Ref* sender) {
            if (choices[i].second) {
                choices[i].second();																						// 执行选择后的回调
            }
            // 重要：这里移除对话框后再添加新的对话框
            if (_currentChoiceBox) {
                _currentChoiceBox->removeFromParent();
                _currentChoiceBox = nullptr;
            }

            });
    }
}

void BossScene::handleChatNPC(cocos2d::Sprite* npc)
{

    // 显示新的对话框
    displayChoice2(npc, "Hello! How can I help you today?", {
        {"Tell me about the town", [this, npc]() { {
                // 延时显示下一个对话框，避免遮挡
                this->scheduleOnce([=](float) {
                    displayTownInfo(npc);
                }, 0.1f, "handleChatNPC");
            } }},
{"I need a quest", [this, npc]() { {
        // 延时显示下一个对话框，避免遮挡
        this->scheduleOnce([=](float) {
            displayQuestInfo(npc);
        }, 0.1f, "handleChatNPC");
    } }},
{"Nothing, just passing by", [this, npc]() { {
        // 延时显示下一个对话框，避免遮挡
        this->scheduleOnce([=](float) {
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
        _currentChoiceBox->removeFromParent();
        _currentChoiceBox = nullptr;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();												// 获取可见区域的大小
    _currentChoiceBox = cocos2d::Sprite::create("smallmap/box.png");
    _currentChoiceBox->setPosition(Vec2(visibleSize.width / 2,visibleSize.height*3/4));
    this->addChild(_currentChoiceBox, 1);
    _currentChoiceBox->setLocalZOrder(100);

    auto label = cocos2d::Label::createWithTTF(question, "fonts/Marker Felt.ttf", 48);
    label->setTextColor(cocos2d::Color4B::BLACK);
    label->setPosition(_currentChoiceBox->getContentSize().width / 2, _currentChoiceBox->getContentSize().height / 2);
    _currentChoiceBox->addChild(label, 1);
    label->setLocalZOrder(101);

    float buttonY = 50;
    for (size_t i = 0; i < choices.size(); ++i)
    {
        auto button = cocos2d::ui::Button::create("button1.png", "button2.png");
        button->setTitleText(choices[i].first);
        button->setTitleFontName("fonts/Marker Felt.ttf");
        button->setTitleColor(cocos2d::Color3B::BLACK);
        button->setTitleFontSize(24);
        button->setPosition(cocos2d::Vec2(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 2, buttonY + i * 150 -200)));
        _currentChoiceBox->addChild(button);

        button->addClickEventListener([=](cocos2d::Ref* sender) {
            if (choices[i].second) {
                choices[i].second();  // 执行选择后的回调
            }
            // 在回调后再移除对话框
            _currentChoiceBox->removeFromParent();
            _currentChoiceBox = nullptr;
            });
    }
}
// NPC 回答关于城镇的情况
void BossScene::displayTownInfo(cocos2d::Sprite* npc)
{
    displayChoice2(npc, "This is a peaceful town. You can find a shop, a tavern, and a blacksmith.", {
        {"I see, tell me more!", [this, npc]() { {
                // 延时显示下一个对话框，避免遮挡
                this->scheduleOnce([=](float) {
                    displayTownDetails(npc);
                }, 0.1f, "handleChatNPC");
            } }},
        {"That's enough, thanks!", [this, npc]() { {
                // 延时显示下一个对话框，避免遮挡
                this->scheduleOnce([=](float) {
                    displayGoodbye(npc);
                }, 0.1f, "handleChatNPC");
            } }}
        });
}

// NPC 详细介绍城镇
void BossScene::displayTownDetails(cocos2d::Sprite* npc)
{
    displayDialogue(npc, "The shop sells potions, the tavern offers drinks and rumors, and the blacksmith can upgrade your gear.");
}

// NPC 给出任务信息
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
            // 设置任务状态为已分配
            npcData.ppp->state = 0;
            // 跳转到 NPC 配置的目标场景
            CCLOG("message", npcData.targetScene);
            rawPlayer1->removeFromParent();
            GlobalManager::getInstance().setLastMap("smallmap/castle.tmx");
            const auto& taskListbat = GlobalManager::getInstance().getTasks();
            taskListbat[0]->id = 0;
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, BattleScene::create()));
            npcData.ppp->state = 1;

        }},
        {"NO", nullptr}
        });
}
// NPC 详细任务信息
void BossScene::displayQuestDetails(cocos2d::Sprite* npc)
{
    displayDialogue(npc, "The herbs grow near the forest. Please bring them back to me once you've collected them.");
}

// NPC 说“再见”
void BossScene::displayGoodbye(cocos2d::Sprite* npc)
{
    displayDialogue(npc, "Goodbye, and good luck on your adventures!");
}



void BossScene::displayDialogue(Sprite* npc, const std::string& text)
{
    // 如果存在当前对话框，移除它
    if (_currentDialogueBox) {
        _currentDialogueBox->removeFromParent();
        _currentDialogueBox = nullptr;
    }

    // 创建对话框
    auto dialogueBox = Sprite::create("box3.png");
    if (!dialogueBox) {
        CCLOG("Failed to create dialogue box!");
        return;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();												// 获取可见区域的大小
    dialogueBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(dialogueBox);

    // 创建文本标签
    auto label = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 24);
    label->setTextColor(Color4B::BLACK);
    label->setPosition(dialogueBox->getContentSize() / 2);
    dialogueBox->addChild(label);

    // 设置当前对话框
    _currentDialogueBox = dialogueBox;

    // 自动消失对话框
    this->scheduleOnce([=](float) {
        dialogueBox->removeFromParent();
        _currentDialogueBox = nullptr;
        }, 3.0f, "closeDialogue");
}