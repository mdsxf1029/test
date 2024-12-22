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
	CCLOG("MiniMap::createWithMap - Start");														 // 输出信息
	MiniMap* scene = new(std::nothrow) MiniMap(mapFile, fly);										 // 创建小地图场景
	if (scene && scene->initWithMap(mapFile)) {
		scene->autorelease();																		// 释放场景
		scene->isFly = fly;																			// 设置是否飞行
		scene->mapName = mapFile;																	// 设置地图名称

		CCLOG("MiniMap::createWithMap - Map file: %s, Fly: %d", mapFile.c_str(), fly);				// 输出地图文件名和是否飞行

		/*在初始化完成后创建任务菜单*/
		scene->createTaskMenu();																	// 这里调用任务菜单的创建方法
		CCLOG("MiniMap::createWithMap - Task menu created");										// 输出信息

		/* 创建并添加大地图按钮*/
		auto bigMapButton = cocos2d::MenuItemImage::create(
			"CloseNormal.png",																		// 按钮的正常状态图像
			"CloseSelected.png",																	// 按钮的选中状态图像
			[=](Ref* sender) {
				const auto& taskListmap = GlobalManager::getInstance().getTasks();					// 获取任务列表
				if (taskListmap[5]->state >= 1)														// 如果任务5已完成
				{
					auto bigMapScene = Setting6::createScene();										// 创建大地图场景
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);					// 加载大地图场景
				}
				else if (taskListmap[4]->state >= 1)												//如果任务4已完成
				{
					auto bigMapScene = Setting5::createScene();										// 创建大地图场景
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);					// 加载大地图场景
				}
				else if (taskListmap[3]->state >= 1)											    //如果任务3已完成
				{
					auto bigMapScene = Setting4::createScene();										// 创建大地图场景
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);					// 加载大地图场景
				}
				else if (taskListmap[2]->state >= 1)	                                            // 如果任务2已完成
				{
					auto bigMapScene = Setting3::createScene();										// 创建大地图场景
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);					// 加载大地图场景
				}
				else if (taskListmap[1]->state >= 1)	                                            // 如果任务1已完成
				{
					auto bigMapScene = Setting2::createScene();										// 创建大地图场景
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);					// 加载大地图场景
				}
				else                                                                                //其他
				{
					auto bigMapScene = Setting::createScene();										// 创建大地图场景
					cocos2d::Director::getInstance()->replaceScene(bigMapScene);					// 加载大地图场景
				}
			}
		);

		auto switchMap = cocos2d::Menu::create(bigMapButton, nullptr);								// 创建菜单
		switchMap->setPosition(cocos2d::Director::getInstance()->getVisibleSize().width / 2 - 950,
			cocos2d::Director::getInstance()->getVisibleSize().height / 2 + 450);					// 设置菜单位置
		scene->addChild(switchMap);																	// 将菜单添加到场景
		AudioManager::getInstance().playIntroMusic();												// 播放背景音乐
		CCLOG("MiniMap::createWithMap - Big map button added to menu");								// 输出信息
		return scene;
	}

	CCLOG("MiniMap::createWithMap - Failed to create scene");
	CC_SAFE_DELETE(scene);
	return nullptr;
}

/*创建任务菜单*/
void MiniMap::createTaskMenu()
{
	CCLOG("MiniMap::createTaskMenu - Start");														// 输出信息
	auto taskMenu = TaskMenu::create();																// 创建任务菜单
	this->addChild(taskMenu, 1);																	// 将任务菜单添加到场景
	CCLOG("MiniMap::createTaskMenu - Task menu added");												// 输出信息
}
/*创建大地图*/
void MiniMap::createBigMap()
{
	CCLOG("MiniMap::createBigMap - Start");															// 输出信息
	const auto& taskListmap = GlobalManager::getInstance().getTasks();								// 获取任务列表

	if (taskListmap[4]->state == 1)																	//如果任务4完成
	{
		auto bigMapScene = Setting5::createScene();													// 创建大地图场景
		if (bigMapScene) {																			// 如果大地图场景存在
			this->addChild(bigMapScene);															// 将大地图场景添加到当前场景
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");						// 输出信息
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");						// 输出错误信息
		}
	}
	else if (taskListmap[4]->state == 1)															// 如果任务4完成
	{
		auto bigMapScene = Setting5::createScene();													// 创建大地图场景
		if (bigMapScene) {																			// 如果大地图场景存在
			this->addChild(bigMapScene);															// 将大地图场景添加到当前场景
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");						// 输出信息
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");						// 输出错误信息
		}
	}
	else if (taskListmap[3]->state == 1)															// 如果任务3完成
	{
		auto bigMapScene = Setting4::createScene();													// 创建大地图场景
		if (bigMapScene) {																			// 如果大地图场景存在
			this->addChild(bigMapScene);															// 将大地图场景添加到当前场景
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");						// 输出信息
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");						// 输出错误信息
		}
	}
	else if (taskListmap[2]->state == 1)															// 如果任务2完成
	{
		auto bigMapScene = Setting3::createScene();													// 创建大地图场景
		if (bigMapScene) {																			// 如果大地图场景存在
			this->addChild(bigMapScene);															// 将大地图场景添加到当前场景
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");						// 输出信息
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");						// 输出错误信息
		}
	}
	else if (taskListmap[1]->state == 1)															// 如果任务1完成
	{
		auto bigMapScene = Setting2::createScene();													// 创建大地图场景
		if (bigMapScene) {																			// 如果大地图场景存在
			this->addChild(bigMapScene);															// 将大地图场景添加到当前场景
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");						// 输出信息
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");						// 输出错误信息
		}
	}
	else
	{
		auto bigMapScene = Setting::createScene();													// 创建大地图场景
		if (bigMapScene) {																			// 如果大地图场景存在
			this->addChild(bigMapScene);															// 将大地图场景添加到当前场景
			CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");						// 输出信息
		}
		else {
			CCLOG("MiniMap::createBigMap - Failed to create big map scene");						// 输出错误信息
		}
	}

}

void MiniMap::createBackpack()
{
	CCLOG("MiniMap::createBackpack - Start");														// 输出信息
	BackpackLayer* backpackLayer = BackpackLayer::create();                                         // 创建一个 BackpackLayer 实例
	if (backpackLayer) {																			// 如果背包层存在

		this->getParent()->addChild(backpackLayer);													// 将背包层添加到父节点
		CCLOG("MiniMap::createBigMap - Big map scene added to MiniMap");							// 输出信息
	}
	else {
		CCLOG("MiniMap::createBigMap - Failed to create big map scene");							// 输出错误信息
	}
}

bool MiniMap::initWithMap(const std::string& mapFile)														// 初始化地图
{
	if (!Scene::init()) {																					// 如果场景初始化失败
		return false;
	}
	mapfile = mapFile;
	auto backpackButton = ui::Button::create("backpack.png");                                                // 使用你自己的图标
	backpackButton->setPosition(Vec2(cocos2d::Director::getInstance()->getVisibleSize().width / 2 + 825,
		cocos2d::Director::getInstance()->getVisibleSize().height / 2 + 150));                               // 按钮位置
	backpackButton->addClickEventListener([this](Ref* sender) {
		this->openBackpack();
		BackpackLayer* backpackLayer = BackpackLayer::create();                                              // 创建一个 BackpackLayer 对象并将其添加到当前场景中
		if (backpackLayer) {
			// 将背包层添加到当前场景中
			Director::getInstance()->getRunningScene()->addChild(backpackLayer);                             // 将背包层添加到当前场景
		}
		});
	this->addChild(backpackButton, 1);																		// 将背包按钮添加到场景中                                    
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();							// 获取可视区域大小
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();							// 获取可视区域原点

	tiledMap = cocos2d::TMXTiledMap::create(mapFile);														// 创建瓦片地图	
	if (!tiledMap) {
		CCLOG("noMap");
		return false;
	}

	// 初始化玩家
	auto objectGroup = tiledMap->getObjectGroup("Objects");													// 获取对象组
	auto ojectGroup = tiledMap->getObjectGroup("TransportPoint");											// 获取传送点对象组
	auto boxGroup = tiledMap->getObjectGroup("Boxs");														// 获取箱子对象组
	auto playerObj = objectGroup->getObject("Player");														// 获取玩家对象
	auto kingObj = objectGroup->getObject("King");															// 获取国王对象

	float playerX = playerObj["x"].asFloat();																// 获取玩家x坐标
	float playerY = playerObj["y"].asFloat();																// 获取玩家y坐标

	float scaleX = 3.0f;																					// 设置x缩放比例
	float scaleY = 3.0f;																					// 设置y缩放比例
	tiledMap->setScale(scaleX, scaleY);																		// 设置地图缩放
	cocos2d::Size mapSize = tiledMap->getMapSize();															// 获取地图大小
	auto tileSize = tiledMap->getTileSize();																// 获取瓦片大小
	auto playerSize = tileSize;																				// 获取玩家大小
	playerSize.width *= scaleX * 2;																			// 计算玩家宽度
	playerSize.height *= scaleY * 2;																		// 计算玩家高度
	player->initWithFile(player->getFileName());															// 初始化玩家图像
	player->setContentSize(playerSize);																		// 设置玩家大小
	float bornPointX = 0.0f, bornPointY = 0.0f;																// 初始化出生点坐标

	auto transportPoint = (isFly == true ? tiledMap->getObjectGroup("TransportPoint") : tiledMap->getObjectGroup("Boat"));	// 获取传送位置的逻辑坐标

	/* 获取传送位置的逻辑坐标*/
	if (transportPoint) {
		auto transportObject = (isFly == true ? transportPoint->getObject("Fly") : transportPoint->getObject("Boat"));		// 获取传送位置的逻辑坐标
		bornPointX = transportObject["x"].asFloat();																		// 获取传送位置的x坐标
		bornPointY = transportObject["y"].asFloat();																		// 获取传送位置的y坐标
	}
	if (!bornPointX && !bornPointY) 																						// 如果没有传送位置
		CCLOG("noBornPoint");																								// 输出信息

	auto bornWorld = tiledMap->convertToWorldSpace(cocos2d::Vec2(bornPointX, bornPointY));								// 计算主控精灵的世界坐标
	cocos2d::Vec2 centerWorldPosition = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);					// 计算视窗中心的世界坐标
	cocos2d::Vec2 offset = centerWorldPosition - bornWorld + cocos2d::Vec2(0.0f, -tileSize.height * scaleY);			// 计算偏移量

	/*调整偏移量，以防边界出现在视窗内部*/
	if (offset.x > 0)																						// 如果偏移量x大于0
		offset.x = 0;																						// 设置偏移量x为0
	else if (offset.x + mapSize.width * tileSize.width * scaleX < visibleSize.width)						// 如果偏移量x加上地图宽度小于可见宽度
		offset.x = visibleSize.width - mapSize.width * tileSize.width * scaleX;								// 设置偏移量x为可见宽度减去地图宽度
	if (offset.y > 0)																						// 如果偏移量y大于0
		offset.y = 0;																						// 设置偏移量y为0
	else if (offset.y + mapSize.height * tileSize.height * scaleY < visibleSize.height)						// 如果偏移量y加上地图高度小于可见高度
		offset.y = visibleSize.height - mapSize.height * tileSize.height * scaleY;							// 设置偏移量y为可见高度减去地图高度

	playerPos = offset + bornWorld - cocos2d::Vec2(0.0f, -tileSize.height * scaleY);						// 计算主控精灵位置
	player->setPosition(playerPos);																			// 设置主控精灵位置
	tiledMap->setPosition(offset);																			// 设置地图位置
	this->addChild(tiledMap);																				// 添加地图
	this->addChild(player.get(), 9);																		// 添加主控精灵
	npcNode = Node::create();																				// 创建NPC节点
	this->addChild(npcNode);																				// 添加NPC节点
	itemNode = Node::create();																				// 创建物品节点
	this->addChild(itemNode);																				// 添加物品节点

	float kingX = kingObj["x"].asFloat();																	// 获取国王x坐标
	float kingY = kingObj["y"].asFloat();																	// 获取国王y坐标
	auto king = cocos2d::Sprite::create("king.png");														// 创建国王精灵
	king->setPosition(kingX, kingY);																		// 设置国王位置
	npcNode->addChild(king, 9);																				// 添加国王精灵
	king->setContentSize(playerSize);																		// 设置国王大小

	const auto& taskList = GlobalManager::getInstance().getTasks();											// 获取任务列表
	auto npcGroup = objectGroup->getObjects();																// 初始化 NPC 并根据类型分类

	auto objectGroup1 = tiledMap->getObjectGroup("GoldOre");												// 获取金矿对象组
	if (objectGroup1 == nullptr) {																			// 如果对象组为空
		CCLOG("Error: Object group 'GoldOre' not found!");													// 输出错误信息
	}
	auto goldoreLayer = objectGroup1->getObjects();															// 获取金矿对象
	if (goldoreLayer.empty()) {																				// 如果金矿对象为空
		CCLOG("Error: No objects found in 'GoldOre' object group!");										// 输出错误信息
	}

	for (const auto& object : goldoreLayer)																	//遍历金矿
	{
		cocos2d::ValueMap goldoreProperties = object.asValueMap();											// 获取金矿属性
		/*检查属性是否存在*/
		if (goldoreProperties.count("id") == 0 || goldoreProperties.count("x") == 0 || goldoreProperties.count("y") == 0) {
			CCLOG("Error: Missing required properties for GoldOre object!");								//如果不存在	
			continue;																						//跳过这个对象
		}

		auto goldoreID = goldoreProperties["id"].asInt();													// 获取金矿ID
		auto x = goldoreProperties["x"].asFloat();															// 获取x坐标
		auto y = goldoreProperties["y"].asFloat();															// 获取y坐标
		CCLOG("GoldOre Object ID: %d at Position: (%f, %f)", goldoreID, x, y);								// 输出金矿对象ID和位置

		auto goldore = cocos2d::Sprite::create("smallmap/GoldOre.png");										// 创建金矿精灵
		goldoreItems.push_back({ goldore,3, goldoreID, Vec2(x, y) });										// 添加金矿精灵到金矿列表，设置碰撞对象数据，准备交互使用。

		cocos2d::Vec2 itemPos = tiledMap->convertToWorldSpace(cocos2d::Vec2(x, y));							// 计算金矿位置
		goldore->setPosition(itemPos);																		// 设置金矿位置

		if (itemNode) {																						// 如果物品节点存在
			itemNode->addChild(goldore);																	// 添加金矿精灵到物品节点
		}
		else {																								// 如果物品节点不存在
			CCLOG("Error: itemNode is not initialized!");													// 输出错误信息
		}
		this->scheduleUpdate();																				// 调度更新
	}

	/*获取可交互苹果对象层*/ 
	auto appleGroup1 = tiledMap->getObjectGroup("Apple");													// 获取苹果对象组
	if (appleGroup1 == nullptr) {																			// 如果对象组为空
		CCLOG("Error: Object group 'GoldOre' not found!");													// 输出错误信息
	}
	auto appleLayer = appleGroup1->getObjects();															// 获取苹果对象
	if (appleLayer.empty()) {																				// 如果苹果对象为空
		CCLOG("Error: No objects found in 'GoldOre' object group!");										// 输出错误信息
	}

	for (const auto& object : appleLayer)																	//遍历对象层
	{
		cocos2d::ValueMap appleProperties = object.asValueMap();											// 获取苹果属性
		// 检查属性是否存在
		if (appleProperties.count("id") == 0 || appleProperties.count("x") == 0 || appleProperties.count("y") == 0) {
			CCLOG("Error: Missing required properties for GoldOre object!");								// 输出错误信息
			continue;																						// 跳过这个对象
		}

		auto appleID = appleProperties["id"].asInt();														// 获取苹果ID
		auto x = appleProperties["x"].asFloat();															// 获取x坐标
		auto y = appleProperties["y"].asFloat();															// 获取y坐标
			
		CCLOG("GoldOre Object ID: %d at Position: (%f, %f)", appleID, x, y);								// 输出苹果对象ID和位置

		auto apple = cocos2d::Sprite::create("Maze/apple.png");												// 创建苹果精灵
		appleItems.push_back({ apple,7, appleID, Vec2(x, y) });												// 添加苹果精灵到苹果列表，存储碰撞对象数据，准备交互使用。

		cocos2d::Vec2 itemPos = tiledMap->convertToWorldSpace(cocos2d::Vec2(x, y));							// 计算苹果位置
		apple->setPosition(itemPos);																		// 设置苹果位置

		/*确保 itemNode 已经初始化*/ 
		if (itemNode) {																						// 如果物品节点存在
			itemNode->addChild(apple);																		// 添加苹果精灵到物品节点
		}
		else {
			CCLOG("Error: itemNode is not initialized!");													// 输出错误信息
		}
		this->scheduleUpdate();																				// 调度更新
	}

	int i = 0;	

	for (auto& npcObj : npcGroup) 																			// 遍历 NPC
	{
		cocos2d::ValueMap npcData = npcObj.asValueMap();													// 获取npc数据
		if (!npcData.empty()) {																				// 如果npc数据不为空
			auto task = taskList[i];																		// 获取任务

			int indexnpc = 0;																				// 初始化NPC索引
			int indexmon = 0;																				// 初始化怪物索引
			std::string npcFunction = npcData["npcFunction"].asString();									// 获取NPC功能
			std::string targetScene = npcData["targetScene"].asString();									// 获取目标场景
			std::string type = npcData["type"].asString();													
			indexnpc = npcData["index"].asInt();															// 获取NPC索引
			if (type == "shopkeeper") {																		// 如果类型是商店店长
				int indexp = npcData["indexp"].asInt();														// 获取NPC图片索引
				auto npc = cocos2d::Sprite::create(std::to_string(indexp) + "NPC.png");						// 创建NPC精灵
				cocos2d::Vec2 npcPos = tiledMap->convertToWorldSpace(cocos2d::Vec2(npcData["x"].asFloat(), npcData["y"].asFloat()));	// 计算NPC位置
				npc->setPosition(npcPos);																	// 设置NPC位置
				npc->setContentSize(playerSize);															// 设置NPC大小
				npcNode->addChild(npc);																		// 添加NPC到NPC节点
				_npcList.push_back({ npc, npcFunction, indexnpc,taskList[indexnpc],indexnpc,targetScene });	// 添加NPC到NPC列表
			}
			if (type == "NPC") {																			// 如果类型是NPC
				auto npc = cocos2d::Sprite::create("4NPC.png");												// 创建NPC精灵
				cocos2d::Vec2 npcPos = tiledMap->convertToWorldSpace(cocos2d::Vec2(npcData["x"].asFloat(), npcData["y"].asFloat()));	// 计算NPC位置
				npc->setPosition(npcPos);																	// 设置NPC位置
				npc->setContentSize(playerSize);															// 设置NPC大小
				npcNode->addChild(npc);																		// 添加NPC到NPC节点
				/* 对话型NPC*/
				if (npcFunction == "chat")																	// 如果NPC功能是聊天
					_npcList.push_back({ npc, npcFunction, indexnpc,taskList[indexnpc],indexnpc,targetScene });	// 添加NPC到NPC列表
				if (npcFunction == "quest")																	// 如果NPC功能是任务
					_npcList.push_back({ npc, npcFunction, indexnpc,taskList[indexnpc],indexnpc,targetScene });	// 添加NPC到NPC列表
			}
			else if (type == "box") {																		// 如果类型是箱子
				auto npc = cocos2d::Sprite::create("smallmap/boxlqy.png");									// 创建箱子精灵
				auto pos = tiledMap->convertToWorldSpace(cocos2d::Vec2(npcData["x"].asFloat(), npcData["y"].asFloat()));				// 计算箱子位置
				npc->setPosition(pos);																		// 设置箱子位置
				npc->setContentSize(playerSize);															// 设置箱子大小
				npcNode->addChild(npc);																		// 添加箱子到NPC节点
				_npcList.push_back({ npc, npcFunction,indexnpc, taskList[indexnpc],indexnpc,targetScene });	// 添加NPC到NPC列表
			}
			else if (type == "monster") {																	// 如果类型是怪物
				indexmon = npcData["indexmon"].asInt();														// 获取怪物索引
				std::string mapf;																			// 初始化地图文件
				if (mapFile == "smallmap/whole3.tmx")														// 如果地图文件是whole3
					mapf = "whole3";																		// 设置地图文件为whole3
				else if (mapFile == "smallmap/gold1.tmx")													// 如果地图文件是gold1
					mapf = "gold1";																			// 设置地图文件为gold1
				else if (mapFile == "smallmap/earth.tmx")													// 如果地图文件是earth
					mapf = "earth";																			// 设置地图文件为earth
				else if (mapFile == "smallmap/fire.tmx")													// 如果地图文件是fire
					mapf = "fire";																			// 设置地图文件为fire
				else if (mapFile == "smallmap/wood.tmx")													// 如果地图文件是wood
					mapf = "wood";																			// 设置地图文件为wood

				auto npc = cocos2d::Sprite::create(mapf + "monster" + std::to_string(indexmon + 1) + ".png");			// 创建怪物精灵
				npc->setContentSize(playerSize);																		// 设置怪物大小
				auto pos = tiledMap->convertToWorldSpace(cocos2d::Vec2(npcData["x"].asFloat(), npcData["y"].asFloat()));// 计算怪物位置
				npc->setPosition(pos);																					// 设置怪物位置
				npcNode->addChild(npc);																					// 添加怪物到NPC节点
				_npcList.push_back({ npc, npcFunction, indexmon,taskList[indexnpc],indexnpc,targetScene });				// 添加怪物到NPC列表
			}
		}
		this->scheduleUpdate();																				// 调度更新
	}
	StartListening();																						// 设置键盘事件监听器

	return true;

}

// 设置键盘事件监听器
void MiniMap::StartListening()
{
	/*确保没有重复添加监听器*/ 
	if (!keyboardListener) {
		keyboardListener = cocos2d::EventListenerKeyboard::create();                        		// 创建并保存键盘事件监听器
		keyboardListener->onKeyPressed = CC_CALLBACK_2(MiniMap::OnKeyPressed, this);	        	// 设置键盘按下事件的回调函数
		keyboardListener->onKeyReleased = CC_CALLBACK_2(MiniMap::OnKeyReleased, this);		        // 设置键盘释放事件的回调函数
		_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);		    // 添加到事件调度器中
	}
}

/* 按键按下的回调函数*/
void MiniMap::OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode) {																				// 根据按键码执行相应操作
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:											// 如果按下的是上箭头键/
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:										// 如果按下的是下箭头键
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:										// 如果按下的是左箭头键
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:										// 如果按下的是右箭头键
			GlobalManager::getInstance().getPlayer()->isMoving = true;								// 设置玩家正在移动
			UpdatePlayerPosition(keyCode);															// 更新玩家位置
			break;
		default:																					// 默认情况
			break;																					// 退出
	}
}

/*更新逻辑*/ 
bool MiniMap::IsColliding(cocos2d::Vec2 position)
{
	/*获取主控精灵当前世界坐标*/ 
	auto playerPos = player->getPosition();															// 获取玩家位置
	auto x = position.x, y = position.y;															// 初始化x和y坐标
	auto tileSize = tiledMap->getTileSize();														// 获取瓦片大小

	// 现在是npc坐标点为中心的四个瓦片范围，如果需要缩小，请自行/2
	if (playerPos.x >= x - tileSize.width && playerPos.x <= x + tileSize.width && playerPos.y >= y - tileSize.height && playerPos.y <= y + tileSize.height) {
		CCLOG("Collide npc");																		// 输出信息
		return true;
	}
	return false;
}

void MiniMap::update(float delta)
{
	for (auto& npcData : _npcList)																	// 遍历NPC
	{
		auto npc = npcData.npcSprite;																// 获取NPC精灵

		if (npcNode) {																				// 如果NPC节点存在
			bool iscod = IsColliding(npc->getPosition() + npcNode->getPosition());					// 检查是否与NPC碰撞

			if (iscod && !_currentDialogueBox && !_currentChoiceBox && !npc->getUserData()) {		// 如果玩家与NPC碰撞并且没有对话框和选择框
				CCLOG("WE ARE NPC");																// 输出信息
				npc->setUserData((void*)1);															// 设置NPC数据
				if (npcData.npcFunction == "chat")													// 如果NPC功能是聊天
				{
					displayChoice1(npc, "Can you talk with me?", {                                  // 显示对话框
						{"Yes", [this, npc]() { {													// 延时显示下一个对话框，避免遮挡
								this->scheduleOnce([=](float) {
									handleChatNPC(npc);
								}, 0.1f, "handleChatNPC");
							} }},
						{"No", nullptr}
						});
				}
				else if (npcData.npcFunction == "quest")											// 如果NPC功能是任务
				{
					CCLOG("KKKKKKKKKKKKK");
					switch (npcData.ppp->state) {													// 根据任务状态执行相应操作
						case -1:																	// 如果任务状态是未接受
							CCLOG("Task state before assignment: %d", npcData.ppp->state);			// 输出信息
							displayTaskOptions(npcData);											// 显示任务选择弹窗
							break;
						case 0:																		// 如果任务状态是已接受
							CCLOG("Task state before assignment: %d", npcData.ppp->state);			// 输出信息
							displayDialogue(npc, "YOU've DONE" + npcData.ppp->getTaskName());		// 显示对话框
							break;
						case 1:																		// 如果任务状态是已完成
							displayRewardOptions(npcData);											// 显示奖励领取弹窗
							break;
						case 2:																		// 如果任务状态是已领取奖励
							displayDialogue(npc, "你已经完成了我的任务，感谢你的帮助！");			// 显示对话框
							break;
					}
				}
				else if (npcData.npcFunction == "questpro") {
					// 任务型NPC
					switch (npcData.ppp->state) {																// 根据任务状态执行相应操作
						case -1:
							/* 显示任务选择弹窗*/
							if (npcData.targetScene == "BattleScene") {											// 如果目标场景是战斗场景
								if (mapfile == "smallmap/whole3.tmx") {											// 如果地图文件是whole3
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsWater();		// 获取水属性怪物列表
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);			// 设置战斗NPC
								}
								if (mapfile == "smallmap/gold1.tmx") {											// 如果地图文件是gold1
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsGold();		// 获取金属性怪物列表
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);			// 设置战斗NPC
								}
								if (mapfile == "smallmap/earth.tmx") {											// 如果地图文件是earth
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsEarth();		// 获取土属性怪物列表
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);			// 设置战斗NPC
								}
								if (mapfile == "smallmap/fire.tmx") {											// 如果地图文件是fire
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsFire();		// 获取火属性怪物列表
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);			// 设置战斗NPC
								}
								if (mapfile == "smallmap/wood.tmx") {											// 如果地图文件是wood
									const auto& MonList = GlobalManager::getInstance().getEnemyNpcsWood();		// 获取木属性怪物列表
									GlobalManager::getInstance().setBattleNpc(MonList[npcData.index]);			// 设置战斗NPC
								}
							}
							displayTaskPro(npcData);															// 显示任务选择弹窗
							break;
						case 0:																					// 如果任务状态是已接受
							/*打印任务状态*/ 
							CCLOG("Task state before assignment: %d", npcData.ppp->state);						// 输出信息
							displayDialogue(npc, "YOU've DONE");												// 显示对话框
							break;
						case 1:																					// 如果任务状态是已完成
							/*显示奖励领取弹窗*/ 
							displayRewardOptions(npcData);														// 显示奖励领取弹窗
							break;
						case 2:																					// 如果任务状态是已领取奖励
							displayDialogue(npc, "thank you");													// 显示对话框
							break;
					}
				}
			}
			/*如果玩家与 NPC 没有碰撞并且之前已经交互过，则重置交互状态*/ 
			else if (!iscod && npc->getUserData() != nullptr)													// 如果玩家与NPC没有碰撞并且之前已经交互过
			{
				npc->setUserData(nullptr);																		// 重置NPC数据
			}
		}
	}
	/*遍历物品，检查是否点击到物品*/ 
	for (auto it = goldoreItems.begin(); it != goldoreItems.end(); ++it)										// 遍历金矿
	{
		auto item = it->itemSprite;																				// 获取金矿精灵

		/*打印物品和玩家位置，检查碰撞范围*/ 
		CCLOG("Item position: (%f, %f)", item->getPosition().x, item->getPosition().y);							// 输出信息
		CCLOG("Player position: (%f, %f)", player->getPosition().x, player->getPosition().y);					// 输出信息

		bool iscod = IsColliding(item->getPosition() + itemNode->getPosition());								// 检查是否点击到物品
		if (iscod)
		{
			checkPickUpItems();																					// 假设一次点击只能拾取一个物品
			break;
		}
	}

	/*遍历物品，检查是否点击到物品*/ 
	for (auto it = appleItems.begin(); it != appleItems.end(); ++it)	                                        //遍历苹果
	{
		auto item = it->itemSprite;																				// 获取苹果精灵

		/*打印物品和玩家位置，检查碰撞范围*/ 
		CCLOG("Item position: (%f, %f)", item->getPosition().x, item->getPosition().y);							// 输出信息 物品
		CCLOG("Player position: (%f, %f)", player->getPosition().x, player->getPosition().y);					// 输出信息	玩家

		bool iscod = IsColliding(item->getPosition() + itemNode->getPosition());								// 检查是否点击到物品
		if (iscod)
		{
			checkPickUpItems();																					// 假设一次点击只能拾取一个物品
			break;
		}
	}
}

/*按键释放的回调函数*/ 
void MiniMap::OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	GlobalManager::getInstance().getPlayer()->isMoving = false;													// 设置玩家不在移动
}

void MiniMap::displayChoice1(cocos2d::Sprite* npc, const std::string& question,
	const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{
	if (_currentChoiceBox) {																					           		  // 如果存在当前对话框，移除它
		_currentChoiceBox->removeFromParent();																					  // 移除对话框
		_currentChoiceBox = nullptr;																					          // 重置对话框
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();																  // 获取可见大小
	_currentChoiceBox = cocos2d::Sprite::create("smallmap/box.png");															  // 创建对话框
	_currentChoiceBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));										  // 设置对话框位置
	this->addChild(_currentChoiceBox);																							  // 添加对话框
	_currentChoiceBox->setLocalZOrder(100);																        				  // 让对话框处于较高的层级 
	auto label = cocos2d::Label::createWithTTF(question, "fonts/Marker Felt.ttf", 48);											  // 创建标签
	label->setTextColor(cocos2d::Color4B::WHITE);																				  // 设置标签颜色
	label->setPosition(_currentChoiceBox->getContentSize().width / 2, _currentChoiceBox->getContentSize().height / 2 + 100);	  // 设置标签位置
	_currentChoiceBox->addChild(label, 1);																					      // 添加标签到对话框
	label->setLocalZOrder(101);																									  // 让标签处于较高的层级

	float buttonY = 50;																											  // 初始化按钮Y坐标
	for (size_t i = 0; i < choices.size(); ++i)								                                                      // 遍历选择
	{
		cocos2d::ui::Button* button;
		if (i == 0) {
			button = cocos2d::ui::Button::create("Yes1.png", "Yes2.png");														  // 创建按钮yes
		}
		else if (i == 1) {
			button = cocos2d::ui::Button::create("No1.png", "No2.png");														      // 创建按钮no
		}
		button->setPosition(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 4 + i * 300 + 30, _currentChoiceBox->getContentSize().height / 4));
		_currentChoiceBox->addChild(button);																					  // 添加按钮到对话框

		button->addClickEventListener([=](cocos2d::Ref* sender) {
			if (choices[i].second) {
				choices[i].second();																				// 执行选择后的回调
			}
			/*重要：这里移除对话框后再添加新的对话框*/ 
			if (_currentChoiceBox) {																				// 如果存在当前对话框
				_currentChoiceBox->removeFromParent();																// 移除对话框
				_currentChoiceBox = nullptr;																		// 重置对话框
			}

			});
	}
}

void MiniMap::handleChatNPC(cocos2d::Sprite* npc)
{
	/*显示新的对话框*/ 
	displayChoice2(npc, "Hello! How can I help you today?", {
		{"Tell me about the town", [this, npc]() { {																// 延时显示下一个对话框，避免遮挡
																													// 延时显示下一个对话框，避免遮挡
				this->scheduleOnce([=](float) {																		// 延时显示下一个对话框
					displayTownInfo(npc);																			// 显示城镇信息
				}, 0.1f, "handleChatNPC");																			// 延时0.1秒
			} }},
		{"I need a quest", [this, npc]() { {
																													// 延时显示下一个对话框，避免遮挡
				this->scheduleOnce([=](float) {																		// 延时显示下一个对话框
					displayQuestInfo(npc);																			// 显示任务信息
				}, 0.1f, "handleChatNPC");																			// 延时0.1秒
			} }},
		{"Nothing, just passing by", [this, npc]() { {
																													// 延时显示下一个对话框，避免遮挡
				this->scheduleOnce([=](float) {																		// 延时显示下一个对话框
					displayGoodbye(npc);																			// 显示再见
				}, 0.1f, "handleChatNPC");																			// 延时0.1秒	
			} }},
		});
}

void MiniMap::displayChoice2(cocos2d::Sprite* npc, const std::string& question,
	const std::vector<std::pair<std::string, std::function<void()>>>& choices)
{
	/*确保旧对话框被清除*/ 
	if (_currentChoiceBox) {																						// 如果存在当前对话框
		_currentChoiceBox->removeFromParent();																		// 移除对话框
		_currentChoiceBox = nullptr;																				// 重置对话框
	}

	_currentChoiceBox = cocos2d::Sprite::create("smallmap/box3.png");												// 创建对话框
	auto visibleSize = Director::getInstance()->getVisibleSize();													// 获取可见大小
	_currentChoiceBox->setPosition(Vec2(visibleSize.width / 2, 5 * visibleSize.height / 6));						// 设置对话框位置
	this->addChild(_currentChoiceBox, 1);																			// 添加对话框
	_currentChoiceBox->setLocalZOrder(100);																			// 让对话框处于较高的层级

	auto label = cocos2d::Label::createWithTTF(question, "fonts/Marker Felt.ttf", 48);								// 创建标签
	label->setTextColor(cocos2d::Color4B::BLACK);																	// 设置标签颜色
	label->setPosition(_currentChoiceBox->getContentSize().width / 2, _currentChoiceBox->getContentSize().height / 2 - 30);	// 设置标签位置
	_currentChoiceBox->addChild(label, 1);																			// 添加标签到对话框
	label->setLocalZOrder(101);																						// 让标签处于较高的层级

	float buttonY = 50;																								// 初始化按钮Y坐标
	for (size_t i = 0; i < choices.size(); ++i)																		// 遍历选择
	{
		auto button = cocos2d::ui::Button::create("button1.png", "button2.png");									// 创建按钮
		button->setTitleText(choices[i].first);																		// 设置按钮文本	
		button->setTitleFontName("fonts/Marker Felt.ttf");															// 设置按钮字体
		button->setTitleColor(cocos2d::Color3B::BLACK);																// 设置按钮文本颜色
		button->setTitleFontSize(24);																				// 设置按钮文本大小
		button->setPosition(cocos2d::Vec2(_currentChoiceBox->getContentSize().width / 2, buttonY + i * 150 - 400));	// 设置按钮位置
		_currentChoiceBox->addChild(button);																		// 添加按钮到对话框

		/* 执行选择后的回调*/
		button->addClickEventListener([=](cocos2d::Ref* sender) {
			if (choices[i].second) {
				choices[i].second();
			}
			/*在回调后再移除对话框*/ 
			_currentChoiceBox->removeFromParent();																	// 移除对话框										
			_currentChoiceBox = nullptr;																			// 重置对话框
			});
	}
}
/*NPC 回答关于城镇的情况*/ 
void MiniMap::displayTownInfo(cocos2d::Sprite* npc)																	// NPC回答关于城镇的情况
{
	displayChoice2(npc, "This is a peaceful town. You can find a shop,\n a tavern, and a blacksmith.", {		    // 显示对话框
		{"I see, tell me more!", [this, npc]() { {													
				this->scheduleOnce([=](float) {																		// 延时显示下一个对话框，避免遮挡
					displayTownDetails(npc);																		// 显示城镇详细信息
				}, 0.1f, "handleChatNPC");																			// 延时0.1秒
			} }},
		{"That's enough, thanks!", [this, npc]() { displayGoodbye(npc); }}											// 显示再见
		});
}

/*NPC 详细介绍城镇*/ 
void MiniMap::displayTownDetails(cocos2d::Sprite* npc)																// NPC 详细介绍城镇
{
	displayDialogue(npc, "The shop sells potions, the tavern offers drinks and rumors, and the blacksmith can upgrade your gear.");
}

/*NPC 给出任务信息*/ 
void MiniMap::displayQuestInfo(cocos2d::Sprite* npc)																// NPC 给出任务信息
{
	displayChoice2(npc, "I have a quest for you: Collect 10 herbs.", {
		{"Maybe later", [this, npc]() { displayGoodbye(npc); }},													// 显示再见
		{"Tell me more", [this, npc]() { displayQuestDetails(npc); }}												// 显示任务详细信息
		});
}

/* NPC 详细任务信息*/
void MiniMap::displayQuestDetails(cocos2d::Sprite* npc)
{
	displayDialogue(npc, "The herbs grow near the forest. \nPlease bring them back to me once you've collected them.");
}

/*NPC 说“再见”*/ 
void MiniMap::displayGoodbye(cocos2d::Sprite* npc)
{
	displayDialogue(npc, "Goodbye, and good luck on your adventures!");
}

void MiniMap::displayDialogue(Sprite* npc, const std::string& text)
{
	if (_currentDialogueBox) {																//如果对话框存在			
		_currentDialogueBox->removeFromParent();											// 移除对话框
		_currentDialogueBox = nullptr;														// 重置对话框
	}

	auto dialogueBox = Sprite::create("smallmap/box3.png");									// 创建对话框
	if (!dialogueBox) {																		// 如果对话框创建失败
		CCLOG("Failed to create dialogue box!");											// 输出错误信息
		return;																				// 退出
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();							// 获取可见区域的大小
	dialogueBox->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));			// 设置对话框位置
	this->addChild(dialogueBox);															// 添加对话框到场景

	auto label = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 24);					// 创建标签
	label->setTextColor(Color4B::BLACK);													// 设置标签颜色
	label->setPosition(dialogueBox->getContentSize() / 2);									// 设置标签位置
	dialogueBox->addChild(label);															// 添加标签到对话框
	_currentDialogueBox = dialogueBox;														// 设置当前对话框

	/* 自动消失对话框*/
	this->scheduleOnce([=](float) {
		dialogueBox->removeFromParent();													// 移除对话框
		_currentDialogueBox = nullptr;
		}, 3.0f, "closeDialogue");
}

void MiniMap::displayTaskOptions(NPCData& npcData) {										// 显示任务选项
	displayChoice1(npcData.npcSprite, npcData.ppp->getTaskName(), {
		{"YES", [this, &npcData]() {
			npcData.ppp->state = 0;															// 设置任务状态为已分配
			createTaskMenu();																// 创建任务菜单
			displayDialogue(npcData.npcSprite, npcData.ppp->getTaskDescription());			// 显示对话框
		}},
		{"NO", nullptr}																		// 不接受任务
		});
}

void MiniMap::displayTaskPro(NPCData& npcData) {											// 显示任务选项
	displayChoice1(npcData.npcSprite, npcData.ppp->getTaskName(), {		                    // 显示任务选项
		{"YES", [this, &npcData]() {
			npcData.ppp->state = 0;															// 设置任务状态为已分配
			CCLOG("message", npcData.targetScene);											// 输出信息
			player->removeFromParent();														// 移除玩家
			GlobalManager::getInstance().setLastMap(mapName);								// 设置上一个地图
			const auto& taskListbat = GlobalManager::getInstance().getTasks();				// 获取任务列表
			taskListbat[0]->id = npcData.taskid;											// 设置任务ID
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, getSceneByName(npcData.targetScene)));	// 替换场景
			npcData.ppp->state = 1;															// 设置任务状态为已完成

		}},
		{"NO", nullptr}																		// 不接受任务
		});
}

void MiniMap::displayTaskStatus(NPCData& npcData) {
	displayDialogue(npcData.npcSprite, "TASK");												// 显示对话框
}

void MiniMap::displayRewardOptions(NPCData& npcData) {
	displayChoice1(npcData.npcSprite, npcData.ppp->getTaskReward(), {						// 显示奖励选项
		{"OF COURSE", [this, &npcData]() {
			if (npcData.ppp->state == 1) {													// 如果任务状态是已完成
				// 标记任务已领取奖励
				if (npcData.ppp->getTaskName() == "WATER TASK" || npcData.ppp->getTaskName() == "GOLD TASK" 
					|| npcData.ppp->getTaskName() == "SOIL TASK" || npcData.ppp->getTaskName() == "FIRE TASK" 
					|| npcData.ppp->getTaskName() == "WOOD TASK") {
					player->Upgrade();														// 玩家升级
				}
				npcData.ppp->state = 2;														//displayDialogue(npcData.npcSprite, "congragulations！");
			}
		}},
		{"LATER", nullptr}
		});
}

cocos2d::Scene* MiniMap::getSceneByName(const std::string& sceneName) {
	if (sceneName == "QuizGame")															// 如果场景名是QuizGame
	{
		return QuizGame::create();															// 返回 Task1Scene 场景
	}
	else if (sceneName == "BattleScene")													// 如果场景名是BattleScene
	{
		return BattleScene::create();														// 返回 Task2Scene 场景
	}
	else
		return BattleScene::create();														// 返回 Task2Scene 场景
}

/*清除监听器*/ 
void MiniMap::StopListening()
{
	if (keyboardListener) {
		_eventDispatcher->removeEventListener(keyboardListener);							// 移除监听器
		keyboardListener = nullptr;															// 重置监听器
	}
}

void MiniMap::openBackpack()																// 打开背包
{
	auto _backpack = new Backpack();														// 创建背包
	auto _backpack_num = new Backpack();													// 创建背包
	const auto& backpack1 = GlobalManager::getInstance().getArmors();						// 获取背包1
	const auto& backpack2 = GlobalManager::getInstance().getFoods();						// 获取背包2
	const auto& backpack3 = GlobalManager::getInstance().getMaterials();					// 获取背包3
	const auto& backpack4 = GlobalManager::getInstance().getWeapons();						// 获取背包4

	for (auto back1 : backpack1) {															// 遍历背包1
		if (back1->isPicked) {																// 如果已经拾取
			_backpack->_items.push_back({ back1->num,back1->name });						// 添加到背包
		}
	}
	for (auto back2 : backpack2) {															// 遍历背包2
		if (back2->isPicked) {																// 如果已经拾取
			_backpack->_items.push_back({ back2->num,back2->name });						// 添加到背包
		}
	}
	for (auto back3 : backpack3) {															// 遍历背包3
		if (back3->isPicked) {																// 如果已经拾取
			_backpack->_items.push_back({ back3->num,back3->name });						// 添加到背包
		}
	}
	for (auto back4 : backpack4) {															// 遍历背包4
		if (back4->isPicked) {																// 如果已经拾取
			_backpack->_items.push_back({ back4->num,back4->name });						// 添加到背包
		}
	}
	 
	auto backpackLayer = BackpackLayer::create();											// 创建背包层，设置背包数据
	backpackLayer->setBackpack(_backpack);													// 设置背包数据
	this->addChild(backpackLayer, 10);														// 添加背包层到场景，设置层级最高
}

/*检查玩家是否靠近物品并执行拾取操作*/ 
void MiniMap::checkPickUpItems()
{
	auto& item_ = GlobalManager::getInstance().getFoods();									// 获取食物
	auto& item_1 = GlobalManager::getInstance().getMaterials();								// 获取材料

	CCLOG("Checking for nearby items...");													// 输出信息

	for (auto it = goldoreItems.begin(); it != goldoreItems.end(); )						// 遍历金矿
	{
		auto& item = *it;																	// 获取物品
		auto itemSprite = item.itemSprite;													// 获取物品精灵
		bool isNear = IsColliding(itemSprite->getPosition() + itemNode->getPosition());		// 检查是否靠近物品

		if (isNear)
		{
			/*调用拾取交互*/ 
			PickUpInteraction(&item);														// 拾取交互					
			item_1[item.index]->num++;														// 物品数量加1
			item_1[item.index]->isPicked = 1;												// 设置物品已拾取
			it = goldoreItems.erase(it);													// 删除当前物品并更新迭代器

			/* 从地图中移除物品*/
			itemSprite->setVisible(false);													// 隐藏物品图像
			CCLOG("Picked up GoldOre Item with ID: %d", item.id);							// 输出信息

			break;																			// 一次拾取后退出循环
		}
		else
		{
			++it;  // 如果没有靠近物品，继续检查下一个物品
		}
	}

	for (auto it = appleItems.begin(); it != appleItems.end(); )							// 遍历苹果
	{
		auto& item = *it;																	// 获取物品
		auto itemSprite = item.itemSprite;													// 获取物品精灵
		bool isNear = IsColliding(itemSprite->getPosition() + itemNode->getPosition());		// 检查是否靠近物品

		if (isNear)																			// 如果靠近物品,执行拾取操作
		{
			PickUpInteraction(&item);														// 拾取交互
			item_[item.index]->num++;														// 物品数量加1
			item_[item.index]->isPicked = 1;												// 设置物品已拾取

			it = appleItems.erase(it);														// 从物品容器中删除已经拾取的物品, 
																							// 删除当前物品并更新迭代器

			/*从地图中移除物品*/ 
			itemSprite->setVisible(false);													// 隐藏物品图像
			CCLOG("Picked up GoldOre Item with ID: %d", item.id);							// 输出信息

			break;																			// 一次拾取后退出循环												
		}
		else
		{
			++it;																			// 如果没有靠近物品，继续检查下一个物品
		}
	}
}

void MiniMap::PickUpInteraction(ItemList* item)												// 拾取交互
{
	// 显示拾取提示
	auto label = Label::createWithTTF("You picked up !", "fonts/arial.ttf", 100);			// 创建标签
	auto visibleSize = Director::getInstance()->getVisibleSize();							// 获取可见大小
	label->setColor(Color3B::YELLOW);														// 使用预定义的黄色
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));				// 设置位置
	this->addChild(label);																	// 添加到场景
	label->runAction(Sequence::create(														// 运行动作序列
		FadeOut::create(2.0f),																// 淡出
		RemoveSelf::create(),																// 移除自身
		nullptr));																			// 空指针
}

void MiniMap::onEnter() {
	Scene::onEnter();																		// 必须调用父类的实现
	CCLOG("SimpleSceneA onEnter");															// 输出信息
	/*设置缩放比例*/
	float scaleX = 3.0f;																	// 设置X轴缩放比例
	float scaleY = 3.0f;																	// 设置Y轴缩放比例
	
	auto tileSize = tiledMap->getTileSize();												// 获取瓦片地图瓦片大小

	// 计算瓦片缩放后大小
	auto playerSize = tileSize;																// 设置玩家大小
	playerSize.width *= scaleX * 2;															// 设置玩家宽度
	playerSize.height *= scaleY * 2;														// 设置玩家高度

	player->initWithFile(player->getFileName());											// 加载主控精灵图像
	player->setContentSize(playerSize);														// 设置主控精灵大小
	player->Sprite::setPosition(playerPos);													// 设置主控精灵位置
	player->setVisible(true);																// 设置主控精灵可见
	player->setLocalZOrder(255);															// 设置主控精灵层级
	this->resume();																			// 在这里添加场景恢复时需要执行的代码
}

void MiniMap::onEnterTransitionDidFinish() {
	Scene::onEnterTransitionDidFinish();													// 必须调用父类的实现
	CCLOG("SimpleSceneA onEnterTransitionDidFinish");										// 输出信息
	/*设置缩放比例*/
	float scaleX = 3.0f;																	// 设置X轴缩放比例
	float scaleY = 3.0f;																	// 设置Y轴缩放比例
	auto tileSize = tiledMap->getTileSize();												// 获取瓦片地图瓦片大小

	/*计算瓦片缩放后大小*/ 
	auto playerSize = tileSize;																// 设置玩家大小					
	playerSize.width *= scaleX * 2;															// 设置玩家宽度
	playerSize.height *= scaleY * 2;														// 设置玩家高度
	 
	player->initWithFile(player->getFileName());											// 加载主控精灵图像 
	player->setContentSize(playerSize);														// 设置主控精灵大小
	player->setPosition(playerPos);															// 设置主控精灵位置
	player->setVisible(true);																// 设置主控精灵可见
	player->setLocalZOrder(255);															// 设置主控精灵层级
	this->resume();																			// 在这里添加场景恢复时需要执行的代码
}

void MiniMap::restorePositionsAfterPop()
{
	auto player = GlobalManager::getInstance().getPlayer();									// 获取玩家
	player->setPosition(preposition);														// 设置玩家位置
	player->Sprite::setPosition(preposition);												// 设置玩家位置
}
// 验证精灵位置
void MiniMap::verifySprites() {};