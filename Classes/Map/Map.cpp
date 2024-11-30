#include "Map.h"
#include "cocos2d.h"

Map::Map(const std::string& name) :mapName(name)
{
	std::string N = mapName + ".tmx";
	tiledMap = cocos2d::TMXTiledMap::create(N);
}

cocos2d::Scene* Map::createScene()
{
	auto current_scene = cocos2d::Scene::create();
	auto map_layer = Map::create();
	current_scene->addChild(map_layer);
	return current_scene;
}

bool Map::init()
{
	if (!Layer::init()) {
		return false;
	}
	// 获取当前可视区域的大小
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	// 获取当前可视区域原点坐标
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	// 加载地图
	Map::addChild(tiledMap);
	return true;
}

bool Map::SwitchBetweenSmallMaps(const std::string& objectMap)
{
	
	// 如果要前往迷宫或战斗，保留上一次的地图
	if (objectMap == "maze" || objectMap == "battle") {
		Map newMap(objectMap);
		auto newScene = newMap.createScene();
		cocos2d::Director::getInstance()->pushScene(newScene);
	}
	// 如果从迷宫或战斗回来，回到上一次地图
	else if (this->mapName == "maze" || this->mapName == "battle") {
		cocos2d::Director::getInstance()->popScene();
	}
	// 如果只是单纯的跳转，则释放掉上一次的地图
	else {
		Map newMap(objectMap);
		auto newScene = newMap.createScene();
		cocos2d::Director::getInstance()->replaceScene(newScene);
	}
	return true;
}

void Map::Pan(const cocos2d::Vec2& roleWorldPosition, const cocos2d::EventKeyboard::KeyCode keyCode)
{
	// 获取当前可见区域的大小
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	// 获取当前可视区域原点坐标
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	// 定义世界边界坐标
	int minWorldX = origin.x;
	int minWorldY = origin.y;
	int maxWorldX = origin.x + visibleSize.width;
	int maxWorldY = origin.y + visibleSize.height;

	// 获取当前瓦片地图坐标
	cocos2d::Vec2 mapPosition = tiledMap->getPosition();
	// 获取当前瓦片地图大小
	cocos2d::Size mapSize = tiledMap->getMapSize();
	// 获取当前瓦片地图瓦片大小
	cocos2d::Size tileSize = tiledMap->getTileSize();
	// 定义瓦片地图边界坐标
	int minTileX = 0;
	int minTileY = 0;
	int maxTileX = mapSize.width - 1;
	int maxTileY = mapSize.height - 1;
	// 通过世界坐标获取精灵在瓦片层中的相对坐标
	cocos2d::Vec2 tilePosInMap = tiledMap->convertToNodeSpace(roleWorldPosition);
	// 计算精灵的逻辑坐标
	int roleTileX = tilePosInMap.x / tileSize.width;  // 精灵的 X 逻辑坐标
	int roleTileY = tilePosInMap.y / tileSize.height; // 精灵的 Y 逻辑坐标

	// 当精灵走到世界边界处，且未抵达地图边界处，才会滑动地图
	// 精灵向左
	if (roleWorldPosition.x <= minWorldX && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW && roleTileX > 0) {
		cocos2d::Vec2 newMapPosition = cocos2d::Vec2(mapPosition.x + tileSize.width, mapPosition.y);
		tiledMap->setPosition(newMapPosition);
	}
	// 精灵向右
	else if (roleWorldPosition.x >= maxWorldX && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW && roleTileX < maxTileX) {
		cocos2d::Vec2 newMapPosition = cocos2d::Vec2(mapPosition.x - tileSize.width, mapPosition.y);
		tiledMap->setPosition(newMapPosition);
	}
	// 精灵向上
	else if (roleWorldPosition.x >= maxWorldY && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW && roleTileY < maxTileY) {
		cocos2d::Vec2 newMapPosition = cocos2d::Vec2(mapPosition.x, mapPosition.y-tileSize.height);
		tiledMap->setPosition(newMapPosition);
	}
	// 精灵向下
	else if (roleWorldPosition.x <= minWorldY && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW && roleTileY > 0) {
		cocos2d::Vec2 newMapPosition = cocos2d::Vec2(mapPosition.x, mapPosition.y+tileSize.height);
		tiledMap->setPosition(newMapPosition);
	}
}
