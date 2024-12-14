#include "MiniMap.h"
#include "cocos2d.h"
constexpr int SPEED = 2000;//移动速度

// 更新主控精灵位置
void MiniMap::UpdatePlayerPosition(const cocos2d::EventKeyboard::KeyCode keyCode)
{
    // 获取主控精灵新位置
    //cocos2d::Vec2& newPos = hero.Move(keyCode);
    cocos2d::Vec2 next_position = player->getPosition(), currentPos = player->getPosition();
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        next_position.y += SPEED * cocos2d::Director::getInstance()->getDeltaTime();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        next_position.y -= SPEED * cocos2d::Director::getInstance()->getDeltaTime();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        next_position.x -= SPEED * cocos2d::Director::getInstance()->getDeltaTime();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        next_position.x += SPEED * cocos2d::Director::getInstance()->getDeltaTime();
        break;
    default:
        break;
    }
    cocos2d::Vec2 newPos = next_position;

    // 是否能走
    bool walkable = true;

    // 获取碰撞检测的动态对象组
    auto collisionLayer = tiledMap->getObjectGroup("Collision");

    // 获取缩放比例
    auto scaleX = tiledMap->getScaleX();
    auto scaleY = tiledMap->getScaleY();

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

    // 获取当前可视区域原点坐标
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // 获取当前可视区域的大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 计算视窗中心的世界坐标
    cocos2d::Vec2 centralWorldPos = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);

    // 定义区域边界世界坐标
    float minWorldX = centralWorldPos.x - visibleSize.width / 4;
    float minWorldY = centralWorldPos.y - visibleSize.height / 4;
    float maxWorldX = centralWorldPos.x + visibleSize.width / 4;
    float maxWorldY = centralWorldPos.y + visibleSize.height / 4;

    // 如果能前往该坐标
    if (walkable) {
        // 更新主控坐标
        //hero.setPosition(newPos);
        // 设置偏移量
        auto offset = SPEED * cocos2d::Director::getInstance()->getDeltaTime();

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
        }
    }
    else {
        CCLOG("无法前往(%f,%f)", newPos.x, newPos.y);
    }
}
