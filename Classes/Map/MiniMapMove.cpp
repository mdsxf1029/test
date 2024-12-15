#include <cmath>
#include <vector>
#include "MiniMap.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
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
        float width = visibleSize.width / 2, height = visibleSize.height; // 设置对话框的大小
        background->setTextureRect(cocos2d::Rect(0.0f, 0.0f, width, height)); // 设为矩形
        background->setColor(Color3B(255, 255, 255)); // 设置对话框背景为白色        
        background->setPosition(centralWorldPos); // 设置对话框位置为视窗中心       
        background->setOpacity(200); // 设置对话框不透明度为较高
        this->addChild(background);

        // 创建文字标签
        auto label = cocos2d::Label::createWithSystemFont("Where do you want to go?", "Arial", 64); // 设置文本
        label->setPosition(centralWorldPos + cocos2d::Vec2(0.0f, visibleSize.height / 4)); // 设置位置
        label->setColor(cocos2d::Color3B(0, 0, 0)); // 设置文本颜色为黑色
        this->addChild(label);

        // 不同地图
        std::vector<std::string> map = { "gold","wood","water","fire","earth","none","village"};

        // 如果现在是村庄
        if (mapName == "village.tmx") {
            for (int i = 0; i < 6; i++) {
                // 创建按钮
                auto button = ui::Button::create("button_normal.png", "button_pressed.png", "button_disabled.png");

                // 设置按钮标题
                button->setTitleText(map[i]); // 设置文本
                button->setTitleFontSize(48); // 设置字号
                button->setTitleColor(Color3B(0, 0, 0)); // 设置标题为黑色
                button->setTitleFontName("Arial"); // 设置标题字体

                // 获取任务
                const auto& tasks = GlobalManager::getInstance().getTasks();
                std::string targetID = "TASK_";
                std::string need = map[i];
                std::transform(need.begin(), need.end(), need.begin(),
                    [](unsigned char c) { return std::toupper(c); }); // 转大写
                targetID += need;

                // 查询任务是否完成
                auto it = std::find_if(tasks.begin(), tasks.end(), [targetID](const std::shared_ptr<Task>& obj) {
                    return (obj->getTaskName() == targetID && obj->isTaskFinished());
                    });

                // 如果未完成，禁用按钮
                if (it == tasks.end()) {
                    button->setEnabled(false); // 禁用按钮
                }

                // 添加按钮点击事件
                button->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));

                // 设置按钮位置
                button->setPosition(cocos2d::Vec2(centralWorldPos.x, visibleSize.height * 3 / 4 - i * 100));

                // 将按钮添加到场景中
                this->addChild(button);
            }
        }
        else if (mapName == "castle.tmx") {
            // 创建按钮
            auto button1 = ui::Button::create("button_normal.png", "button_pressed.png", "button_disabled.png");
            auto button2 = ui::Button::create("button_normal.png", "button_pressed.png", "button_disabled.png");

            // 设置按钮的位置
            button1->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y - visibleSize.height / 3));
            button2->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y + visibleSize.height / 3));

            // 设置按钮标题
            button1->setTitleText(map[6]); // 设置文本
            button1->setTitleFontSize(48); // 设置字号
            button1->setTitleColor(Color3B(0, 0, 0)); // 设置标题为黑色
            button1->setTitleFontName("Arial"); // 设置标题字体
            button2->setTitleText(map[5]); // 设置文本
            button2->setTitleFontSize(48); // 设置字号
            button2->setTitleColor(Color3B(0, 0, 0)); // 设置标题为黑色
            button2->setTitleFontName("Arial"); // 设置标题字体

            // 添加按钮点击事件
            button1->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));
            button2->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));

            // 将按钮添加到场景中
            this->addChild(button1);
            this->addChild(button2);
        }
        else {
            // 查找相邻地图
            std::string newMap1, newMap2;
            GetNeighborMap(newMap1, newMap2);
            
            for (int i = 0; i < 4; i++) {
                // 创建按钮
                auto button = ui::Button::create("button_normal.png", "button_pressed.png", "button_disabled.png");

                // 设置按钮位置
                button->setPosition(cocos2d::Vec2(centralWorldPos.x, visibleSize.height * 3 / 4 - i * 100));

                // 设置按钮标题
                button->setTitleFontSize(48); // 设置字号
                button->setTitleColor(Color3B(0, 0, 0)); // 设置标题为黑色
                button->setTitleFontName("Arial"); // 设置标题字体
                
                // 设置标题文本
                if (i == 0 || i == 1) {
                    std::string need;
                    if (i == 0) {
                        button->setTitleText(newMap1);
                        need = newMap1;
                    }
                    else {
                        button->setTitleText(newMap2);
                        need = newMap2;
                    }

                    // 获取任务
                    const auto& tasks = GlobalManager::getInstance().getTasks();
                    std::string targetID = "TASK_";
                    std::transform(need.begin(), need.end(), need.begin(),
                        [](unsigned char c) { return std::toupper(c); }); // 转大写
                    targetID += need;

                    // 查询任务是否完成
                    auto it = std::find_if(tasks.begin(), tasks.end(), [targetID](const std::shared_ptr<Task>& obj) {
                        return (obj->getTaskName() == targetID && obj->isTaskFinished());
                        });

                    // 如果未完成，禁用按钮
                    if (it == tasks.end()) {
                        button->setEnabled(false); // 禁用按钮
                    }
                }
                else if (i == 3) {
                    button->setTitleText("village");
                }
                else
                    button->setTitleText("none");

                // 添加按钮点击事件
                button->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));

                // 将按钮添加到场景中
                this->addChild(button);
            }
        }
    }

    // 如果是村庄
    if (mapName == "village.tmx") {
        // 寻找是否有gate点
        auto gateLayer = tiledMap->getObjectGroup("Gate");

        // 标记传送与否
        bool gate = false;

        // 如果有gate点，找gate属性
        if (gateLayer) {
            auto gateObjects = gateLayer->getObjects();
            for (const auto& object : gateObjects) {
                cocos2d::ValueMap boatProperties = object.asValueMap();
                auto x = boatProperties["x"].asFloat();
                auto y = boatProperties["y"].asFloat();
                auto width = boatProperties["width"].asFloat();
                auto height = boatProperties["height"].asFloat();
                if (tilePos.x >= x && tilePos.x <= x + width && tilePos.y >= y && tilePos.y <= y + height) {
                    gate = true;
                    break;
                }
            }
        }

        // 如果在gate点
        if (gate) {
            // 创建按钮
            auto button1 = ui::Button::create("button_normal.png", "button_pressed.png", "button_disabled.png");
            auto button2 = ui::Button::create("button_normal.png", "button_pressed.png", "button_disabled.png");

            // 设置按钮的位置
            button1->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y - visibleSize.height / 3));
            button2->setPosition(cocos2d::Vec2(centralWorldPos.x, centralWorldPos.y + visibleSize.height / 3));

            // 设置按钮标题
            button1->setTitleText("castle"); // 设置文本
            button1->setTitleFontSize(48); // 设置字号
            button1->setTitleColor(Color3B(0, 0, 0)); // 设置标题为黑色
            button1->setTitleFontName("Arial"); // 设置标题字体
            button2->setTitleText("none"); // 设置文本
            button2->setTitleFontSize(48); // 设置字号
            button2->setTitleColor(Color3B(0, 0, 0)); // 设置标题为黑色
            button2->setTitleFontName("Arial"); // 设置标题字体

            // 添加按钮点击事件
            button1->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));
            button2->addClickEventListener(std::bind(&MiniMap::ButtonCallback, this, std::placeholders::_1));

            // 将按钮添加到场景中
            this->addChild(button1);
            this->addChild(button2);
        }
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
    removeChildByName("label");

    // 将 Ref 指针转换为 Button 指针
    ui::Button* button = static_cast<ui::Button*>(sender);

    // 获取按钮标题
    std::string title = button->getTitleText();

    // 补充标题为完整文件名
    if (title == "gold")
        title += "1.tmx";
    else
        title += ".tmx";

    // 移除按钮
    button->removeFromParent();

    // 前往新地图
    BoatingToMap(title);
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