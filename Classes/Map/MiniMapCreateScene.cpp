#include "MiniMap.h"
#include "cocos2d.h"
#include "TaskMenu.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"
#include <vector>
#include <utility>  // std::pair
#include "SmallTask/QuizGame.h"
#include "BattleScene.h"
#include "Sets/manager.h"
#include "Map/BackgroundManager.h"
#include "Map/SettingScene.h"
#include "Backpack.h"
#include "BackpackLayer.h"
#include "AudioManager.h"
#include "SoilWaterGoldFireWood.h"
#include "GoldWoodSoilWater.h"
#include "GoldWoodSoil.h"
#include "GoldWood.h"
#include <Overmap.h>
cocos2d::Vec2 tilePos;
cocos2d::Size tileSize;
cocos2d::Vec2 playerPos;
std::string mapfile;
std::string files[2] = { "monster1","monster2" };
cocos2d::Label* _playerHealthLabel;
std::shared_ptr<Player> player = GlobalManager::getInstance().getPlayer();

cocos2d::Scene* MiniMap::createWithMap(const std::string& mapFile, bool fly)
{
	CCLOG("MiniMap::createWithMap - Start"); 
	MiniMap* scene = new(std::nothrow) MiniMap(mapFile,fly);
	if (scene && scene->initWithMap(mapFile)) {
		scene->autorelease();
		scene->isFly = fly;
		scene->mapName = mapFile;

		CCLOG("MiniMap::createWithMap - Map file: %s, Fly: %d", mapFile.c_str(), fly);

																									// 在初始化完成后创建任务菜单
		scene->createTaskMenu();																	// 这里调用任务菜单的创建方法
		CCLOG("MiniMap::createWithMap - Task menu created");

																									// 创建并添加大地图按钮
		auto bigMapButton = cocos2d::MenuItemImage::create(
			"CloseNormal.png",																		// 按钮的正常状态图像
			"CloseSelected.png",																	// 按钮的选中状态图像
			[=](Ref* sender) {
				const auto& taskListmap = GlobalManager::getInstance().getTasks();
				
				if (taskListmap[5]->state >= 1)
				{
					auto bigMapScene = Setting6::createScene();
					/*
					if (bigMapScene) {
						this->addChild(bigMapScene);
						CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
					}
					else {
						CCLOG("MiniMap::createBigMap - Failed to create big map scene");
					}
					*/
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);
				}
				else if (taskListmap[4]->state >= 1)
				{
					auto bigMapScene = Setting5::createScene();
					/*
					if (bigMapScene) {
						this->addChild(bigMapScene);
						CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
					}
					else {
						CCLOG("MiniMap::createBigMap - Failed to create big map scene");
					}
					*/
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);
				}
				else if (taskListmap[3]->state >= 1)
				{
					auto bigMapScene = Setting4::createScene();
					/*
					if (bigMapScene) {
						this->addChild(bigMapScene);
						CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
					}
					else {
						CCLOG("MiniMap::createBigMap - Failed to create big map scene");
					}
					*/
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);
				}
				else if (taskListmap[2]->state >= 1)
				{
					auto bigMapScene = Setting3::createScene();
					/*
					if (bigMapScene) {
						this->addChild(bigMapScene);
						CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
					}
					else {
						CCLOG("MiniMap::createBigMap - Failed to create big map scene");
					}
					*/
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);
				}
				else if (taskListmap[1]->state >=1)
				{
					auto bigMapScene = Setting2::createScene();
					/*if (bigMapScene) {
						this->addChild(bigMapScene);
						CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
					}
					else {
						CCLOG("MiniMap::createBigMap - Failed to create big map scene");
					}
					*/
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);
				}// 切换到大地图场景
				else
				{
					auto bigMapScene = Setting::createScene();
					/*if (bigMapScene) {
						this->addChild(bigMapScene);
						CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
					}
					else {
						CCLOG("MiniMap::createBigMap - Failed to create big map scene");
					}
					*/
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);
				}// 切换到大地图场景

				//cocos2d::Director::getInstance()->replaceScene(bigMapScene);
			}
		);

		auto switchMap = cocos2d::Menu::create(bigMapButton, nullptr);
		switchMap->setPosition(cocos2d::Director::getInstance()->getVisibleSize().width / 2 -950, 
			cocos2d::Director::getInstance()->getVisibleSize().height / 2+450);
		scene->addChild(switchMap);

		AudioManager::getInstance().playIntroMusic();

		CCLOG("MiniMap::createWithMap - Big map button added to menu");
		
		return scene;
	}

	CCLOG("MiniMap::createWithMap - Failed to create scene");
	CC_SAFE_DELETE(scene);
	return nullptr;
}

void MiniMap::createTaskMenu()
{
	CCLOG("MiniMap::createTaskMenu - Start");
	auto taskMenu = TaskMenu::create();
	this->addChild(taskMenu, 1);
	CCLOG("MiniMap::createTaskMenu - Task menu added");
}

void MiniMap::createBigMap()
{
	CCLOG("MiniMap::createBigMap - Start");
	// 直接调用Setting::createScene()来创建大地图场景
	const auto& taskListmap = GlobalManager::getInstance().getTasks();
	//taskListmap[4]->state = 0;
	if (taskListmap[4]->state == 1)
	{
		auto bigMapScene = Setting5::createScene();
		if (bigMapScene) {
			this->addChild(bigMapScene);
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");
		}
	}
	 else if (taskListmap[4]->state == 1)
	{
		auto bigMapScene = Setting5::createScene();
		if (bigMapScene) {
			this->addChild(bigMapScene);
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");
		}
	}
	else if (taskListmap[3]->state == 1)
	{
		auto bigMapScene = Setting4::createScene();
		if (bigMapScene) {
			this->addChild(bigMapScene);
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");
		}
	}
	else if (taskListmap[2]->state == 1)
	{
		auto bigMapScene = Setting3::createScene();
		if (bigMapScene) {
			this->addChild(bigMapScene);
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");
		}
	}
	else if (taskListmap[1]->state == 1)
	{
		auto bigMapScene = Setting2::createScene();
		if (bigMapScene) {
			this->addChild(bigMapScene);
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");
		}
	}
	else 
	{
		auto bigMapScene = Setting::createScene();
		if (bigMapScene) {
			this->addChild(bigMapScene);
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");
		}
	}
	
}

void MiniMap::createBackpack()
{
	CCLOG("MiniMap::createBackpack - Start");

	// 创建一个 BackpackLayer 实例
	BackpackLayer* backpackLayer = BackpackLayer::create();  // 创建实例

	if (backpackLayer) {

		this->getParent()->addChild(backpackLayer);
		CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");
	}
	else {
		CCLOG("MiniMap::createBigMap - Failed to create big map scene");
	}
}

bool MiniMap::initWithMap(const std::string& mapFile)
{

	if (!Scene::init()) {
		return false;
	}
	mapfile = mapFile;
	auto backpackButton = ui::Button::create("backpack.png");                                                // 使用你自己的图标
	backpackButton->setPosition(Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2 + 825,
		cocos2d::Director::getInstance()->getVisibleSize().height / 2 + 150));                               // 按钮位置
	backpackButton->addClickEventListener([this](Ref* sender) {
		this->openBackpack();
		                                                                                                     // 创建一个 BackpackLayer 对象并将其添加到当前场景中
		BackpackLayer* backpackLayer = BackpackLayer::create();                                              // 创建实例
		if (backpackLayer) {
			                                                                                                 // 将背包层添加到当前场景中
			Director::getInstance()->getRunningScene()->addChild(backpackLayer);                             // 将背包层添加到当前场景
		}
		});

	// 将背包按钮添加到场景中
	this->addChild(backpackButton, 1);                                       
	// 获取当前可视区域的大小
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	// 获取当前可视区域原点坐标
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// 获取地图
	tiledMap = cocos2d::TMXTiledMap::create(mapFile);
	if (!tiledMap) {
		CCLOG("noMap");
		return false;
	}

	// 初始化玩家
	auto objectGroup = tiledMap->getObjectGroup("Objects");
	auto ojectGroup = tiledMap->getObjectGroup("TransportPoint");
	auto boxGroup = tiledMap->getObjectGroup("Boxs");
	auto playerObj = objectGroup->getObject("Player");
	auto kingObj = objectGroup->getObject("King");


	float playerX = playerObj["x"].asFloat();
	float playerY = playerObj["y"].asFloat();


	//设置缩放比例
	float scaleX = 3.0f;
	float scaleY = 3.0f;

	// 加载地图
	tiledMap->setScale(scaleX, scaleY);
	// 获取当前瓦片地图大小
	cocos2d::Size mapSize = tiledMap->getMapSize();
	// 获取瓦片地图瓦片大小
	auto tileSize = tiledMap->getTileSize();
	// 计算瓦片缩放后大小
	auto playerSize = tileSize;
	playerSize.width *= scaleX*2;
	playerSize.height *= scaleY*2;

	// 加载主控精灵
	player->initWithFile(player->getFileName());
	// 设置主控精灵大小
	player->setContentSize(playerSize);
	
	// 获取主控精灵需要到达的逻辑坐标
	float bornPointX = 0.0f, bornPointY = 0.0f;

	// 创建对象层
	auto transportPoint = (isFly == true ? tiledMap->getObjectGroup("TransportPoint") : tiledMap->getObjectGroup("Boat"));

	// 获取传送位置的逻辑坐标
	if (transportPoint) {
		auto transportObject = (isFly == true ? transportPoint->getObject("Fly") : transportPoint->getObject("Boat"));
		bornPointX = transportObject["x"].asFloat();
		bornPointY = transportObject["y"].asFloat();
	}

	if (!bornPointX && !bornPointY)
		CCLOG("noBornPoint");

	// 计算主控精灵的世界坐标
	auto bornWorld = tiledMap->convertToWorldSpace(cocos2d::Vec2(bornPointX, bornPointY));

	// 计算视窗中心的世界坐标
	cocos2d::Vec2 centerWorldPosition = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);

	// 获取偏移量
	cocos2d::Vec2 offset = centerWorldPosition - bornWorld + cocos2d::Vec2(0.0f, -tileSize.height * scaleY);

	// 调整偏移量，以防边界出现在视窗内部
	if (offset.x > 0)
		offset.x = 0;
	else if (offset.x + mapSize.width * tileSize.width * scaleX < visibleSize.width)
		offset.x = visibleSize.width - mapSize.width * tileSize.width * scaleX;
	if (offset.y > 0)
		offset.y = 0;
	else if (offset.y + mapSize.height * tileSize.height * scaleY < visibleSize.height)
		offset.y = visibleSize.height - mapSize.height * tileSize.height * scaleY;

	// 调整主控精灵位置
	playerPos = offset + bornWorld - cocos2d::Vec2(0.0f, -tileSize.height * scaleY);

	// 设置主控精灵位置
	player->setPosition(playerPos);

	// 设置地图位置
	tiledMap->setPosition(offset);

	// 把精灵添加到场景
	this->addChild(tiledMap);
	//if (mapName == "smallmap/battlefeild.tmx")
		//this->removeAllChildren();
	// 把地图添加到场景
	this->addChild(player.get(),9);
	npcNode = Node::create();
	this->addChild(npcNode);
	itemNode = Node::create();
	this->addChild(itemNode);

	float kingX = kingObj["x"].asFloat();
	float kingY = kingObj["y"].asFloat();
	auto king = cocos2d::Sprite::create("king.png");
	king->setPosition(kingX, kingY);
	npcNode->addChild(king, 9);
	king->setContentSize(playerSize);

	const auto& taskList = GlobalManager::getInstance().getTasks();
	// 初始化 NPC 并根据类型分类
	auto npcGroup = objectGroup->getObjects();

	// 获取可交互金矿对象层
	auto objectGroup1 = tiledMap->getObjectGroup("GoldOre");
	if (objectGroup1 == nullptr) {
		CCLOG("Error: Object group 'GoldOre' not found!");
	}
	auto goldoreLayer = objectGroup1->getObjects();
	if (goldoreLayer.empty()) {
		CCLOG("Error: No objects found in 'GoldOre' object group!");
	}

	for (const auto& object : goldoreLayer)
	{
		cocos2d::ValueMap goldoreProperties = object.asValueMap();

		// 检查属性是否存在
		if (goldoreProperties.count("id") == 0 || goldoreProperties.count("x") == 0 || goldoreProperties.count("y") == 0) {
			CCLOG("Error: Missing required properties for GoldOre object!");
			// 跳过这个对象
			continue;  
		}

		auto goldoreID = goldoreProperties["id"].asInt();
		auto x = goldoreProperties["x"].asFloat();
		auto y = goldoreProperties["y"].asFloat();

		CCLOG("GoldOre Object ID: %d at Position: (%f, %f)", goldoreID, x, y);
		
		auto goldore = cocos2d::Sprite::create("smallmap/GoldOre.png");
		// 存储碰撞对象的数据，准备交互使用
		goldoreItems.push_back({ goldore,3, goldoreID, Vec2(x, y) });

		cocos2d::Vec2 itemPos = tiledMap->convertToWorldSpace(cocos2d::Vec2(x, y));
		goldore->setPosition(itemPos);

		// 确保 itemNode 已经初始化
		if (itemNode) {  
			itemNode->addChild(goldore);
		}
		else {
			CCLOG("Error: itemNode is not initialized!");
		}
		this->scheduleUpdate();
	}

	// 获取可交互苹果对象层
	auto appleGroup1 = tiledMap->getObjectGroup("Apple");
	if (appleGroup1 == nullptr) {
		CCLOG("Error: Object group 'GoldOre' not found!");
	}
	auto appleLayer = appleGroup1->getObjects();
	if (appleLayer.empty()) {
		CCLOG("Error: No objects found in 'GoldOre' object group!");
	}

	for (const auto& object : appleLayer)
	{
		cocos2d::ValueMap appleProperties = object.asValueMap();

		// 检查属性是否存在
		if (appleProperties.count("id") == 0 || appleProperties.count("x") == 0 || appleProperties.count("y") == 0) {
			CCLOG("Error: Missing required properties for GoldOre object!");
			// 跳过这个对象
			continue;
		}

		auto appleID = appleProperties["id"].asInt();
		auto x = appleProperties["x"].asFloat();
		auto y = appleProperties["y"].asFloat();

		CCLOG("GoldOre Object ID: %d at Position: (%f, %f)", appleID, x, y);

		auto apple = cocos2d::Sprite::create("Maze/apple.png");
		// 存储碰撞对象的数据，准备交互使用
		appleItems.push_back({ apple,7, appleID, Vec2(x, y) });

		cocos2d::Vec2 itemPos = tiledMap->convertToWorldSpace(cocos2d::Vec2(x, y));
		apple->setPosition(itemPos);

		// 确保 itemNode 已经初始化
		if (itemNode) {
			itemNode->addChild(apple);
		}
		else {
			CCLOG("Error: itemNode is not initialized!");
		}
		this->scheduleUpdate();
	}

	int i = 0;

	for (auto& npcObj : npcGroup)
	{
		cocos2d::ValueMap npcData = npcObj.asValueMap();
		if (!npcData.empty()) {
			auto task = taskList[i];

			int indexnpc = 0;
			int indexmon = 0;
			std::string npcFunction = npcData["npcFunction"].asString();
			std::string targetScene = npcData["targetScene"].asString();
			std::string type = npcData["type"].asString();
			indexnpc = npcData["index"].asInt();
			if (type == "shopkeeper") {
				int indexp = npcData["indexp"].asInt();
				auto npc = cocos2d::Sprite::create(std::to_string(indexp)+"NPC.png");
				cocos2d::Vec2 npcPos = tiledMap->convertToWorldSpace(cocos2d::Vec2(npcData["x"].asFloat(), npcData["y"].asFloat()));
				npc->setPosition(npcPos);
				npc->setContentSize(playerSize);
				npcNode->addChild(npc);
				_npcList.push_back({ npc, npcFunction, indexnpc,taskList[indexnpc],indexnpc,targetScene });
			}
			if (type == "NPC") {
				auto npc = cocos2d::Sprite::create("4NPC.png");
				cocos2d::Vec2 npcPos = tiledMap->convertToWorldSpace(cocos2d::Vec2(npcData["x"].asFloat(), npcData["y"].asFloat()));
				npc->setPosition(npcPos);
				npc->setContentSize(playerSize);
				npcNode->addChild(npc);
				// 对话型NPC
				if (npcFunction == "chat")
					_npcList.push_back({ npc, npcFunction, indexnpc,taskList[indexnpc],indexnpc,targetScene });
				if (npcFunction == "quest")
					_npcList.push_back({ npc, npcFunction, indexnpc,taskList[indexnpc],indexnpc,targetScene });
				
			}
			else if (type == "box") {
				auto npc = cocos2d::Sprite::create("smallmap/boxlqy.png");
				auto pos = tiledMap->convertToWorldSpace(cocos2d::Vec2(npcData["x"].asFloat(), npcData["y"].asFloat()));
				npc->setPosition(pos);
				npc->setContentSize(playerSize);
				npcNode->addChild(npc);
				// 任务型NPC
				_npcList.push_back({ npc, npcFunction,indexnpc, taskList[indexnpc],indexnpc,targetScene });
				
			}
			else if (type == "monster") {
				indexmon = npcData["indexmon"].asInt();
				std::string mapf;
				if (mapFile == "smallmap/whole3.tmx")
					mapf = "whole3";
				else if (mapFile == "smallmap/gold1.tmx")
					mapf = "gold1";
				else if (mapFile == "smallmap/earth.tmx")
					mapf = "earth";	
				else if (mapFile == "smallmap/fire.tmx")
					mapf = "fire";
				else if (mapFile == "smallmap/wood.tmx")
					mapf = "wood";
				auto npc = cocos2d::Sprite::create(mapf + "monster" + std::to_string(indexmon+1)+".png");
				npc->setContentSize(playerSize);
				auto pos = tiledMap->convertToWorldSpace(cocos2d::Vec2(npcData["x"].asFloat(), npcData["y"].asFloat()));
				npc->setPosition(pos);
				
				npcNode->addChild(npc);
				
				_npcList.push_back({ npc, npcFunction, indexmon,taskList[indexnpc],indexnpc,targetScene });
				
			}
		}
		this->scheduleUpdate();
	}

	// 设置键盘事件监听器
	StartListening();

	return true;
}

// 设置键盘事件监听器
void MiniMap::StartListening()
{
	// 确保没有重复添加监听器
	if (!keyboardListener) { 
		keyboardListener = cocos2d::EventListenerKeyboard::create();                        		// 创建并保存键盘事件监听器
		keyboardListener->onKeyPressed = CC_CALLBACK_2(MiniMap::OnKeyPressed, this);	        	// 设置键盘按下事件的回调函数
		keyboardListener->onKeyReleased = CC_CALLBACK_2(MiniMap::OnKeyReleased, this);		        // 设置键盘释放事件的回调函数
		_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);		    // 添加到事件调度器中
	}
}

// 按键按下的回调函数
void MiniMap::OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode) {
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		GlobalManager::getInstance().getPlayer()->isMoving = true;
		UpdatePlayerPosition(keyCode);
		break;
	default:
		break;
	}
}

// 更新逻辑
bool MiniMap::IsColliding(cocos2d::Vec2 position)
{
	// 获取主控精灵当前世界坐标
	auto playerPos = player->getPosition();
	auto x = position.x, y = position.y;

	// 获取瓦片地图的瓦片大小
	auto tileSize = tiledMap->getTileSize();
	
	// 现在是npc坐标点为中心的四个瓦片范围，如果需要缩小，请自行/2
	if (playerPos.x >= x - tileSize.width && playerPos.x <= x + tileSize.width && playerPos.y >= y - tileSize.height && playerPos.y <= y + tileSize.height) {
		CCLOG("Collide npc");
		return true;
	}
	return false;
}

void MiniMap::update(float delta)
{
	//createTaskMenu();

	for (auto& npcData : _npcList)
	{
		auto npc = npcData.npcSprite;

		if (npcNode) {
			bool iscod = IsColliding(npc->getPosition() + npcNode->getPosition());

			if (iscod && !_currentDialogueBox && !_currentChoiceBox && !npc->getUserData()) {
				CCLOG("WE ARE NPC");
				// 标记已交互
				npc->setUserData((void*)1); 
				if (npcData.npcFunction == "chat")
				{
					displayChoice1(npc, "Can you talk with me?", {
						{"Yes", [this, npc]() { {
								// 延时显示下一个对话框，避免遮挡
								this->scheduleOnce([=](float) {
									handleChatNPC(npc);
								}, 0.1f, "handleChatNPC");
							} }},
						{"No", nullptr}
						});
				}
				else if (npcData.npcFunction == "quest")
				{
					CCLOG("KKKKKKKKKKKKK");
					// 任务型NPC
					switch (npcData.ppp->state) {
						case -1:
							CCLOG("Task state before assignment: %d", npcData.ppp->state);
							// 显示任务选择弹窗
							displayTaskOptions(npcData); 
							break;
						case 0:
							// 打印任务状态
							CCLOG("Task state before assignment: %d", npcData.ppp->state); 
							displayDialogue(npc, "YOU've DONE" + npcData.ppp->getTaskName());
							break;
						case 1:
							// 显示奖励领取弹窗
							displayRewardOptions(npcData); 
							break;
						case 2:
							displayDialogue(npc, "你已经完成了我的任务，感谢你的帮助！");
							break;
					}
				}
				else if (npcData.npcFunction == "questpro") {
					// 任务型NPC
					switch (npcData.ppp->state) {
						case -1:
							// 显示任务选择弹窗
							if (npcData.targetScene == "BattleScene") {
								if (mapfile == "smallmap/whole3.tmx") {
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsWater();
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);
								}
								if (mapfile == "smallmap/gold1.tmx") {
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsGold();
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);
								}
								if (mapfile == "smallmap/earth.tmx") {
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsEarth();
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);
								}
								if (mapfile == "smallmap/fire.tmx") {
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsFire();
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);
								}
								if (mapfile == "smallmap/wood.tmx") {
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsWood();
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);
								}
							}
							displayTaskPro(npcData); 
							break;
						case 0:
							// 打印任务状态
							CCLOG("Task state before assignment: %d", npcData.ppp->state); 
							displayDialogue(npc, "YOU've DONE");
							break;
						case 1:
							// 显示奖励领取弹窗
							displayRewardOptions(npcData); 
							break;
						case 2:
							displayDialogue(npc, "thank you");
							break;
					}
				}
			}
			// 如果玩家与 NPC 没有碰撞并且之前已经交互过，则重置交互状态
			else if (!iscod && npc->getUserData() != nullptr)
			{
				// 重置交互状态，允许再次触发
				npc->setUserData(nullptr);
			}
		}
	}

	// 遍历物品，检查是否点击到物品
	for (auto it = goldoreItems.begin(); it != goldoreItems.end(); ++it)
	{
		auto item = it->itemSprite;

		// 打印物品和玩家位置，检查碰撞范围
		CCLOG("Item position: (%f, %f)", item->getPosition().x, item->getPosition().y);
		CCLOG("Player position: (%f, %f)", player->getPosition().x, player->getPosition().y);

		bool iscod = IsColliding(item->getPosition() + itemNode->getPosition());
		if (iscod)
		{
			checkPickUpItems();
			// 假设一次点击只能拾取一个物品
			break; 
		}
	}

	// 遍历物品，检查是否点击到物品
	for (auto it = appleItems.begin(); it != appleItems.end(); ++it)
	{
		auto item = it->itemSprite;

		// 打印物品和玩家位置，检查碰撞范围
		CCLOG("Item position: (%f, %f)", item->getPosition().x, item->getPosition().y);
		CCLOG("Player position: (%f, %f)", player->getPosition().x, player->getPosition().y);

		bool iscod = IsColliding(item->getPosition() + itemNode->getPosition());
		if (iscod)
		{
			checkPickUpItems();
			// 假设一次点击只能拾取一个物品
			break;
		}
	}
}

// 按键释放的回调函数
void MiniMap::OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	GlobalManager::getInstance().getPlayer()->isMoving = false;
}

void MiniMap::displayChoice1(cocos2d::Sprite* npc, const std::string& question,
	const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{ 
	if (_currentChoiceBox) {																					           		  // 如果存在当前对话框，移除它
		_currentChoiceBox->removeFromParent();
		_currentChoiceBox = nullptr;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_currentChoiceBox = cocos2d::Sprite::create("smallmap/box.png");
	//_currentChoiceBox->setPosition(npc->getPosition() + cocos2d::Vec2(0, 80)); 
	_currentChoiceBox->setPosition(Vec2(visibleSize.width / 2,  visibleSize.height / 2));
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
		else if(i==1){
			button = cocos2d::ui::Button::create("No1.png", "No2.png");
		}
		//button->setTitleText(choices[i].first);
		//button->setTitleFontName("fonts/Marker Felt.ttf");
		//button->setTitleFontSize(24);
		button->setPosition(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 4+ i * 300+30, _currentChoiceBox->getContentSize().height/4));
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

void MiniMap::handleChatNPC(cocos2d::Sprite* npc)
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

void MiniMap::displayChoice2(cocos2d::Sprite* npc, const std::string& question,
	const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{
	// 确保旧对话框被清除
	if (_currentChoiceBox) {
		_currentChoiceBox->removeFromParent();
		_currentChoiceBox = nullptr;
	}

	_currentChoiceBox = cocos2d::Sprite::create("smallmap/box3.png");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_currentChoiceBox->setPosition(Vec2(visibleSize.width / 2, 5*visibleSize.height / 6));
	this->addChild(_currentChoiceBox, 1);
	_currentChoiceBox->setLocalZOrder(100);

	auto label = cocos2d::Label::createWithTTF(question, "fonts/Marker Felt.ttf", 48);
	label->setTextColor(cocos2d::Color4B::BLACK);
	label->setPosition(_currentChoiceBox->getContentSize().width / 2, _currentChoiceBox->getContentSize().height / 2 - 30);
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
		button->setPosition(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 2, buttonY + i * 150 -400));
		_currentChoiceBox->addChild(button);

		button->addClickEventListener([=](cocos2d::Ref* sender) {
			// 执行选择后的回调
			if (choices[i].second) {
				choices[i].second(); 
			}
			// 在回调后再移除对话框
			_currentChoiceBox->removeFromParent();
			_currentChoiceBox = nullptr;
			});
	}
}
// NPC 回答关于城镇的情况
void MiniMap::displayTownInfo(cocos2d::Sprite* npc)
{
	displayChoice2(npc, "This is a peaceful town. You can find a shop,\n a tavern, and a blacksmith.", {
		{"I see, tell me more!", [this, npc]() { {
				// 延时显示下一个对话框，避免遮挡
				this->scheduleOnce([=](float) {
					displayTownDetails(npc);
				}, 0.1f, "handleChatNPC");
			} }},
		{"That's enough, thanks!", [this, npc]() { displayGoodbye(npc); }}
	});
}

// NPC 详细介绍城镇
void MiniMap::displayTownDetails(cocos2d::Sprite* npc)
{
	displayDialogue(npc, "The shop sells potions, the tavern offers drinks and rumors, and the blacksmith can upgrade your gear.");
}

// NPC 给出任务信息
void MiniMap::displayQuestInfo(cocos2d::Sprite* npc)
{
	displayChoice2(npc, "I have a quest for you: Collect 10 herbs.", {

		{"Maybe later", [this, npc]() { displayGoodbye(npc); }},
		{"Tell me more", [this, npc]() { displayQuestDetails(npc); }}
	});
}

// NPC 详细任务信息
void MiniMap::displayQuestDetails(cocos2d::Sprite* npc)
{
	displayDialogue(npc, "The herbs grow near the forest. \nPlease bring them back to me once you've collected them.");
}

// NPC 说“再见”
void MiniMap::displayGoodbye(cocos2d::Sprite* npc)
{
	displayDialogue(npc, "Goodbye, and good luck on your adventures!");
}

void MiniMap::displayDialogue(Sprite* npc, const std::string& text)
{
	// 如果存在当前对话框，移除它
	if (_currentDialogueBox) {
		_currentDialogueBox->removeFromParent();
		_currentDialogueBox = nullptr;
	}

	// 创建对话框
	auto dialogueBox = Sprite::create("smallmap/box3.png");
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

void MiniMap::displayTaskOptions(NPCData& npcData) {
	displayChoice1(npcData.npcSprite, npcData.ppp->getTaskName(), {
		{"YES", [this, &npcData]() {
			// 设置任务状态为已分配
			npcData.ppp->state = 0; 
			createTaskMenu();
			// 展示对话框
			displayDialogue(npcData.npcSprite, npcData.ppp->getTaskDescription());
		}},
		{"NO", nullptr}
	});
}

void MiniMap::displayTaskPro(NPCData& npcData) {
	displayChoice1(npcData.npcSprite, npcData.ppp->getTaskName(), {
		{"YES", [this, &npcData]() {
			// 设置任务状态为已分配
			npcData.ppp->state = 0; 
			// 跳转到 NPC 配置的目标场景
			CCLOG("message", npcData.targetScene);
			player->removeFromParent();
			GlobalManager::getInstance().setLastMap(mapName);
			const auto& taskListbat = GlobalManager::getInstance().getTasks();
			taskListbat[0]->id= npcData.taskid;
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, getSceneByName(npcData.targetScene)));
			npcData.ppp->state = 1;
		
		}},
		{"NO", nullptr}
	});
}

void MiniMap::displayTaskStatus(NPCData& npcData) {
	displayDialogue(npcData.npcSprite, "TASK");
}

void MiniMap::displayRewardOptions(NPCData& npcData) {
	displayChoice1(npcData.npcSprite, npcData.ppp->getTaskReward(), {
		{"OF COURSE", [this, &npcData]() {
			if (npcData.ppp->state == 1) {
				// 标记任务已领取奖励
				if (npcData.ppp->getTaskName() == "WATER TASK"|| npcData.ppp->getTaskName() == "GOLD TASK"|| npcData.ppp->getTaskName() == "SOIL TASK"|| npcData.ppp->getTaskName() == "FIRE TASK"|| npcData.ppp->getTaskName() == "WOOD TASK") {

					player->Upgrade();
				}
			
				npcData.ppp->state = 2; 
				//displayDialogue(npcData.npcSprite, "congragulations！");
			}
		}},
		{"LATER", nullptr}
	});
}

cocos2d::Scene* MiniMap::getSceneByName(const std::string& sceneName) {
	if (sceneName == "QuizGame")
	{
		return QuizGame::create();                                          // 返回 Task1Scene 场景
	}
	else if (sceneName == "BattleScene")
	{
		return BattleScene::create();                                       // 返回 Task2Scene 场景
	}
	else
		return BattleScene::create();
}

// 清理监听器
void MiniMap::StopListening()
{
	if (keyboardListener) {
		_eventDispatcher->removeEventListener(keyboardListener);
		// 清空指针
		keyboardListener = nullptr; 
	}
}

void MiniMap::openBackpack()
{
	auto _backpack = new Backpack();
	auto _backpack_num = new Backpack();
	const auto& backpack1 = GlobalManager::getInstance().getArmors();
	const auto& backpack2 = GlobalManager::getInstance().getFoods();
	const auto& backpack3 = GlobalManager::getInstance().getMaterials();
	const auto& backpack4 = GlobalManager::getInstance().getWeapons();

	for (auto back1 : backpack1) {
		if (back1->isPicked) {
			_backpack->_items.push_back({ back1->num,back1->name });
		}
	}
	for (auto back2 : backpack2) {
		if (back2->isPicked) {
			_backpack->_items.push_back({ back2->num,back2->name });
		}
	}
	for (auto back3 : backpack3) {
		if (back3->isPicked) {
			_backpack->_items.push_back({ back3->num,back3->name });
		}
	}
	for (auto back4 : backpack4) {
		if (back4->isPicked) {
			_backpack->_items.push_back({ back4->num,back4->name });
		}
	}

	// 创建背包层并设置背包数据
	auto backpackLayer = BackpackLayer::create();
	// 将背包数据传递给背包层
	backpackLayer->setBackpack(_backpack);  

	// 将背包层添加到场景中
	// 高 z-order 确保背包显示在上层
	this->addChild(backpackLayer, 10);  
}

// 检查玩家是否靠近物品并执行拾取操作
void MiniMap::checkPickUpItems()
{
	auto& item_ = GlobalManager::getInstance().getFoods();
	auto& item_1 = GlobalManager::getInstance().getMaterials();

	// 记录进入此函数的日志
	CCLOG("Checking for nearby items...");  

	for (auto it = goldoreItems.begin(); it != goldoreItems.end(); )
	{
		auto& item = *it;
		auto itemSprite = item.itemSprite;

		// 检查玩家是否靠近物品
		bool isNear = IsColliding(itemSprite->getPosition() + itemNode->getPosition());

		if (isNear)
		{
			// 调用拾取交互
			PickUpInteraction(&item);
			item_1[item.index]->num++;
			item_1[item.index]->isPicked = 1;

			// 从物品容器中删除已经拾取的物品
			it = goldoreItems.erase(it);  // 删除当前物品并更新迭代器

			// 从地图中移除物品
			itemSprite->setVisible(false);  // 隐藏物品图像
			CCLOG("Picked up GoldOre Item with ID: %d", item.id);

			// 一次拾取后退出循环
			break;
		}
		else
		{
			++it;  // 如果没有靠近物品，继续检查下一个物品
		}
	}

	for (auto it = appleItems.begin(); it != appleItems.end(); )
	{
		auto& item = *it;
		auto itemSprite = item.itemSprite;

		// 检查玩家是否靠近物品
		bool isNear = IsColliding(itemSprite->getPosition() + itemNode->getPosition());

		if (isNear)
		{
			// 调用拾取交互
			PickUpInteraction(&item);
			item_[item.index]->num++;
			item_[item.index]->isPicked = 1;

			// 从物品容器中删除已经拾取的物品
			it = appleItems.erase(it);  // 删除当前物品并更新迭代器

			// 从地图中移除物品
			itemSprite->setVisible(false);  // 隐藏物品图像
			CCLOG("Picked up GoldOre Item with ID: %d", item.id);

			// 一次拾取后退出循环
			break;
		}
		else
		{
			++it;  // 如果没有靠近物品，继续检查下一个物品
		}
	}
}

void MiniMap::PickUpInteraction(ItemList* item)
{
	// 显示拾取提示
	auto label = Label::createWithTTF("You picked up !", "fonts/arial.ttf", 100);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	label->setColor(Color3B::YELLOW);  // 使用预定义的黄色
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(label);
	label->runAction(Sequence::create(
		FadeOut::create(2.0f),
		RemoveSelf::create(),
		nullptr));
}

void MiniMap::onEnter() {
	Scene::onEnter();  // 必须调用父类的实现
	CCLOG("SimpleSceneA onEnter");
	//设置缩放比例
	float scaleX = 3.0f;
	float scaleY = 3.0f;
	// 获取瓦片地图瓦片大小
	auto tileSize = tiledMap->getTileSize();

	// 计算瓦片缩放后大小
	auto playerSize = tileSize;
	playerSize.width *= scaleX * 2;
	playerSize.height *= scaleY * 2;

	// 加载主控精灵
	player->initWithFile(player->getFileName());
	// 设置主控精灵大小
	player->setContentSize(playerSize);
	player->Sprite::setPosition(playerPos);
	player->setVisible(true);
	player->setLocalZOrder(255);
	// 在这里添加场景恢复时需要执行的代码
	this->resume();
}

void MiniMap::onEnterTransitionDidFinish() {
	Scene::onEnterTransitionDidFinish();  // 必须调用父类的实现
	CCLOG("SimpleSceneA onEnterTransitionDidFinish");
	//设置缩放比例
	float scaleX = 3.0f;
	float scaleY = 3.0f;
	// 获取瓦片地图瓦片大小
	auto tileSize = tiledMap->getTileSize();

	// 计算瓦片缩放后大小
	auto playerSize = tileSize;
	playerSize.width *= scaleX * 2;
	playerSize.height *= scaleY * 2;

	// 更新显示的玩家生命值
	//_playerHealthLabel->setString("Health: ");
	// 更新 Label 位置，使其始终跟随敌人
	//_playerHealthLabel->setPosition(cocos2d::Vec2(player->Sprite::getPosition().x, player->Sprite::getPosition().y + 150));
	// 加载主控精灵
	player->initWithFile(player->getFileName());
	// 设置主控精灵大小
	player->setContentSize(playerSize);
	//player->Sprite::setPosition(playerPos);
	player->setPosition(playerPos);
	player->setVisible(true);
	player->setLocalZOrder(255);
	// 在这里添加场景完全恢复后需要执行的代码
	this->resume();
}

void MiniMap::restorePositionsAfterPop()
{
	auto player = GlobalManager::getInstance().getPlayer();
	player->setPosition(preposition);
	player->Sprite::setPosition(preposition);
}
// 验证精灵位置
void MiniMap::verifySprites() {};