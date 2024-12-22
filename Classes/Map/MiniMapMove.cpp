#include <cmath>
#include <vector>
#include "Map/MiniMap.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Sets/manager.h"
#include "HelloWorldScene.h"

std::shared_ptr<Player> _player = GlobalManager::getInstance().getPlayer();

// 更新主控精灵位置
void MiniMap::UpdatePlayerPosition(const cocos2d::EventKeyboard::KeyCode keyCode)
{
    cocos2d::Vec2 currentPos = _player->getPosition();                                                              // 获取主控精灵原位置
	CCLOG("Current player position: (%f, %f)", currentPos.x, currentPos.y);                                         // 输出原位置
	preposition = currentPos;                                                                                       // 记录原位置
    
	cocos2d::Vec2 newPos = GlobalManager::getInstance().getPlayer()->Move(keyCode);								   // 获取主控精灵新位置
	CCLOG("New player position: (%f, %f)", newPos.x, newPos.y);													   // 输出新位置

	bool walkable = true;																						   // 标记是否可行走
    auto collisionLayer = tiledMap->getObjectGroup("Collision");                                                   //获取碰撞检测的动态对象组  

    // 获取缩放比例
	auto scaleX = tiledMap->getScaleX();                                                                            // 获取x轴缩放比例
	auto scaleY = tiledMap->getScaleY();																			// 获取y轴缩放比例
	CCLOG("Scale factors: (%f, %f)", scaleX, scaleY);															    // 输出缩放比例

	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();                                    // 获取可视区域原点坐标
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();								    // 获取可视区域大小
	CCLOG("Visible area: origin(%f, %f), size(%f, %f)", origin.x, origin.y, visibleSize.width, visibleSize.height); // 输出可视区域信息

	cocos2d::Vec2 centralWorldPos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);					// 计算视窗中心的世界坐标
	CCLOG("Window center world position: (%f, %f)", centralWorldPos.x, centralWorldPos.y);						    // 输出视窗中心的世界坐标

    // 获取当前瓦片地图大小
	cocos2d::Size mapSize = tiledMap->getMapSize();															       // 获取地图大小
    CCLOG("Tile map size: (%f, %f)", mapSize.width, mapSize.height);

    // 获取瓦片地图瓦片大小
	cocos2d::Size tileSize = tiledMap->getTileSize();															   // 获取瓦片大小
    CCLOG("Tile size: (%f, %f)", tileSize.width, tileSize.height);

    // 获取当前瓦片地图坐标
	cocos2d::Vec2 currentMapPos = tiledMap->getPosition();														   // 获取地图位置
	CCLOG("Current tile map position: (%f, %f)", currentMapPos.x, currentMapPos.y);                                // 输出地图位置

    // 计算瓦片缩放后大小
	cocos2d::Size playerSize = tileSize;                                                                           // 获取瓦片大小
	playerSize.width *= scaleX;																					   // 计算缩放后宽度
	playerSize.height *= scaleY;																				   // 计算缩放后高度

    // 通过世界坐标获取精灵在瓦片层中的相对坐标
	cocos2d::Vec2 tilePos = tiledMap->convertToNodeSpace(newPos);												   // 获取新位置的瓦片坐标
	CCLOG("Relative tile position: (%f, %f)", tilePos.x, tilePos.y);										       // 输出瓦片坐标

    // 如果有碰撞检测层，找Collision属性
    if (collisionLayer) {
		auto collisionObjects = collisionLayer->getObjects();                                                       // 获取碰撞对象
		CCLOG("Number of collision objects: %lu", collisionObjects.size());										    // 输出碰撞对象数量
        for (const auto& object : collisionObjects) {
			cocos2d::ValueMap collisionProperties = object.asValueMap();										   // 获取碰撞属性
			auto x = collisionProperties["x"].asFloat();														   // 获取x坐标
			auto y = collisionProperties["y"].asFloat();														   // 获取y坐标
			auto width = collisionProperties["width"].asFloat();												   // 获取宽度
			auto height = collisionProperties["height"].asFloat();												   // 获取高度
			CCLOG("Collision area: (%f, %f), width: %f, height: %f", x, y, width, height);						   // 输出碰撞区域
			if (tilePos.x >= x && tilePos.x <= x + width && tilePos.y >= y && tilePos.y <= y + height) {		   // 如果碰撞
				walkable = false;																				   // 不可行走
				CCLOG("Collision detected: cannot move to (%f, %f)", tilePos.x, tilePos.y);						   // 输出碰撞信息
                break;
            }
        }
    }

    // 寻找是否有boat点
	auto boatLayer = tiledMap->getObjectGroup("Boat");															   // 获取boat层 
    // 标记传送与否
	bool boat = false;																							   // 标记是否在boat点
     
	if (boatLayer) {                                                                                               // 如果有boat层
		auto boatObjects = boatLayer->getObjects();																   // 获取boat对象
		CCLOG("Number of boat objects: %lu", boatObjects.size());												   // 输出boat对象数量
		for (const auto& object : boatObjects) {																   // 遍历boat对象
			cocos2d::ValueMap boatProperties = object.asValueMap();												   // 获取boat属性
			auto x = boatProperties["x"].asFloat();																   // 获取x坐标
			auto y = boatProperties["y"].asFloat();																   // 获取y坐标
			auto width = boatProperties["width"].asFloat();														   // 获取宽度
			auto height = boatProperties["height"].asFloat();													   // 获取高度
			CCLOG("Boat area: (%f, %f), width: %f, height: %f", x, y, width, height);							   // 输出boat区域
            if (tilePos.x >= x && tilePos.x <= x + width && tilePos.y >= y && tilePos.y <= y + height) {
				boat = true;																					   // 可以boat
                CCLOG("Boat detected: player is on a boat spot");
                break;
            }
        }
    }

    // 如果可以boat，调对话框
    if (boat) {
        CCLOG("Entering boat dialog");

        // 创建对话框的背景精灵
        auto background = cocos2d::Sprite::create();
        float width = visibleSize.width / 2, height = visibleSize.height / 2;                                    // 设置对话框的大小
        background->setTextureRect(cocos2d::Rect(0.0f, 0.0f, width, height));                                    // 设为矩形
        background->setColor(Color3B(255, 255, 255));                                                            // 设置对话框背景为白色        
        background->setPosition(centralWorldPos);                                                                // 设置对话框位置为视窗中心       
        background->setOpacity(200);                                                                             // 设置对话框透明度为较高
        background->setName("background");                                                                       // 设置背景精灵的名字
		this->addChild(background); 																		     // 添加背景精灵                    
		CCLOG("Background sprite has been added.");

        // 创建文字标签
        auto label = cocos2d::Label::createWithSystemFont("Where do you want to go?", "fonts/arial.ttf", 64);    // 设置文本
        label->setPosition(centralWorldPos + cocos2d::Vec2(0.0f, visibleSize.height / 3));                       // 设置位置
        label->setColor(cocos2d::Color3B(0, 0, 0));                                                              // 设置文本颜色为黑色
        label->setName("label");                                                                                 // 设置文本标签的名字
		this->addChild(label);  																		         // 添加文本标签                 
		CCLOG("Label has been added.");

        // 创建父节点管理所有按钮
		auto buttonParentNode = cocos2d::Node::create();														// 创建父节点
		this->addChild(buttonParentNode);																		// 添加父节点 
		auto closeButton = ui::Button::create("CloseSelected.png");												// 创建关闭按钮
		closeButton->setPosition(centralWorldPos + cocos2d::Vec2(width / 2, height / 2));						// 设置关闭按钮位置

		closeButton->addClickEventListener([this, buttonParentNode](cocos2d::Ref* sender) {					    // 添加点击事件
			auto sprite = this->getChildByName("background");                                                   // 查找背景精灵
             
            if (sprite) {
				sprite->removeFromParentAndCleanup(true);												   	    // 移除背景精灵
                CCLOG("background sprite has been removed.");
            }
			auto label = this->getChildByName("label");														    // 查找文本标签
             
            if (label) {
				label->removeFromParentAndCleanup(true);                                                        //移除文本标签
                CCLOG("label has been removed.");
            }
			buttonParentNode->removeAllChildren();															    // 移除所有子节点--按钮
            });
        buttonParentNode->addChild(closeButton);                                                                // 将按钮添加到父节点

		std::vector<std::string> map = { "gold","wood","earth","water","fire","none","village" };			    // 创建地图名称

        // 获取任务
        const auto& tasks = GlobalManager::getInstance().getTasks();										    // 获取任务

        if (mapName == "smallmap/village.tmx")                                                                  //如果当前是village
        {
            for (int i = 0; i < 6; i++)
            {
                auto button = ui::Button::create("CloseSelected.png", "CloseSelected.png", "CloseSelected.png");                // 创建按钮
                // 设置按钮标题
                button->setTitleText(map[i]);                                                                                   // 设置文本
				CCLOG("Build button %s", map[i].c_str());																		// 输出按钮信息   
                button->setTitleFontSize(48);                                                                                   // 设置字号
                button->setTitleColor(Color3B(0, 0, 0));                                                                        // 设置标题为黑色
                button->setTitleFontName("Arial");                                                                              // 设置标题字体

				// 查询前一个地图的任务是否完成（除了金地图）
                if (tasks[i]->state <= 0 && i < 5 && i != 0)      														            // 如果未完成，禁用按钮                                              
                {
                    button->setEnabled(false);
                }

                button->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));                // 添加按钮点击事件
                button->setPosition(cocos2d::Vec2(centralWorldPos.x, visibleSize.height * 2 / 3 - i * 70));                     // 设置按钮位置
                buttonParentNode->addChild(button);                                                                             // 将按钮添加到父节点中
            }
        }
        else if (mapName == "smallmap/castle.tmx")
        {
            // 创建按钮
			auto button1 = ui::Button::create("CloseNormal.png", "CloseNormal.png", "CloseNormal.png");                  // 创建按钮
            auto button2 = ui::Button::create("CloseSelected.png", "CloseSelected.png", "CloseSelected.png");

            // 设置按钮的位置
			button1->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y - visibleSize.height / 10));		 // 设置按钮位置
            button2->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y + visibleSize.height / 10));

            // 设置按钮标题
            button1->setTitleText(map[6]);                                                                               // 设置文本
            CCLOG("Build button %s", map[6].c_str());
            button1->setTitleFontSize(48);                                                                               // 设置字号
            button1->setTitleColor(Color3B(0, 0, 0));                                                                    // 设置标题为黑色
            button1->setTitleFontName("Arial");                                                                          // 设置标题字体
            button2->setTitleText(map[5]);                                                                               // 设置文本
            CCLOG("Build button %s", map[5].c_str());                                                                          
            button2->setTitleFontSize(48);                                                                               // 设置字号
            button2->setTitleColor(Color3B(0, 0, 0));                                                                    // 设置标题为黑色
            button2->setTitleFontName("Arial");                                                                          // 设置标题字体

			button1->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));		     // 添加按钮点击事件
            button2->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));

			buttonParentNode->addChild(button1);																	     // 将按钮添加到父节点中
            buttonParentNode->addChild(button2);
        }
        else
        {
			std::string newMap1, newMap2;
            int map1, map2;
            GetNeighborMap(newMap1, newMap2, map1, map2);															     // 获取相邻地图
            for (int i = 0; i < 4; i++)
            {
				auto button = ui::Button::create("CloseSelected.png", "CloseSelected.png", "CloseSelected.png");	     // 创建按钮
				button->setPosition(cocos2d::Vec2(centralWorldPos.x, visibleSize.height * 2 / 3 - i * 100));		     // 设置按钮位置

                // 设置按钮标题
                button->setTitleFontSize(48);                                                                            // 设置字号
                button->setTitleColor(Color3B(0, 0, 0));                                                                 // 设置标题为黑色
                button->setTitleFontName("Arial");                                                                       // 设置标题字体

                // 设置标题文本
                if (i == 0 || i == 1)
                {
                    if (i == 0)
                    {
						button->setTitleText(newMap1);                                                                   // 设置文本
                    }
                    else
                    {
						button->setTitleText(newMap2);																    // 设置文本
                    }

                    // 获取任务
                    if ((i == 0 && tasks[map1]->state <= 0) || (i == 1 && tasks[map2]->state <= 0))                                                                              // 如果未完成
                    {
                        button->setEnabled(false);                                                                      // 禁用按钮
                    }
                }
				else if (i == 3)                                                                                        // 如果是村庄
                {
					button->setTitleText("village");															    	// 设置文本
                }
                else
					button->setTitleText("none");																       // 设置文本

				button->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));	   // 添加按钮点击事件
				buttonParentNode->addChild(button);																	   // 将按钮添加到父节点中
            }
        }
    }

    // 如果是村庄
    if (mapName == "smallmap/village.tmx")
    {
        auto gateLayer = tiledMap->getObjectGroup("Gate");                                                            // 寻找是否有gate点
        bool gate = false;                                                                                            // 标记传送与否

        // 如果有gate点，找gate属性
        if (gateLayer) {
			auto gateObjects = gateLayer->getObjects();															      // 获取gate对象
            for (const auto& object : gateObjects) {
				cocos2d::ValueMap boatProperties = object.asValueMap();											      // 获取gate属性
				auto x = boatProperties["x"].asFloat();															      // 获取x坐标
				auto y = boatProperties["y"].asFloat();															      // 获取y坐标
				auto width = boatProperties["width"].asFloat();													      // 获取宽度
				auto height = boatProperties["height"].asFloat();											          // 获取高度
				if (tilePos.x >= x && tilePos.x <= x + width && tilePos.y >= y && tilePos.y <= y + height) {		  // 如果在gate点
					gate = true; 																			          // 可以gate
                    break;
                }
            }
        }

        // 如果在gate点
        if (gate)
        {
			auto buttonParentNode = cocos2d::Node::create();													  // 创建父节点
            this->addChild(buttonParentNode);																	    // 管理所有按钮

            // 创建按钮
			auto button1 = ui::Button::create("CloseNormal.png", "CloseNormal.png", "CloseNormal.png");		        // 创建按钮
            auto button2 = ui::Button::create("CloseSelected.png", "CloseSelected.png", "CloseSelected.png");

            // 设置按钮的位置
			button1->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y - visibleSize.height / 3));     // 设置按钮位置
            button2->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y + visibleSize.height / 3));

            // 设置按钮标题
            button1->setTitleText("castle");                                                                        // 设置文本
            button1->setTitleFontSize(48);                                                                          // 设置字号
            button1->setTitleColor(Color3B(0, 0, 0));                                                               // 设置标题为黑色
            button1->setTitleFontName("Arial");                                                                     // 设置标题字体
            button2->setTitleText("none");                                                                          // 设置文本
            button2->setTitleFontSize(48);                                                                          // 设置字号
            button2->setTitleColor(Color3B(0, 0, 0));                                                               // 设置标题为黑色
            button2->setTitleFontName("Arial");                                                                     // 设置标题字体

            // 添加按钮点击事件
			button1->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));	  // 添加按钮点击事件
            button2->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));

            // 将按钮添加到父节点中
			buttonParentNode->addChild(button1);																  // 将按钮添加到父节点中
            buttonParentNode->addChild(button2);
        }
    }
    // 定义区域边界世界坐标
	float minWorldX = centralWorldPos.x - visibleSize.width / 4;                                                  // 定义区域边界世界坐标x最小
	float minWorldY = centralWorldPos.y - visibleSize.height / 4;                                                 // 定义区域边界世界坐标y最小
	float maxWorldX = centralWorldPos.x + visibleSize.width / 4;												  // 定义区域边界世界坐标x最大
	float maxWorldY = centralWorldPos.y + visibleSize.height / 4;												  // 定义区域边界世界坐标y最大

    static int a = 0;
	auto objectGroupp = tiledMap->getObjectGroup("Objects");                                                      // 获取对象组
    if (objectGroupp) {
		auto npcGroup = objectGroupp->getObjects();															      // 获取对象
        for (auto& npcObj : npcGroup) {
			cocos2d::ValueMap npcData = npcObj.asValueMap();													  // 获取npc数据
            if (!npcData.empty()) {
				auto x = npcData["x"].asFloat();                                                                  // 获取x坐标
				auto y = npcData["y"].asFloat();																  // 获取y坐标
                
                if (tilePos.x >= x - tileSize.width && tilePos.x <= x + tileSize.width && tilePos.y >= y - tileSize.height && tilePos.y <= y + tileSize.height) {
                    CCLOG("Collide npc，%d", a);
                    CCLOG("X1,Y1 %f,%f", x, y);
                    a++;
                    break;
                }
            }
        }
    }
    // 如果能前往该坐标
    if (walkable)
    {
		float offset;                                                                                   // 定义偏移量
		if (abs(newPos.x - currentPos.x))															    // 如果x轴偏移
			offset = abs(newPos.x - currentPos.x);													    // 计算x轴偏移
        else
			offset = abs(newPos.y - currentPos.y);													    // 计算y轴偏移

        // 精灵向左
        if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW && newPos.x <= minWorldX && tilePos.x > 0
            && currentMapPos.x < 0) {
			cocos2d::Vec2 newMapPosition = currentMapPos + cocos2d::Vec2(offset, 0.0f);                 // 计算新地图位置
			cocos2d::Vec2 newNPCPos = npcNode->getPosition() + cocos2d::Vec2(offset, 0.0f);			    // 计算新NPC位置
			cocos2d::Vec2 newItemPos = itemNode->getPosition() + cocos2d::Vec2(offset, 0.0f);	        // 计算新物品位置

			CCLOG("newposition x:%f,y:%f", newMapPosition.x, newMapPosition.y);						    // 输出新地图位置
			CCLOG("newPos x:%f,y:%f", newPos.x, newPos.y);											    // 输出新位置
			CCLOG("minWorld x:%f,y:%f", minWorldX, minWorldY);										    // 输出区域边界
			CCLOG("npcNode x:%f,y%f", npcNode->getPositionX(), npcNode->getPositionY());			    // 输出NPC位置

			tiledMap->setPosition(newMapPosition);														// 设置新地图位置
			npcNode->setPosition(newNPCPos);															// 设置新NPC位置
			itemNode->setPosition(newItemPos);															// 设置新物品位置
        }

        // 精灵向右
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW && newPos.x >= maxWorldX    
            && tilePos.x < mapSize.width * tileSize.width && currentMapPos.x + (mapSize.width - 2) * tileSize.width * scaleX > visibleSize.width) {
			cocos2d::Vec2 newMapPosition = currentMapPos - cocos2d::Vec2(offset, 0.0f);                 // 计算新地图位置
			cocos2d::Vec2 newNPCPos = npcNode->getPosition() - cocos2d::Vec2(offset, 0.0f);			    // 计算新NPC位置
			cocos2d::Vec2 newItemPos = itemNode->getPosition() - cocos2d::Vec2(offset, 0.0f);	        // 计算新物品位置
			CCLOG("newposition x:%f,y:%f", newMapPosition.x, newMapPosition.y);						    // 输出新地图位置
			CCLOG("newPos x:%f,y:%f", newPos.x, newPos.y);											    // 输出新位置
			CCLOG("minWorld x:%f,y:%f", minWorldX, minWorldY);										    // 输出区域边界
			CCLOG("npcNode x:%f,y%f", npcNode->getPositionX(), npcNode->getPositionY());			    // 输出NPC位置
			tiledMap->setPosition(newMapPosition);														// 设置新地图位置
			npcNode->setPosition(newNPCPos);															// 设置新NPC位置
			itemNode->setPosition(newItemPos);															// 设置新物品位置
        }

        // 精灵向上
        else if (newPos.y >= maxWorldY && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW && tilePos.y > 0
            && currentMapPos.y + (mapSize.height - 2) * tileSize.height * scaleY > visibleSize.height) {
            cocos2d::Vec2 newMapPosition = currentMapPos - cocos2d::Vec2(0.0f, offset);                 //同上
            cocos2d::Vec2 newNPCPos = npcNode->getPosition() - cocos2d::Vec2(0.0f, offset);
            cocos2d::Vec2 newItemPos = itemNode->getPosition() - cocos2d::Vec2(0.0f, offset);
            CCLOG("newposition x:%f,y:%f", newMapPosition.x, newMapPosition.y);
            CCLOG("newPos x:%f,y:%f", newPos.x, newPos.y);
            CCLOG("minWorld x:%f,y:%f", minWorldX, minWorldY);
            CCLOG("npcNode x:%f,y%f", npcNode->getPositionX(), npcNode->getPositionY());
            tiledMap->setPosition(newMapPosition);
            npcNode->setPosition(newNPCPos);
            itemNode->setPosition(newItemPos);
        }

        // 精灵向下
        else if (newPos.y <= minWorldY && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW
            && tilePos.y < mapSize.height * tileSize.height && currentMapPos.y < 0) {
			cocos2d::Vec2 newMapPosition = currentMapPos + cocos2d::Vec2(0.0f, offset);				 //同上   
            cocos2d::Vec2 newNPCPos = npcNode->getPosition() + cocos2d::Vec2(0.0f, offset);
            cocos2d::Vec2 newItemPos = itemNode->getPosition() + cocos2d::Vec2(0.0f, offset);
            CCLOG("newposition x:%f,y:%f", newMapPosition.x, newMapPosition.y);
            CCLOG("newPos x:%f,y:%f", newPos.x, newPos.y);
            CCLOG("minWorld x:%f,y:%f", minWorldX, minWorldY);
            CCLOG("npcNode x:%f,y%f", npcNode->getPositionX(), npcNode->getPositionY());
            tiledMap->setPosition(newMapPosition);
            npcNode->setPosition(newNPCPos);
            itemNode->setPosition(newItemPos);
        }

        else if (newPos.x > 0 && newPos.x < visibleSize.width && newPos.y>0 && newPos.y < visibleSize.height) {
			auto moveTo = cocos2d::MoveTo::create(0.1f, newPos);									     		// 创建平滑动作
			_player->runAction(moveTo);																			// 运行动作
            GlobalManager::getInstance().getPlayer()->setPosition(newPos);                                      // 更新主控坐标
        }
    }
    else
    {
		CCLOG("无法前往(%f,%f)", newPos.x, newPos.y);															// 输出无法前往信息
    }
}

void MiniMap::ButtonCallback(Ref* sender)
{
	this->removeChildByName("background");                                                                    // 移除背景精灵
	this->removeChildByName("label");																		  // 移除文本标签
    ui::Button* button = static_cast<ui::Button*>(sender);													  // 获取按钮 将 Ref 指针转换为 Button 指针
	std::string title = button->getTitleText();																  // 获取按钮标题
    // 补充标题为完整文件名
	title = "smallmap/" + title;    																          // 补充标题                           
	if (title == "smallmap/gold")                                                                             // 如果是gold
		title += "1.tmx";                                                                                     // 补充标题
	else if (title == "smallmap/water")                                                                       // 如果是water
		title = "smallmap/whole3.tmx";                                                                        // 补充标题
    else
		title += ".tmx";                                                                                      // 补充标题

	auto parentNode = button->getParent();                                                                    //获取父节点
 
    if (parentNode)
		parentNode->removeAllChildren();																	  // 移除所有子节点-- 按钮
    else
		button->removeFromParentAndCleanup(true);															  // 移除按钮
    if (title != "smallmap/none.tmx")
		BoatingToMap(title);    																              // 航行到地图                     
}

void MiniMap::GetNeighborMap(std::string& newMap1, std::string& newMap2, int& map1, int& map2)                                      // 获取相邻地图
{
    if (mapName == "smallmap/gold1.tmx")                                                                      // 如果是gold1
    {
		newMap1 = "fire";                                                                                     //相邻地图1是fire
        newMap2 = "wood";                                                                                     //相邻地图2是wood
        map1 = 4;
        map2 = 1;
    }
    else if (mapName == "smallmap/wood.tmx")                                                                  // 如果是wood   
    {
        newMap1 = "gold";                                                                                     //相邻地图1是gold
        newMap2 = "earth";                                                                                    //相邻地图2是earth
        map1 = 1;
        map2 = 2;
    }
    else if (mapName == "smallmap/earth.tmx")                                                                 //如果是earth
    {
        newMap1 = "wood";                                                                                     //相邻地图1是wood
        newMap2 = "water";                                                                                     //相邻地图2是water
        map1 = 1;
        map2 = 3;
    }
    else if (mapName == "smallmap/whole3.tmx")                                                                 //如果是water
    {
        newMap1 = "earth";                                                                                     //相邻地图1是earth
        newMap2 = "fire";                                                                                     //相邻地图2是fire          
        map1 = 2;
        map2 = 4;
    }
    else if (mapName == "smallmap/fire.tmx")                                                                  //如果是fire
    {
        newMap1 = "water";                                                                                    //相邻地图1是water
        newMap2 = "gold";                                                                                    //相邻地图2是gold
        map1 = 3;
        map2 = 1;
    }
}