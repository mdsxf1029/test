#include "BaseMap.h"

USING_NS_CC;

BaseMap::BaseMap()
    : tiledMap(nullptr), isExplored(false), playerPosition(Vec2::ZERO) {}

BaseMap::~BaseMap() {}

void BaseMap::loadMap(const std::string& mapFile) {
    // 加载 TMX 地图文件
    tiledMap = TMXTiledMap::create(mapFile);
    if (tiledMap) {
        this->addChild(tiledMap);
    }
    else {
        CCLOG("Failed to load map: %s", mapFile.c_str());
    }

    // 初始化交互点（可以通过 TMX 的对象层获取）
    auto objectGroup = tiledMap->getObjectGroup("Objects");
    if (objectGroup) {
        auto objects = objectGroup->getObjects();
        for (const auto& obj : objects) {
            auto dict = obj.asValueMap();
            std::string name = dict["name"].asString();
            float x = dict["x"].asFloat();
            float y = dict["y"].asFloat();
            locationPoints[name] = Vec2(x, y);
        }
    }
}

void BaseMap::handleInteraction(const Vec2& position) {
    // 检查角色是否接近某个交互点
    for (const auto& point : locationPoints) {
        if (position.distance(point.second) < 32.0f) { // 距离小于 32 像素
            CCLOG("Interacting with: %s", point.first.c_str());
            // 子类可以重写此函数实现具体交互逻辑
        }
    }
}

void BaseMap::updateExploration(const Vec2& position) {
    // 当角色移动到某个区域时标记地图为已探索
    if (!isExplored) {
        CCLOG("Map is now explored!");
        isExplored = true;
    }
}

void BaseMap::setPlayerPosition(const Vec2& position) {
    playerPosition = position;
    // 更新角色在地图中的位置
    if (tiledMap) {
        auto playerSprite = dynamic_cast<cocos2d::Sprite*>(this->getChildByName("player"));
        if (playerSprite != nullptr) {
            playerSprite->setPosition(position);
        }

    }
}

Vec2 BaseMap::getPlayerPosition() const {
    return playerPosition;
}
