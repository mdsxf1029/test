#include "SettingScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
USING_NS_CC;

bool Setting::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 创建并添加背景
	auto bg = Sprite::create("BigMap.png");
	float x = origin.x + visibleSize.width / 2;
	float y = origin.y + visibleSize.height / 2;
	bg->setPosition(Vec2(x, y));
	bg->setName("bgSprite"); // 设置名字为 "bgSprite"
	this->addChild(bg);

	// 创建背景管理实例
	_backgroundManager = new BackgroundManager(this);

	// 创建菜单项
	auto downtownMenuItem = createTextButton("Downtown", "fonts/Marker Felt.ttf", 300, "downtown.png");
	auto castleMenuItem = createTextButton("Castle", "fonts/Marker Felt.ttf", 300, "castle.png");
	auto goldMenuItem = createTextButton("Gold", "fonts/Marker Felt.ttf", 300, "gold.png");
	auto woodMenuItem = createTextButton("Wood", "fonts/Marker Felt.ttf", 300, "wood.png");
	auto waterMenuItem = createTextButton("Water", "fonts/Marker Felt.ttf", 300, "water.png");
	auto fireMenuItem = createTextButton("Fire", "fonts/Marker Felt.ttf", 300, "fire.png");
	auto soilMenuItem = createTextButton("Soil", "fonts/Marker Felt.ttf", 300, "soil.png");

	// 创建菜单
	auto menu = Menu::create(downtownMenuItem, castleMenuItem, goldMenuItem, woodMenuItem, waterMenuItem, fireMenuItem, soilMenuItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	menu->setTag(200); // 设置菜单的 tag
	this->addChild(menu);

	// 设置按钮的位置
	downtownMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 500, origin.y + visibleSize.height / 2 - 100));
	castleMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 500));
	goldMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 2000, origin.y + visibleSize.height / 2 + 500));
	woodMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2 + 1500, origin.y + visibleSize.height / 2 + 500));
	waterMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 1500, origin.y + visibleSize.height / 2 - 1500));
	fireMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 500, origin.y + visibleSize.height / 2 + 1500));
	soilMenuItem->setPosition(Vec2(origin.x + visibleSize.width / 2 + 500, origin.y + visibleSize.height / 2 - 1500));

	return true;
}


void Setting::menuItemCallback1(Ref* sender, const std::string& backgroundImage)
{
	// 切换背景
	_backgroundManager->setBackground(backgroundImage);

	// 移除背景精灵
	this->removeChildByName("bgSprite");

	// 禁用并移除菜单
	auto menuNode = this->getChildByTag(200); // 获取菜单节点
	if (menuNode) {
		auto menuRef = dynamic_cast<Menu*>(menuNode);
		if (menuRef) {
			menuRef->setEnabled(false); // 禁用交互
		}
		this->removeChild(menuNode); // 移除菜单节点
	}

	// 添加鼠标滚轮事件监听器
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseScroll = CC_CALLBACK_1(Setting::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}


cocos2d::MenuItemLabel* Setting::createTextButton(const std::string& text, const std::string& fontFile, int fontSize, const std::string& backgroundImage)
{
	// 创建文字标签
	auto label = Label::createWithTTF(text, fontFile, fontSize);

	// 设置文字颜色
	label->setTextColor(Color4B::BLACK); 

	// 创建文字按钮，并绑定回调函数
	auto button = MenuItemLabel::create
	(label, [this, backgroundImage](Ref* sender) 
	{
		this->menuItemCallback1(sender, backgroundImage);
	}
	);

	return button;
}

//小地图的放大缩小功能
void Setting::onMouseScroll(cocos2d::Event* event) {
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
	float scrollY = mouseEvent->getScrollY(); // 获取鼠标滚轮的滚动值

	auto map = this->getChildByTag(100); // 获取地图节点
	if (map) {
		// 获取当前缩放比例
		float currentScale = map->getScale();

		// 根据滚轮方向调整缩放比例
		float newScale = currentScale + (scrollY > 0 ? 0.1f : -0.1f); // 上滑放大，下滑缩小
		newScale = std::max(0.5f, std::min(newScale, 5.0f)); // 限制缩放范围

		// 获取鼠标在屏幕上的位置
		Vec2 mousePositionScreen = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());

		// 将鼠标屏幕坐标转换为 OpenGL 坐标
		Vec2 mousePositionGL = Director::getInstance()->convertToGL(mousePositionScreen);

		// 将 OpenGL 坐标转换为地图的局部坐标
		Vec2 mousePositionLocal = map->convertToNodeSpace(mousePositionGL);

		// 缩放地图
		map->setScale(newScale);

		// 重新计算地图局部坐标在新缩放比例下对应的世界坐标
		Vec2 mousePositionWorldAfterScale = map->convertToWorldSpace(mousePositionLocal);

		// 调整地图的位置，确保鼠标位置保持固定
		Vec2 mapPosition = map->getPosition();
		Vec2 offset = mousePositionGL - mousePositionWorldAfterScale;
		Vec2 newMapPosition = mapPosition + offset;

		// 获取地图缩放后的大小
		auto mapSize = map->getContentSize() * newScale;

		// 获取屏幕的可视区域
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();

		// 计算边界限制
		float minX = origin.x + visibleSize.width - mapSize.width / 2;
		float maxX = origin.x + mapSize.width / 2;
		float minY = origin.y + visibleSize.height - mapSize.height / 2;
		float maxY = origin.y + mapSize.height / 2;

		// 限制地图的位置
		newMapPosition.x = std::max(minX, std::min(maxX, newMapPosition.x));
		newMapPosition.y = std::max(minY, std::min(maxY, newMapPosition.y));

		map->setPosition(newMapPosition);
	}
}

