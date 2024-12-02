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

bool Map::SwitchBetweenSmallMaps(const std::string& objectMap, const bool walk)
{
	// 如果要前往迷宫或战斗，保留上一次的地图
	if (objectMap == "maze" || objectMap == "battle") {
		// 获取可见区域的大小
		auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

		// 创建过渡场景的背景精灵
		auto transitionSprite = cocos2d::Sprite::create("GameTransition.png");

		// 设置精灵的大小与屏幕一样大
		transitionSprite->setContentSize(visibleSize);

		// 设置精灵的位置为屏幕中心
		transitionSprite->setPosition(visibleSize / 2);

		// 创建过渡场景
		cocos2d::Scene* transitionScene = cocos2d::Scene::create();

		// 将背景精灵添加到过渡场景中
		transitionScene->addChild(transitionSprite);

		// 添加过渡动画
		auto transition = cocos2d::TransitionSlideInT::create(0.5f, transitionScene);

		// 把上次地图压入栈中，展示过渡图像
		cocos2d::Director::getInstance()->pushScene(transition);

		// 创建新场景
		Map newMap(objectMap);
		auto newScene = newMap.createScene();

		// 添加过渡动画
		auto newTransition = cocos2d::TransitionSlideInT::create(0.5f, newScene);

		// 加载新场景，释放掉过渡场景
		cocos2d::Director::getInstance()->replaceScene(newScene);
	}
	// 如果从迷宫或战斗回来，回到上一次地图
	else if (this->mapName == "maze" || this->mapName == "battle") {
		cocos2d::Director::getInstance()->popScene();
	}
	// 如果是主线任务地图之间的跳转
	else {
		// 获取可见区域的大小
		auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

		// 创建过渡场景的背景精灵
		cocos2d::Sprite* transitionSprite;
		if (walk == true) // 相邻地图
			transitionSprite = cocos2d::Sprite::create("GoByWalking.png");
		else // 锚点传送
			transitionSprite = cocos2d::Sprite::create("GoByPortal.png");

		// 设置精灵的大小与屏幕一样大
		transitionSprite->setContentSize(visibleSize);

		// 设置精灵的位置为屏幕中心
		transitionSprite->setPosition(visibleSize / 2);

		// 创建过渡场景
		cocos2d::Scene* transitionScene = cocos2d::Scene::create();

		// 将背景精灵添加到过渡场景中
		transitionScene->addChild(transitionSprite);

		// 添加过渡动画
		auto transition = cocos2d::TransitionSlideInL::create(0.5f, transitionScene);

		// 把上次地图压入栈中，展示过渡图像
		cocos2d::Director::getInstance()->replaceScene(transition);

		// 创建新场景
		Map newMap(objectMap);
		auto newScene = newMap.createScene();

		// 添加过渡动画
		auto newTransition = cocos2d::TransitionSlideInT::create(0.5f, newScene);

		// 加载新场景，释放掉过渡场景
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

	// 获取当前瓦片地图坐标
	cocos2d::Vec2 mapPosition = tiledMap->getPosition();

	// 获取当前瓦片地图大小
	cocos2d::Size mapSize = tiledMap->getMapSize();

	// 获取当前瓦片地图瓦片大小
	cocos2d::Size tileSize = tiledMap->getTileSize();

	// 定义瓦片地图边界坐标
	float minTileX = 0.0f;
	float minTileY = 0.0f;
	float maxTileX = mapSize.width - 1;
	float maxTileY = mapSize.height - 1;

	// 定义世界中心坐标
	float centralWorldX = (origin.x + visibleSize.width) / 2;
	float centralWorldY = (origin.y + visibleSize.height) / 2;

	// 定义区域边界坐标
	float minWorldX = centralWorldX - visibleSize.width / 4;
	float minWorldY = centralWorldY - visibleSize.height / 4;
	float maxWorldX = centralWorldX + visibleSize.width / 4;
	float maxWorldY = centralWorldY + visibleSize.height / 4;

	// 通过世界坐标获取精灵在瓦片层中的相对坐标
	cocos2d::Vec2 tilePosInMap = tiledMap->convertToNodeSpace(roleWorldPosition);

	// 计算精灵的逻辑坐标
	float roleTileX = tilePosInMap.x / tileSize.width;  // 精灵的 X 逻辑坐标
	float roleTileY = tilePosInMap.y / tileSize.height; // 精灵的 Y 逻辑坐标

	// 退出游戏
	if ((mapName == "maze" || mapName == "battle") && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_Q) {
		// 调交互系统的对话框，再给我返回一个值表示是否退出？
		
		// 如果确定退出，调用小地图转换
		SwitchBetweenSmallMaps("lastMap", false);
	}

	// 当精灵走到给定的世界区域边界处，且未抵达地图边界处，才会滑动地图
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
