#include "MiniMap.h"
#include "cocos2d.h"

// 确保给出的值在某个范围内，主要用于设置相机中心位置
template<typename T>
T clamp(const T& value, const T& min, const T& max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}

// 初始化
MiniMap::MiniMap(const std::string& map, bool fly)
{
	mapName = map;
	isFly = fly;
	tiledMap = nullptr;
	player = nullptr;
	keyboardListener = nullptr;
}

cocos2d::Scene* MiniMap::createScene()
{
	auto current_scene = cocos2d::Scene::create();
	auto map = MiniMap::create();
	current_scene->addChild(map);
	return current_scene;
}

bool MiniMap::init()
{
	if (!Scene::init()) {
		return false;
	}

	// 获取当前可视区域的大小
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	// 获取当前可视区域原点坐标
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// 获取地图
	tiledMap = cocos2d::TMXTiledMap::create("smallmap/wood.tmx");

	// 加载地图
	MiniMap::addChild(tiledMap);

	// 创建相机
	auto camera = cocos2d::Camera::create();
	this->addChild(camera);

	// 设置缩放比例
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	camera->setScaleX(scaleX);
	camera->setScaleY(scaleY);

	// 获取瓦片地图瓦片大小
	auto tileSize = tiledMap->getTileSize();

	// 计算瓦片缩放后大小
	auto playerSize = tileSize;
	playerSize.width *= scaleX;
	playerSize.height *= scaleY;

	// 加载主控精灵
	player = cocos2d::Sprite::create("CloseSelected.png");

	// 设置主控精灵大小
	player->setContentSize(playerSize);

	// 创建对象层
	auto objectLayer = tiledMap->getLayer("TransportPoint");
	
	// 获取主控精灵需要到达的逻辑坐标
	float bornPointX = 0.0f, bornPointY = 0.0f;
	if (objectLayer) {
		// 获取层的大小
		auto layerSize = objectLayer->getLayerSize();

		// 获取主控精灵需要到达的逻辑坐标
		float bornPointX = 0.0f, bornPointY = 0.0f;
		for (int y = 0; y < layerSize.height; ++y) { // 遍历每个瓦片
			for (int x = 0; x < layerSize.width; ++x) {
				// 获取瓦片的 GID
				int tileGID = objectLayer->getTileGIDAt(cocos2d::Vec2(x, y));

				// 检查 GID 是否有效
				if (tileGID != 0) {
					// 获取瓦片的所有属性
					auto properties = tiledMap->getPropertiesForGID(tileGID).asValueMap();

					//获取瓦片的type
					auto tileType = properties["type"].asString();

					// 判断该瓦片是否是目标瓦片
					if (isFly && tileType == "flyPoint") { // 传送方式
						bornPointX = properties["X"].asFloat();
						bornPointY = properties["Y"].asFloat();
					}
					else if (!isFly && tileType == "boatPoint") { // 划船方式
						bornPointX = properties["X"].asFloat();
						bornPointY = properties["Y"].asFloat();
					}
				}
			}
		}
	}
	if (!bornPointX && !bornPointY)
		CCLOG("没找到出生点");

	// 计算主控精灵的世界坐标
	float bornWorldX = bornPointX * tileSize.width * scaleX;
	float bornWorldY = bornPointY * tileSize.height * scaleY;

	// 设置主控精灵位置
	player->setPosition(cocos2d::Vec2(bornWorldX, bornWorldY));

	// 计算可视区域的实际尺寸
	float visibleWidth = visibleSize.width / scaleX;
	float visibleHeight = visibleSize.height / scaleY;

	// 计算相机中心位置
	float cameraX = clamp<float>(bornWorldX, visibleWidth / 2, tiledMap->getMapSize().width * tileSize.width - visibleWidth / 2);
	float cameraY = clamp<float>(bornWorldY, visibleHeight / 2, tiledMap->getMapSize().height * tileSize.height - visibleHeight / 2);

	// 设置相机的位置
	camera->setPosition(cocos2d::Vec2(cameraX,cameraY));

	// 设置键盘事件监听器
	StartListening();

	return true;
}

// 设置键盘事件监听器
void MiniMap::StartListening()
{
	if (!keyboardListener) { // 确保没有重复添加监听器
		// 创建并保存键盘事件监听器
		keyboardListener = cocos2d::EventListenerKeyboard::create();

		// 设置键盘按下事件的回调函数
		keyboardListener->onKeyPressed = CC_CALLBACK_2(MiniMap::OnKeyPressed, this);

		// 设置键盘释放事件的回调函数
		keyboardListener->onKeyReleased = CC_CALLBACK_2(MiniMap::OnKeyReleased, this);

		// 添加到事件调度器中
		_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
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
		UpdatePlayerPosition(keyCode);
		break;
	default:
		break;
	}
}

// 按键释放的回调函数（暂时好像不需要，先放着吧）
void MiniMap::OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
}

// 清理监听器
void MiniMap::StopListening()
{
	if (keyboardListener) {
		_eventDispatcher->removeEventListener(keyboardListener);
		keyboardListener = nullptr; // 清空指针
	}
}


/*
// 划船去相邻地图
void MiniMap::BoatingToMap(const std::string& objectMap)
{
	// 创建将要前往的地图对象
	MiniMap object(objectMap, false);

	// 加载地图
	object.createScene();

}*/

/*
bool MiniMap::SwitchBetweenSmallMaps(const std::string& objectMap, const bool walk)
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
// 我安装事件监听器，监听玩家移动，调用Player类的计算函数，传移动方向参数，计算函数返给我新的坐标。
// 我判断新坐标是否可到达，如可，更新Sprite的png显示，并调用Player类的更新函数，让Player更新人物属性。
void MiniMap::Pan(const cocos2d::Vec2& roleWorldPosition, const cocos2d::EventKeyboard::KeyCode keyCode)
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
*/

void MiniMap::UpdatePlayerPosition(const cocos2d::EventKeyboard::KeyCode keyCode)
{
	// 函数实现代码
}
