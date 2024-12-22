#include "GoldWoodSoilWater.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "Map/MiniMap.h"
USING_NS_CC;

//初始化
bool Setting4::init()																						
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();														//获取可见区域的大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();															//获取可见区域的原点

	// 创建一个父节点来包含地图和所有标签
	auto mapParentNode = Node::create();																				//创建父节点
	mapParentNode->setTag(100);																							// 设置父节点的 tag
	mapParentNode->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));				//设置父节点的位置
	this->addChild(mapParentNode);																						//将父节点添加到场景

	// 创建并添加背景到父节点
	auto bg = Sprite::create("GoldWoodSoilWater.png");																	//创建背景
	bg->setPosition(Vec2::ZERO);																						// 相对于父节点的位置	
	bg->setName("bgSprite");																							//设置背景的名字
	mapParentNode->addChild(bg);																						//将背景添加到父节点

	// 添加鼠标滚轮事件监听器
	auto mouseListener = EventListenerMouse::create();																	//创建鼠标滚轮事件监听器
	mouseListener->onMouseScroll = CC_CALLBACK_1(Setting4::onMouseScroll, this);										//设置鼠标滚轮事件监听器的回调函数
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);										//添加鼠标滚轮事件监听器

	_backgroundManager = new BackgroundManager(this);																	//创建背景管理实例
	// 创建菜单项
	auto downtownMenuItem = createTextButton("Downtown", "fonts/Marker Felt.ttf", 80, "smallmap/village.tmx");					//创建菜单项，下同	
	auto castleMenuItem = createTextButton("Castle", "fonts/Marker Felt.ttf", 80, "smallmap/castle.tmx");
	auto waterMenuItem = createTextButton("Water", "fonts/Marker Felt.ttf", 80, "smallmap/whole3.tmx");
	auto soilMenuItem = createTextButton("Soil", "fonts/Marker Felt.ttf", 80, "smallmap/earth.tmx");
	auto woodMenuItem = createTextButton("Wood", "fonts/Marker Felt.ttf", 80, "smallmap/wood.tmx");
	auto goldMenuItem = createTextButton("Gold", "fonts/Marker Felt.ttf", 80, "smallmap/gold1.tmx");
	// 创建菜单
	auto menu = Menu::create(downtownMenuItem, castleMenuItem, waterMenuItem, soilMenuItem, woodMenuItem, goldMenuItem, nullptr);//创建菜单
	menu->setPosition(Vec2::ZERO);																								 //设置菜单的位置
	mapParentNode->addChild(menu);																								 // 将菜单添加到父节点

	// 设置按钮的位置（相对于父节点）
	downtownMenuItem->setPosition(Vec2(-100, -2.22));														                                      //设置菜单项的位置 下同
	castleMenuItem->setPosition(Vec2(0, 61.11));
	soilMenuItem->setPosition(Vec2(-800, 11.11));
	woodMenuItem->setPosition(Vec2(-300, -455.55));
	waterMenuItem->setPosition(Vec2(-500, 566.66));
	goldMenuItem->setPosition(Vec2(600, -132.22));
	return true;
}
cocos2d::Scene* Setting4::createScene()
{
	auto scene = Setting4::create();																			    // 创建场景		
	return scene;
}
void Setting4::disableBigMapScrolling()
{
	_eventDispatcher->removeEventListenersForTarget(this);																// 移除鼠标滚轮事件监听器
}

void Setting4::menuItemCallback1(Ref* sender, const std::string& backgroundImage)
{
	disableBigMapScrolling();																							// 禁用 BigMap 的滚轮缩放

	MiniMap* miniMap = new MiniMap();																	      // 创建 MiniMap 实例
	if (miniMap)
	{
		miniMap->autorelease();																				  // 释放 MiniMap 实例
		miniMap->FlyToMap(backgroundImage);																	  // 跳转到指定地图
	}														// 设置背景

	// 隐藏或移除 BigMap
	auto mapParentNode = this->getChildByTag(100);																		// 获取包含 BigMap 的父节点
	if (mapParentNode) {
		auto bgSprite = mapParentNode->getChildByName("bgSprite");														// 获取背景精灵
		if (bgSprite) {
			bgSprite->setVisible(false);																				//使得背景精灵不可见
		}
	}

	// 隐藏菜单
	auto menuNode = this->getChildByTag(200);																			// 获取菜单节点
	if (menuNode) {
		menuNode->setVisible(false);																					// 隐藏菜单
		auto menuRef = dynamic_cast<Menu*>(menuNode);																	// 转换为 Menu 类型
		if (menuRef) {
			menuRef->setEnabled(false);																					// 禁用交互
		}
	}
}


cocos2d::MenuItemLabel* Setting4::createTextButton(const std::string& text, const std::string& fontFile, int fontSize, const std::string& backgroundImage)
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
void Setting4::onMouseScroll(cocos2d::Event* event) {
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
	float scrollY = mouseEvent->getScrollY();
	auto mapParentNode = this->getChildByTag(100);

	if (!mapParentNode) return;

	// 获取当前缩放和新的缩放值
	float currentScale = mapParentNode->getScale();
	float scaleChange = scrollY > 0 ? 0.1f : -0.1f;
	float newScale = currentScale + scaleChange;
	// 限制缩放范围
	newScale = std::max(0.5f, std::min(newScale, 5.0f));

	// 如果缩放值没有改变，直接返回
	if (std::abs(newScale - currentScale) < 0.001f) return;

	// 平滑缩放效果
	mapParentNode->stopAllActions();
	auto scaleTo = ScaleTo::create(0.1f, newScale);
	auto easeAction = EaseOut::create(scaleTo, 2.0f);
	mapParentNode->runAction(easeAction);

	// 获取屏幕边界
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// 确保位置在有效范围内
	Vec2 currentPos = mapParentNode->getPosition();
	float minX = origin.x + visibleSize.width - 3100;
	float minY = origin.y + visibleSize.height - 2000;

	currentPos.x = std::max(currentPos.x, minX);
	currentPos.y = std::max(currentPos.y, minY);

	mapParentNode->setPosition(currentPos);
}





