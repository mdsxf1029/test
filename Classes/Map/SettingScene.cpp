#include "SettingScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "BackpackLayer.h"
#include <ui/UIButton.h>
#include "MiniMap.h"
USING_NS_CC;



bool Setting::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	// 创建一个父节点来包含地图和所有标签
	auto mapParentNode = Node::create();
	mapParentNode->setTag(100); // 设置父节点的 tag
	mapParentNode->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(mapParentNode);

	/*//创建背包按钮（使用 UIButton）
	auto backpackButton = ui::Button::create("backpack.png");  // 使用你自己的图标
	backpackButton->setPosition(Vec2(2000, -1000));  // 按钮位置
	backpackButton->addClickEventListener([this](Ref* sender) {

		this->openBackpack();  // 点击背包按钮时调用 openBackpack()
		});

	mapParentNode->addChild(backpackButton, 1);  // 将背包按钮添加到场景中
	

	*/
	

	//创建并添加背景到父节点
	auto bg = Sprite::create("Gold.png");
	bg->setPosition(Vec2::ZERO); // 相对于父节点的位置
	bg->setName("bgSprite");
	mapParentNode->addChild(bg);


	// 添加鼠标滚轮事件监听器
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseScroll = CC_CALLBACK_1(Setting::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
	
	
	// 创建背景管理实例
	_backgroundManager = new BackgroundManager(this);
	CCLOG("Showing popup with message: 1");  
	// 创建菜单项
	std::string fullPath = "Resources/maps"; 
	CCLOG("Full path to map: %s", fullPath.c_str());

	auto downtownMenuItem = createTextButton("Downtown", "fonts/Marker Felt.ttf", 300, "maps/downtown.tmx");
	auto castleMenuItem = createTextButton("Castle", "fonts/Marker Felt.ttf", 300, "maps/castle.tmx");
	auto goldMenuItem = createTextButton("Gold", "fonts/Marker Felt.ttf", 300, "maps/goldMap.tmx");
	CCLOG("Showing popup with message: 2");
	// 创建菜单
	auto menu = Menu::create(downtownMenuItem, castleMenuItem, goldMenuItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	mapParentNode->addChild(menu); // 将菜单添加到父节点

	// 设置按钮的位置（相对于父节点）
	downtownMenuItem->setPosition(Vec2(-500, -100));
	castleMenuItem->setPosition(Vec2(0, 500));
	goldMenuItem->setPosition(Vec2(3000, -1000));
	
	return true;
}

void Setting::disableBigMapScrolling()
{
	// 移除鼠标滚轮事件监听器
	_eventDispatcher->removeEventListenersForTarget(this);
}

void Setting::menuItemCallback1(Ref* sender, const std::string& backgroundImage)
{
	// 禁用 BigMap 的滚轮缩放
	disableBigMapScrolling();

	// 切换背景
	auto miniMapScene = MiniMap::createWithMap(backgroundImage, true);
	cocos2d::Director::getInstance()->replaceScene(miniMapScene);

	// 隐藏或移除 BigMap
	auto mapParentNode = this->getChildByTag(100); // 获取包含 BigMap 的父节点
	if (mapParentNode) {
		auto bgSprite = mapParentNode->getChildByName("bgSprite");
		if (bgSprite) {
			bgSprite->setVisible(false); // 或使用 mapParentNode->removeChild(bgSprite);
		}
	}

	// 隐藏菜单
	auto menuNode = this->getChildByTag(200); // 获取菜单节点
	if (menuNode) {
		menuNode->setVisible(false); // 隐藏菜单
		auto menuRef = dynamic_cast<Menu*>(menuNode);
		if (menuRef) {
			menuRef->setEnabled(false); // 禁用交互
		}
	}
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
	float scrollY = mouseEvent->getScrollY();

	// 获取父节点（包含地图和标签）
	auto mapParentNode = this->getChildByTag(100);
	if (mapParentNode) {
		// 获取当前缩放比例
		float currentScale = mapParentNode->getScale();

		// 根据滚轮方向调整缩放比例
		float newScale = currentScale + (scrollY > 0 ? 0.1f : -0.1f); // 上滑放大，下滑缩小
		newScale = std::max(0.5f, std::min(newScale, 5.0f)); // 限制缩放范围

		// 获取鼠标屏幕坐标
		Vec2 mousePositionScreen = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());

		// 将鼠标屏幕坐标转换为 OpenGL 坐标
		Vec2 mousePositionGL = Director::getInstance()->convertToGL(mousePositionScreen);

		// 将鼠标坐标转换为父节点的局部坐标
		Vec2 mousePositionLocalBeforeScale = mapParentNode->convertToNodeSpace(mousePositionGL);

		// 缩放父节点
		mapParentNode->setScale(newScale);

		// 获取缩放后的地图大小
		auto mapSize = mapParentNode->getContentSize() * newScale;

		// 将鼠标位置重新转换为缩放后的相对坐标
		Vec2 mousePositionLocalAfterScale = mapParentNode->convertToNodeSpace(mousePositionGL);

		// 计算鼠标缩放前后的位置差异
		Vec2 positionOffset = mousePositionLocalBeforeScale - mousePositionLocalAfterScale;

		// 获取当前地图的位置
		Vec2 currentMapPosition = mapParentNode->getPosition();

		// 更新地图位置，使鼠标位置保持在相同的位置
		Vec2 newMapPosition = currentMapPosition + positionOffset;

		// 获取屏幕可见区域
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();

		// 限制地图的位置，防止超出屏幕
		newMapPosition.x =origin.x+visibleSize.width-3100;
		
		newMapPosition.y = origin.y + visibleSize.height-2000;


		if ((currentMapPosition.x == (origin.x + visibleSize.width - 3100)) &&
			(currentMapPosition.y == origin.y + visibleSize.height - 2000))
		{
			mapParentNode->setPosition(mousePositionGL);
		}
		else
		{
			mapParentNode->setPosition(newMapPosition);
		}
	
	
	}
}

void Setting::openBackpack()
{
	// 创建背包对象并添加物品
	auto _backpack = new Backpack();  // 假设你已经在 Backpack 类中实现了物品的管理
	_backpack->addItem("HELMET");
	_backpack->addItem("ARMOR");
	_backpack->addItem("SHOES");
	_backpack->addItem("MAGIC_RING");
	_backpack->addItem("MAGIC_CRYSTAL");
	_backpack->addItem("MAGIC_SCROLL");
	/*
	_backpack->addItem("FISH");
	_backpack->addItem("FRUIT");
	_backpack->addItem("VEGETABLE");
	_backpack->addItem("HERB");
	_backpack->addItem("MEAT");
	_backpack->addItem("MUSHROOM");
	_backpack->addItem("RICE");
	_backpack->addItem("APPLE");
	_backpack->addItem("TREE");
	_backpack->addItem("WOOD");
	_backpack->addItem("GOLD_MINE");
	_backpack->addItem("STONE");
	_backpack->addItem("CHEST");
	*/
	// 创建背包层并设置背包数据
	auto backpackLayer = BackpackLayer::create();
	backpackLayer->setBackpack(_backpack);  // 将背包数据传递给背包层

	// 将背包层添加到场景中
	this->addChild(backpackLayer, 1000);  // 高 z-order 确保背包显示在上层

}





