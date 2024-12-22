#include "BossMapInteraction.h"
#include "Sets/inventory.h"  // 管理玩家背包

USING_NS_CC;

bool BossMapInteraction::init()
{
    // 初始化地图
    map.loadMap("boss.tmx");
    selectedItem = nullptr;

    // 监听鼠标点击事件
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        Vec2 touchLocation = touch->getLocation();
        checkItemClick(touchLocation);
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // 加载地图数据，包括物品、碰撞对象等
    loadMapData();

    return true;
}

void BossMapInteraction::loadMapData()
{
    // 加载地图
    map.loadMap("boss.tmx");

    // 获取碰撞层
    auto collisionLayer = map->getObjectGroup("Collision");
    if (collisionLayer)
    {
        auto collisionObjects = collisionLayer->getObjects();
        for (const auto& object : collisionObjects)
        {
            ValueMap collisionProperties = object.asValueMap();
            auto collisionID = collisionProperties["id"].asInt();  // 获取碰撞对象的 ID
            auto x = collisionProperties["x"].asFloat();
            auto y = collisionProperties["y"].asFloat();
            CCLOG("Collision Object ID: %d at Position: (%f, %f)", collisionID, x, y);

            // 存储碰撞对象的数据，准备交互使用
            collisionItems.push_back(CollisionItem{ collisionID, Vec2(x, y) });
        }
    }
    // 获取可交互金矿对象层
    auto goldoreLayer = map->getObjectGroup("GoldOre");
    if (goldoreLayer)
    {
        auto goldoreObjects = collisionLayer->getObjects();
        for (const auto& object : goldoreObjects)
        {
            ValueMap goldoreProperties = object.asValueMap();
            auto goldoreID = goldoreProperties["id"].asInt();  // 获取碰撞对象的 ID
            auto x = goldoreProperties["x"].asFloat();
            auto y = goldoreProperties["y"].asFloat();
            CCLOG("GoldOre Object ID: %d at Position: (%f, %f)", goldoreID, x, y);

            // 存储碰撞对象的数据，准备交互使用
            goldoreItems.push_back(Item{ goldoreID, Vec2(x, y) });
        }
    }
}

void BossMapInteraction::onEnter()
{
    Scene::onEnter();
    // 进行一些初始化工作
}

void BossMapInteraction::onExit()
{
    // 清理资源
    _eventDispatcher->removeEventListenersForTarget(this);
    Scene::onExit();
}

void BossMapInteraction::checkItemClick(const Vec2& touchLocation)
{
    // 遍历物品，检查是否点击到物品
    for (auto it = goldoreItems.begin(); it != goldoreItems.end(); ++it)
    {
        // 假设物品的点击范围是一个固定的半径，你可以根据实际情况调整这个值
        float radius = 30.0f;  // 假设物品的点击范围是 30 像素

        if (it->position.distance(touchLocation) < radius)
        {
            // 点击到金矿物品了，执行拾取操作
            PickUpInteraction(&(*it));  // 传递指向物品的指针，进行拾取

            // 从物品容器中删除已经拾取的物品
            goldoreItems.erase(it);  // 删除当前物品
            CCLOG("Picked up GoldOre Item with ID: %d", it->id);

            // 获取金矿物品所在的对象层
            auto goldoreLayer = map->getObjectGroup("GoldOre");
            if (goldoreLayer)
            {
                // 遍历所有对象，找到与当前金矿物品匹配的 ID，并从对象层删除
                auto goldoreObjects = goldoreLayer->getObjects();
                for (auto& object : goldoreObjects)
                {
                    ValueMap goldoreProperties = object.asValueMap();
                    int goldOreID = goldoreProperties["id"].asInt();
                    if (goldOreID == it->id)  // 匹配物品 ID
                    {
                        goldoreLayer->removeObject(object);  // 从对象层删除物品
                        CCLOG("Removed GoldOre Object ID: %d at Position: (%f, %f)", goldOreID, it->position.x, it->position.y);
                        break;  // 找到并删除后退出
                    }
                }
            }

            break;  // 假设一次点击只能拾取一个物品
        }
    }
}

bool BossMapInteraction::checkPlayerPosition(const Vec2& playerPosition)
{
    // 检查玩家是否接触到碰撞对象
    for (const auto& collisionItem : collisionItems)
    {
        if (collisionItem.position.distance(playerPosition) < collisionThreshold)
        {
            // 玩家碰到了碰撞区域
            CCLOG("Player cannot pass through Collision Object ID: %d", collisionItem.id);
            return false;  // 阻止角色继续移动
        }
    }
}

void BossMapInteraction::PickUpInteraction(Item* item)
{
    // 显示拾取提示
    if (!Inventory::isFull)
    {
        auto label = Label::createWithTTF("You picked up: " + item->getName(), "fonts/arial.ttf", 24);
        label->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(label);
        label->runAction(Sequence::create(
            FadeOut::create(2.0f),
            RemoveSelf::create(),
            nullptr));

        // 将物品加入背包
        Inventory::addItem(item);
    }
    else
    {
        auto label = Label::createWithTTF("Inventory is full", "fonts/arial.ttf", 24);
        label->setPosition(Director::getInstance()->getVisibleSize() / 2);
        this->addChild(label);
        label->runAction(Sequence::create(
            FadeOut::create(2.0f),
            RemoveSelf::create(),
            nullptr));
    }
}