#include "GoldWoodSoil.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "Map/MiniMap.h"
USING_NS_CC;

bool Setting3::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();										   // 获取可见区域的大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();											   // 获取可见区域的原点

	/*创建一个父节点来包含地图和所有标签*/ 
	auto mapParentNode = Node::create();																   // 创建一个父节点
	mapParentNode->setTag(100);																			   // 设置父节点的 tag
	mapParentNode->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2)); // 设置父节点的位置
	this->addChild(mapParentNode);																		   // 将父节点添加到场景

	/*创建并添加背景到父节点*/ 
	auto bg = Sprite::create("GoldWoodSoil.png");														   // 创建背景精灵
	bg->setPosition(Vec2::ZERO);																		   // 相对于父节点的位置
	bg->setName("bgSprite");																			   // 设置背景精灵的名字
	mapParentNode->addChild(bg);																		   // 将背景精灵添加到父节点

	/*添加鼠标滚轮事件监听器*/ 
	auto mouseListener = EventListenerMouse::create();													   // 创建鼠标事件监听器
	mouseListener->onMouseScroll = CC_CALLBACK_1(Setting3::onMouseScroll, this);						   // 设置鼠标滚轮事件回调函数
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);					       // 添加鼠标滚轮事件监听器
	_backgroundManager = new BackgroundManager(this);													   // 创建背景管理实例
	/*创建菜单项*/ 
	auto downtownMenuItem = createTextButton("Downtown", "fonts/Marker Felt.ttf", 80, "smallmap/village.tmx");	 // 创建菜单项，
	auto castleMenuItem = createTextButton("Castle", "fonts/Marker Felt.ttf", 80, "smallmap/castle.tmx");		 // 传入参数：文字，字体，字体大小，背景图片
	auto soilMenuItem = createTextButton("Soil", "fonts/Marker Felt.ttf", 80, "smallmap/earth.tmx");
	auto woodMenuItem = createTextButton("Wood", "fonts/Marker Felt.ttf", 80, "smallmap/wood.tmx");
	auto goldMenuItem = createTextButton("Gold", "fonts/Marker Felt.ttf", 80, "smallmap/gold1.tmx");

	/*创建菜单*/ 
	auto menu = Menu::create(downtownMenuItem, castleMenuItem, soilMenuItem, woodMenuItem, goldMenuItem, nullptr);// 创建菜单，传入参数：菜单项，空指针
	menu->setPosition(Vec2::ZERO);																				  // 设置菜单的位置
	mapParentNode->addChild(menu);																				  // 将菜单添加到父节点

	/*设置按钮的位置（相对于父节点）*/ 
	downtownMenuItem->setPosition(Vec2(-100, -2.22));														      //设置菜单项的位置 下同
	castleMenuItem->setPosition(Vec2(0, 61.11));
	soilMenuItem->setPosition(Vec2(-800, 11.11));
	woodMenuItem->setPosition(Vec2(-300, -455.55));
	goldMenuItem->setPosition(Vec2(600, -132.22));

	return true;
}
cocos2d::Scene* Setting3::createScene()																			  // 创建场景
{
	auto scene = Setting3::create();																			  // 创建场景		
	return scene;																								  // 返回场景
}
void Setting3::disableBigMapScrolling()																			  // 禁用大地图滚动
{
	_eventDispatcher->removeEventListenersForTarget(this);														  // 移除鼠标滚轮事件监听器
}

void Setting3::menuItemCallback1(Ref* sender, const std::string& backgroundImage)
{
	disableBigMapScrolling();																// 禁用大地图滚动											

	MiniMap* miniMap = new MiniMap();														// 创建 MiniMap 实例
	if (miniMap)																			// 如果 MiniMap 实例创建成功
	{
		miniMap->autorelease();																// 释放 MiniMap 实例
		miniMap->FlyToMap(backgroundImage);													// 跳转到指定地图
	}													

	/*隐藏或移除 BigMap*/ 
	auto mapParentNode = this->getChildByTag(100);											// 获取包含 BigMap 的父节点
	if (mapParentNode) {																	// 如果父节点存在
		auto bgSprite = mapParentNode->getChildByName("bgSprite");							// 获取背景精灵
		if (bgSprite) {																		// 如果背景精灵存在
			bgSprite->setVisible(false);													// 或使用 mapParentNode->removeChild(bgSprite);
		}
	}

	/*隐藏菜单*/ 
	auto menuNode = this->getChildByTag(200);												// 获取菜单节点
	if (menuNode) {																			// 如果菜单节点存在
		menuNode->setVisible(false);														// 隐藏菜单
		auto menuRef = dynamic_cast<Menu*>(menuNode);										// 将菜单节点转换为菜单
		if (menuRef) {																		// 如果菜单存在
			menuRef->setEnabled(false);														// 禁用交互
		}
	}
}


cocos2d::MenuItemLabel* Setting3::createTextButton(const std::string& text, const std::string& fontFile, int fontSize, const std::string& backgroundImage)
{
	auto label = Label::createWithTTF(text, fontFile, fontSize);							// 创建文字标签
	label->setTextColor(Color4B::BLACK);													// 设置文字颜色									

	/*创建文字按钮，并绑定回调函数*/ 
	auto button = MenuItemLabel::create                                                     //创建文字按钮
	(label, [this, backgroundImage](Ref* sender)											// 设置回调函数
		{
			this->menuItemCallback1(sender, backgroundImage);								// 这里传入的是背景图片
		}
	);

	return button;
}

/*小地图的放大缩小功能*/
void Setting3::onMouseScroll(cocos2d::Event* event) {
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);								// 获取鼠标事件
	float scrollY = mouseEvent->getScrollY();												// 获取鼠标滚轮的滚动值
	auto mapParentNode = this->getChildByTag(100);											// 获取包含 BigMap 的父节点

	if (!mapParentNode) return;																// 如果父节点不存在，直接返回

	/* 获取当前缩放和新的缩放值*/
	float currentScale = mapParentNode->getScale();											// 获取当前缩放值
	float scaleChange = scrollY > 0 ? 0.1f : -0.1f;											// 设置缩放变化值
	float newScale = currentScale + scaleChange;											// 计算新的缩放值
	newScale = std::max(0.5f, std::min(newScale, 5.0f));									// 限制缩放范围
	if (std::abs(newScale - currentScale) < 0.001f) return;									// 如果缩放值没有改变，直接返回

	/*平滑缩放效果*/ 
	mapParentNode->stopAllActions();														// 停止所有动作
	auto scaleTo = ScaleTo::create(0.1f, newScale);											// 创建缩放动作
	auto easeAction = EaseOut::create(scaleTo, 2.0f);										// 创建缓动动作
	mapParentNode->runAction(easeAction);													// 执行动作

	/*获取屏幕边界*/ 
	auto visibleSize = Director::getInstance()->getVisibleSize();							// 获取可见区域的大小
	auto origin = Director::getInstance()->getVisibleOrigin();								// 获取可见区域的原点

	/*确保位置在有效范围内*/ 
	Vec2 currentPos = mapParentNode->getPosition();											// 获取当前位置
	float minX = origin.x + visibleSize.width - 3100;										// 计算最小 x 坐标
	float minY = origin.y + visibleSize.height - 2000;										// 计算最小 y 坐标

	currentPos.x = std::max(currentPos.x, minX);											// 限制 x 坐标
	currentPos.y = std::max(currentPos.y, minY);											// 限制 y 坐标

	mapParentNode->setPosition(currentPos);
}
