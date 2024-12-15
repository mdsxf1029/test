#include <cmath>
#include "MiniMap.h"
#include "cocos2d.h"
#include "Classes/manager/manager.h"

// 更新主控精灵位置
void MiniMap::UpdatePlayerPosition(const cocos2d::EventKeyboard::KeyCode keyCode)
{
    // 获取主控精灵原位置
    cocos2d::Vec2 currentPos = player->getPosition();

    // 获取主控精灵新位置
    cocos2d::Vec2 newPos = GlobalManager::getInstance().getPlayer()->Move(keyCode);

    // 是否能走
    bool walkable = true;

    // 获取碰撞检测的动态对象组
    auto collisionLayer = tiledMap->getObjectGroup("Collision");

    // 获取缩放比例
    auto scaleX = tiledMap->getScaleX();
    auto scaleY = tiledMap->getScaleY();

    // 获取当前可视区域原点坐标
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // 获取当前可视区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 计算视窗中心的世界坐标
    cocos2d::Vec2 centralWorldPos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);

    // 获取当前瓦片地图大小
    cocos2d::Size mapSize = tiledMap->getMapSize();

    // 获取瓦片地图瓦片大小
    cocos2d::Size tileSize = tiledMap->getTileSize();

    // 获取当前瓦片地图坐标
    cocos2d::Vec2 currentMapPos = tiledMap->getPosition();

    // 计算瓦片缩放后大小
    cocos2d::Size playerSize = tileSize;
    playerSize.width *= scaleX;
    playerSize.height *= scaleY;

    // 通过世界坐标获取精灵在瓦片层中的相对坐标
    cocos2d::Vec2 tilePos = tiledMap->convertToNodeSpace(newPos);

    // 如果有碰撞检测层，找Collision属性
    if (collisionLayer) {
        auto collisionObjects = collisionLayer->getObjects();
        for (const auto& object : collisionObjects) {
            cocos2d::ValueMap collisionProperties = object.asValueMap();
            auto x = collisionProperties["x"].asFloat();
            auto y = collisionProperties["y"].asFloat();
            auto width = collisionProperties["width"].asFloat();
            auto height = collisionProperties["height"].asFloat();
            if (tilePos.x >= x && tilePos.x <= x + width && tilePos.y >= y && tilePos.y <= y + height) {
                walkable = false;
                break;
            }
        }
    }

    // 寻找是否有boat点
    auto boatLayer = tiledMap->getObjectGroup("Boat");

    // 标记传送与否
    bool boat = false;

    // 如果有boat点，找boat属性
    if (boatLayer) {
        auto boatObjects = boatLayer->getObjects();
        for (const auto& object : boatObjects) {
            cocos2d::ValueMap boatProperties = object.asValueMap();
            auto x = boatProperties["x"].asFloat();
            auto y = boatProperties["y"].asFloat();
            auto width = boatProperties["width"].asFloat();
            auto height = boatProperties["height"].asFloat();
            if (tilePos.x >= x && tilePos.x <= x + width && tilePos.y >= y && tilePos.y <= y + height) {
                boat = true;
                break;
            }
        }

    }

    // 如果可以boat，调对话框
    if (boat) {
        // 创建对话框的背景精灵
        auto background = cocos2d::Sprite::create();
        float width = visibleSize.width / 4, height = visibleSize.height / 5; // 设置对话框的大小
        background->setTextureRect(cocos2d::Rect(0.0f, 0.0f, width, height)); // 设为矩形
        background->setColor(Color3B(255, 255, 255)); // 设置对话框背景为白色        
        background->setPosition(centralWorldPos); // 设置对话框位置为视窗中心       
        background->setOpacity(200); // 设置对话框透明度为较高
        this->addChild(background);

        // 创建文字标签
        auto label = cocos2d::Label::createWithSystemFont("Where do you want to go?", "Arial", 24); // 设置文本
        label->setPosition(centralWorldPos + cocos2d::Vec2(0.0f, visibleSize.height / 20)); // 设置位置
        label->setColor(cocos2d::Color3B(255, 255, 255)); // 设置文本颜色为白色
        this->addChild(label);

        // 查找相邻地图
        std::string newMap1, newMap2;
        GetNeighborMap(newMap1, newMap2);

        // 创建按钮
        auto label1 = cocos2d::Label::createWithSystemFont(newMap1, "Arial", 24);
        auto label2 = cocos2d::Label::createWithSystemFont(newMap2, "Arial", 24);
        auto label3 = cocos2d::Label::createWithSystemFont("None", "Arial", 24);
        auto button1 = cocos2d::MenuItemLabel::create(label1, CC_CALLBACK_1(MiniMap::ButtonCallback, this));
        auto button2 = cocos2d::MenuItemLabel::create(label2, CC_CALLBACK_1(MiniMap::ButtonCallback, this));
        auto button3 = cocos2d::MenuItemLabel::create(label3, CC_CALLBACK_1(MiniMap::ButtonCallback, this));
        button1->setPosition(centralWorldPos + cocos2d::Vec2(-visibleSize.width / 8, -visibleSize.height / 20));
        button2->setPosition(centralWorldPos + cocos2d::Vec2(0.0f, -visibleSize.height / 20));
        button3->setPosition(centralWorldPos + cocos2d::Vec2(visibleSize.width / 8, -visibleSize.height / 20));
    }

    // 定义区域边界世界坐标
    float minWorldX = centralWorldPos.x - visibleSize.width / 4;
    float minWorldY = centralWorldPos.y - visibleSize.height / 4;
    float maxWorldX = centralWorldPos.x + visibleSize.width / 4;
    float maxWorldY = centralWorldPos.y + visibleSize.height / 4;

    // 如果能前往该坐标
    if (walkable) {
        // 设置偏移量
        float offset;
        if (abs(newPos.x - currentPos.x))
            offset = abs(newPos.x - currentPos.x);
        else
            offset = abs(newPos.y - currentPos.y);

        // 精灵向左
        if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW && newPos.x <= minWorldX && tilePos.x > 0
            && currentMapPos.x < 0) {
            cocos2d::Vec2 newMapPosition = currentMapPos + cocos2d::Vec2(offset, 0.0f);
            tiledMap->setPosition(newMapPosition);
        }

        // 精灵向右
        else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW && newPos.x >= maxWorldX
            && tilePos.x < mapSize.width * tileSize.width && currentMapPos.x + (mapSize.width - 2) * tileSize.width * scaleX > visibleSize.width) {
            cocos2d::Vec2 newMapPosition = currentMapPos + cocos2d::Vec2(-offset, 0.0f);
            tiledMap->setPosition(newMapPosition);
        }

        // 精灵向上
        else if (newPos.y >= maxWorldY && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW && tilePos.y > 0
            && currentMapPos.y + (mapSize.height - 2) * tileSize.height * scaleY > visibleSize.height) {
            cocos2d::Vec2 newMapPosition = currentMapPos + cocos2d::Vec2(0.0f, -offset);
            tiledMap->setPosition(newMapPosition);
        }

        // 精灵向下
        else if (newPos.y <= minWorldY && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW
            && tilePos.y < mapSize.height * tileSize.height && currentMapPos.y < 0) {
            cocos2d::Vec2 newMapPosition = currentMapPos + cocos2d::Vec2(0.0f, offset);
            tiledMap->setPosition(newMapPosition);
        }

        else if (newPos.x > 0 && newPos.x < visibleSize.width && newPos.y>0 && newPos.y < visibleSize.height) {
            // 创建平滑移动的动作
            auto moveTo = cocos2d::MoveTo::create(0.1f, newPos);

            // 执行动作
            player->runAction(moveTo);

            // 更新主控坐标
            GlobalManager::getInstance().getPlayer()->setPosition(newPos);
        }
    }
    else {
        CCLOG("无法前往(%f,%f)", newPos.x, newPos.y);
    }
}

void MiniMap::ButtonCallback(Ref* sender)
{
    // 移除背景精灵
    removeChildByName("background");

    // 移除文字标签
    removeChildByName("label1");
    removeChildByName("label2");
    removeChildByName("label3");

    // 移除按钮菜单
    removeChildByName("button1");
    removeChildByName("button2");
    removeChildByName("button3");

    // 从按钮中获取 Label
    auto menuItemLabel = static_cast<cocos2d::MenuItemLabel*>(sender);
    auto label = dynamic_cast<cocos2d::Label*>(menuItemLabel->getLabel());

    // 获取 Label 的文本
    std::string labelText = label->getString();
    if (labelText == "None")
        return;
    else {
        const auto& tasks = GlobalManager::getInstance().getTasks();
        std::string targetID = "TASK_";
        if (labelText == "gold")
            targetID += "GOLD";
        else if (labelText == "wood")
            targetID += "WOOD";
        else if (labelText == "water")
            targetID += "WATER";
        else if (labelText == "fire")
            targetID += "FIRE";
        else
            targetID += "EARTH";
        auto it = std::find_if(tasks.begin(), tasks.end(), [targetID](const std::shared_ptr<Task>& obj) {
            return (obj->getTaskName() == targetID && obj->isTaskFinished());
            });
        if (it != tasks.end()) {
            if (labelText == "gold")
                labelText += "1.tmx";
            else
                labelText += ".tmx";
            BoatingToMap(labelText);
        }
    }
}

void MiniMap::GetNeighborMap(std::string& newMap1, std::string& newMap2)
{
    if (mapName == "gold1.tmx") {
        newMap1 = "earth";
        newMap2 = "wood";
    }
    else if (mapName == "wood.tmx") {
        newMap1 = "gold";
        newMap2 = "water";
    }
    else if (mapName == "water.tmx") {
        newMap1 = "wood";
        newMap2 = "fire";
    }
    else if (mapName == "fire.tmx") {
        newMap1 = "water";
        newMap2 = "earth";
    }
    else {
        newMap1 = "fire";
        newMap2 = "earth";
    }
}