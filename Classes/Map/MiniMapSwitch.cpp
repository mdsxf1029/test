/*2351271 黄弋涵*/
#include "Map/MiniMap.h"
#include "cocos2d.h"
std::shared_ptr<Player> _player1 = GlobalManager::getInstance().getPlayer();
/*划船去相邻地图：金木水火土村庄城堡*/ 
void MiniMap::BoatingToMap(const std::string& objectMap)
{
	CCLOG("boat to!!!!!!!");																							// 输出信息 
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();												// 获取可见区域大小
	CCLOG("boat to2222");																								// 输出信息
	auto boatScene = cocos2d::Scene::create();																			// 创建过渡场景
	CCLOG("boat to3333");																								// 输出信息 
	cocos2d::Sprite* boatSprite;																						// 创建精灵 -- 过度场景
	if (mapName == "smallmap/whole3.tmx" || (mapName == "smallmap/fire.tmx" && objectMap == "smallmap/whole3.tmx")) {	// 如果是从水村庄城堡去往金村庄城堡
		boatSprite = cocos2d::Sprite::create("CloseNormal.png");														// 创建精灵
	}
	else {
		boatSprite = cocos2d::Sprite::create("CloseSelected.png");														// 创建精灵
	}

	boatSprite->setContentSize(visibleSize);																			// 设置精灵大小 和 可见区域一样大
	boatSprite->setPosition(visibleSize / 2);																			// 设置精灵位置为屏幕中心
	boatScene->addChild(boatSprite);																					// 将精灵添加到过渡场景
	auto boatTransition1 = cocos2d::TransitionSlideInT::create(0.5f, boatScene);										// 创建过渡动画
	cocos2d::Director::getInstance()->replaceScene(boatTransition1);													// 加载过度场景，代替当前场景
	std::shared_ptr<Player> player1 = GlobalManager::getInstance().getPlayer();											// 获取玩家
	_player1->removeFromParent();																						// 移除玩家（上个场景）
	auto newScene = createWithMap(objectMap, false);																	// 创建新场景图像
	auto boatTransition2 = cocos2d::TransitionSlideInT::create(0.5f, newScene);											// 创建新场景
	cocos2d::Director::getInstance()->replaceScene(boatTransition2);													// 加载新场景，代替过渡场景
}

/*传送去相邻地图：跳转至金木水火土村庄城堡，前往迷宫/竞技场或从迷宫/竞技场退出*/ 
void MiniMap::FlyToMap(const std::string& objectMap)
{
	CCLOG("flyto111"); 																									// 输出信息
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();												// 获取可见区域的大小
	auto flyScene = cocos2d::Scene::create();																			// 创建过渡场景
	auto flySprite = cocos2d::Sprite::create("UI/X.png");																// 创建精灵
	flySprite->setContentSize(visibleSize);																				// 设置精灵的大小与屏幕一样大
	flySprite->setPosition(visibleSize / 2);																			// 设置精灵的位置为屏幕中心
	flyScene->addChild(flySprite);																						// 将精灵添加到过渡场景
	auto flyTransition1 = cocos2d::TransitionSlideInT::create(2.0f, flyScene);											// 创建过渡动画

	/*如果是前往迷宫或竞技场*/ 
	if (objectMap == "smallmap/maze.tmx" || objectMap == "smallmap/battlefeild.tmx") { 
		CCLOG("flyto222222");
		cocos2d::Director::getInstance()->pushScene(flyTransition1);													//把上次地图压入栈中，展示过渡图像
	}
	/*去其他地方*/ 
	else {  
		cocos2d::Director::getInstance()->replaceScene(flyTransition1);													// 加载过渡场景，代替当前场景
	}
	/*如果是从迷宫或竞技场退出*/ 
	if (mapName == "smallmap/maze.tmx" || mapName == "smallmap/battlefeild.tmx") { 
		auto fadeOut = cocos2d::FadeOut::create(2.0f);																	// 创建淡出动作
		 
		auto callFunc = cocos2d::CallFunc::create([]() {
			cocos2d::Director::getInstance()->popScene();																// 动画完成后，弹出场景
			});

		auto sequence = cocos2d::Sequence::create(fadeOut, callFunc, nullptr);											// 创建一个序列，先淡出再调用 popScene
		flyScene->runAction(sequence);																					// 将序列动作添加到过渡场景	
	}
	/*其他转换*/ 
	else {  
		this->cleanup();																								// 清理当前场景									
		auto newScene = createWithMap(objectMap, true);																	// 创建新场景										
		auto flyTransition2 = cocos2d::TransitionSlideInT::create(0.5f, newScene);										// 添加过渡动画
		cocos2d::Director::getInstance()->replaceScene(flyTransition2);													// 加载新场景，释放掉过渡场景
	}
}