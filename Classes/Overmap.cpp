#include "Overmap.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "Map/MiniMap.h"
#include"BossScene.h"
USING_NS_CC;

bool Setting6::init()																						//初始化
{
	if (!Scene::init())																						//调用基类的初始化函数 如果场景初始化失败
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();											//获取可见区域的大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();												//获取可见区域的原点

	/* 创建一个父节点来包含地图和所有标签*/
	auto mapParentNode = Node::create();																	//创建一个节点
	mapParentNode->setTag(100);																				// 设置父节点的 tag
	mapParentNode->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));	//设置节点的位置	
	this->addChild(mapParentNode);																			//将节点添加到场景中
	 
	/*创建并添加背景到父节点*/ 
	auto bg = Sprite::create("GoldWoodSoilWaterFire.png");													//创建一个精灵
	bg->setPosition(Vec2::ZERO);																			// 相对于父节点的位置  相对位置
	bg->setName("bgSprite");																				//设置精灵的名字
	mapParentNode->addChild(bg);																			//将精灵添加到节点中

	/*添加鼠标滚轮事件监听器*/ 
	auto mouseListener = EventListenerMouse::create();														//创建一个鼠标事件监听器
	mouseListener->onMouseScroll = CC_CALLBACK_1(Setting6::onMouseScroll, this);							//设置鼠标滚轮事件监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);							//添加鼠标滚轮事件监听器

	/*创建菜单项*/ 
	auto downtownMenuItem = createTextButton("Downtown", "fonts/Marker Felt.ttf", 80, "smallmap/village.tmx");		//创建一个菜单项   下列均为菜单项
	auto castleMenuItem = createTextButton("Castle", "fonts/Marker Felt.ttf", 80, "smallmap/castle.tmx");
	auto soilMenuItem = createTextButton("Soil", "fonts/Marker Felt.ttf", 80, "smallmap/earth.tmx");
	auto fireMenuItem = createTextButton("Fire", "fonts/Marker Felt.ttf", 80, "smallmap/fire.tmx");
	auto woodMenuItem = createTextButton("Wood", "fonts/Marker Felt.ttf", 80, "smallmap/wood.tmx");
	auto waterMenuItem = createTextButton("Water", "fonts/Marker Felt.ttf", 80, "smallmap/whole3.tmx");
	auto goldMenuItem = createTextButton("Gold", "fonts/Marker Felt.ttf", 80, "smallmap/gold1.tmx");
	auto bossMenuItem = createTextButton("Boss", "fonts/Marker Felt.ttf", 80, "smallmap/boss.tmx");

	/*创建菜单*/ 
	auto menu = Menu::create(downtownMenuItem, castleMenuItem, soilMenuItem, fireMenuItem, woodMenuItem, waterMenuItem, goldMenuItem, bossMenuItem,nullptr);	  //创建一个菜单
	menu->setPosition(Vec2::ZERO);																			                                      //设置菜单的位置
	mapParentNode->addChild(menu);																			                                      // 将菜单添加到父节点

	/*设置按钮的位置（相对于父节点）*/ 
	downtownMenuItem->setPosition(Vec2(-100, -2.22));														                                      //设置菜单项的位置 下同
	castleMenuItem->setPosition(Vec2(0, 61.11));
	soilMenuItem->setPosition(Vec2(-800, 11.11));
	fireMenuItem->setPosition(Vec2(400, 555.55));
	woodMenuItem->setPosition(Vec2(-300, -455.55));
	waterMenuItem->setPosition(Vec2(-500, 566.66));
	goldMenuItem->setPosition(Vec2(600, -132.22));
	bossMenuItem->setPosition(Vec2(600, 555.55));
	return true;
}

void Setting6::disableBigMapScrolling()																		//禁用大地图滚动	
{
	_eventDispatcher->removeEventListenersForTarget(this);													// 移除鼠标滚轮事件监听器
}
cocos2d::Scene* Setting6::createScene()
{
	auto scene = Setting6::create();																		// 创建场景		
	return scene;
}
void Setting6::menuItemCallback1(Ref* sender, const std::string& backgroundImage)							//菜单项回调函数
{
	disableBigMapScrolling();																				// 禁用 BigMap 的滚轮缩放

	MiniMap* miniMap = new MiniMap();																	    // 创建 MiniMap 实例
	if (miniMap)
	{
		miniMap->autorelease();																				// 释放 MiniMap 实例
		if (backgroundImage == "smallmap/boss.tmx")															// 如果是boss.tmx
		{
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, BossScene::create()));       // 释放 MiniMap 实例
		}
		else
		{
			miniMap->FlyToMap(backgroundImage);																// 跳转到指定地图
		}
																											// 跳转到指定地图
	}																										// 切换背景

	// 隐藏或移除 BigMap
	auto mapParentNode = this->getChildByTag(100);															// 获取包含 BigMap 的父节点
	if (mapParentNode) {																					// 如果父节点存在
		auto bgSprite = mapParentNode->getChildByName("bgSprite");											// 获取背景精灵
		if (bgSprite) {																						// 如果背景精灵存在
			bgSprite->setVisible(false);																	// 或使用 mapParentNode->removeChild(bgSprite);
		}
	}

	// 隐藏菜单
	auto menuNode = this->getChildByTag(200);																// 获取菜单节点
	if (menuNode) {																							// 如果菜单节点存在
		menuNode->setVisible(false);																		// 隐藏菜单
		auto menuRef = dynamic_cast<Menu*>(menuNode);														// 转换为 Menu 类型
		if (menuRef) {																						// 如果菜单存在
			menuRef->setEnabled(false);																		// 禁用交互
		}
	}
}


cocos2d::MenuItemLabel* Setting6::createTextButton(const std::string& text, const std::string& fontFile, int fontSize, const std::string& backgroundImage)
{
	auto label = Label::createWithTTF(text, fontFile, fontSize);											//创建一个文字标签	 
	label->setTextColor(Color4B::BLACK);																	// 设置文字颜色
	auto button = MenuItemLabel::create                                                                     // 创建文字按钮，并绑定回调函数
	(label, [this, backgroundImage](Ref* sender)															// 设置回调函数
		{
			this->menuItemCallback1(sender, backgroundImage);												// 调用菜单项回调函数
		}
	);

	return button;																							//返回按钮
}

void Setting6::onMouseScroll(cocos2d::Event* event) {
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);												// 获取鼠标事件
	float scrollY = mouseEvent->getScrollY();																// 获取鼠标滚轮的滚动值
	auto mapParentNode = this->getChildByTag(100);															// 获取包含 BigMap 的父节点

	if (!mapParentNode) return;																				// 如果父节点不存在，直接返回

	/*获取当前缩放和新的缩放值*/ 
	float currentScale = mapParentNode->getScale();															// 获取当前缩放值
	float scaleChange = scrollY > 0 ? 0.1f : -0.1f;															// 根据滚动值设置缩放变化
	float newScale = currentScale + scaleChange;															// 计算新的缩放值 
	newScale = std::max(0.5f, std::min(newScale, 5.0f));													// 限制缩放范围

	if (std::abs(newScale - currentScale) < 0.001f) return;													// 如果缩放值没有改变，直接返回

	// 平滑缩放效果
	mapParentNode->stopAllActions();																		// 停止所有动作
	auto scaleTo = ScaleTo::create(0.1f, newScale);															// 创建缩放动作
	auto easeAction = EaseOut::create(scaleTo, 2.0f);														// 创建缓动动作
	mapParentNode->runAction(easeAction);																	// 执行动作

	// 获取屏幕边界
	auto visibleSize = Director::getInstance()->getVisibleSize();											// 获取可见区域的大小
	auto origin = Director::getInstance()->getVisibleOrigin();												// 获取可见区域的原点

	// 确保位置在有效范围内
	Vec2 currentPos = mapParentNode->getPosition();															// 获取当前位置
	float minX = origin.x + visibleSize.width - 3100;														// 设置最小 x 值
	float minY = origin.y + visibleSize.height - 2000;														// 设置最小 y 值

	currentPos.x = std::max(currentPos.x, minX);															// 限制 x 值
	currentPos.y = std::max(currentPos.y, minY);															// 限制 y 值

	mapParentNode->setPosition(currentPos);																	// 设置新位置
}







