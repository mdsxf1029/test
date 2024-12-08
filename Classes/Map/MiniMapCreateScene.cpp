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
	tiledMap = cocos2d::TMXTiledMap::create(map);
	player = cocos2d::Sprite::create("player.png");
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

	// 加载地图
	MiniMap::addChild(tiledMap);

	// 创建相机
	auto camera = cocos2d::Camera::create();
	this->addChild(camera);

	// 设置缩放比例
	float scaleX = 4.0f;
	float scaleY = 4.0f;
	camera->setScaleX(scaleX);
	camera->setScaleY(scaleY);

	// 获取瓦片地图瓦片大小
	cocos2d::Size tileSize = tiledMap->getTileSize();

	// 计算瓦片缩放后大小
	cocos2d::Size playerSize = tileSize;
	playerSize.width *= scaleX;
	playerSize.height *= scaleY;

	// 设置主控精灵大小
	player->setContentSize(playerSize);

	// 创建对象层
	cocos2d::TMXLayer* objectLayer = tiledMap->getLayer("Object");

	// 获取层的大小
	auto layerSize = objectLayer->getLayerSize();

	// 获取主控精灵需要到达的逻辑坐标
	float bornPointX, bornPointY;
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
