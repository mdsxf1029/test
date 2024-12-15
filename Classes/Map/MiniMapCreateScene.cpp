#include "MiniMap.h"
#include "cocos2d.h"

cocos2d::Scene* MiniMap::createWithMap(const std::string& mapFile, bool fly)
{
	MiniMap* scene = new(std::nothrow) MiniMap(mapFile, fly);
	if (scene && scene->initWithMap(mapFile)) {
		scene->autorelease();
		scene->isFly = fly;
		scene->mapName = mapFile;
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return nullptr;
}

bool MiniMap::initWithMap(const std::string& mapFile)
{
	if (!Scene::init()) {
		return false;
	}
	// 获取当前可视区域的大小
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	// 获取当前可视区域原点坐标
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// 获取地图
	tiledMap = cocos2d::TMXTiledMap::create(mapFile);
	if (!tiledMap) {
		CCLOG("noMap");
		return false;
	}

	//设置缩放比例
	float scaleX = 3.0f;
	float scaleY = 3.0f;

	// 加载地图
	tiledMap->setScale(scaleX, scaleY);

	// 获取当前瓦片地图大小
	cocos2d::Size mapSize = tiledMap->getMapSize();

	// 获取瓦片地图瓦片大小
	auto tileSize = tiledMap->getTileSize();

	// 计算瓦片缩放后大小
	auto playerSize = tileSize;
	playerSize.width *= scaleX;
	playerSize.height *= scaleY;

	// 加载主控精灵
	player = cocos2d::Sprite::create("HelloWorld.png");

	// 设置主控精灵大小
	player->setContentSize(playerSize);

	// 获取主控精灵需要到达的逻辑坐标
	float bornPointX = 0.0f, bornPointY = 0.0f;

	// 创建对象层
	auto transportPoint = (isFly == true ? tiledMap->getObjectGroup("TransportPoint") : tiledMap->getObjectGroup("Boat"));

	// 获取传送位置的逻辑坐标
	if (transportPoint) {
		auto transportObject = (isFly == true ? transportPoint->getObject("Fly") : transportPoint->getObject("Boat"));
		bornPointX = transportObject["x"].asFloat();
		bornPointY = transportObject["y"].asFloat();
	}

	if (!bornPointX && !bornPointY)
		CCLOG("noBornPoint");

	// 计算主控精灵的世界坐标
	auto bornWorld = tiledMap->convertToWorldSpace(cocos2d::Vec2(bornPointX, bornPointY));

	// 计算视窗中心的世界坐标
	cocos2d::Vec2 centerWorldPosition = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);

	// 获取偏移量
	cocos2d::Vec2 offset = centerWorldPosition - bornWorld + cocos2d::Vec2(0.0f, -tileSize.height * scaleY);

	// 调整偏移量，以防边界出现在视窗内部
	if (offset.x > 0)
		offset.x = 0;
	else if (offset.x + mapSize.width * tileSize.width * scaleX < visibleSize.width)
		offset.x = visibleSize.width - mapSize.width * tileSize.width * scaleX;
	if (offset.y > 0)
		offset.y = 0;
	else if (offset.y + mapSize.height * tileSize.height * scaleY < visibleSize.height)
		offset.y = visibleSize.height - mapSize.height * tileSize.height * scaleY;

	// 调整主控精灵位置
	cocos2d::Vec2 playerPos = offset + bornWorld - cocos2d::Vec2(0.0f, -tileSize.height * scaleY);

	// 设置主控精灵位置
	player->setPosition(playerPos);
	tiledMap->setPosition(offset);

	// 把精灵添加到场景
	this->addChild(tiledMap);
	this->addChild(player);

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