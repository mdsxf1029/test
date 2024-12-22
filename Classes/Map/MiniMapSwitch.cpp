/*2351271 黄弋涵*/
#include "Map/MiniMap.h"
#include "cocos2d.h"
std::shared_ptr<Player> _player1 = GlobalManager::getInstance().getPlayer();
// 划船去相邻地图：金木水火土村庄城堡
void MiniMap::BoatingToMap(const std::string& objectMap)
{
	CCLOG("boat to!!!!!!!");
	// 获取可见区域的大小
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	CCLOG("boat to2222");
	// 创建过渡场景
	auto boatScene = cocos2d::Scene::create();
	CCLOG("boat to3333");
	// 创建过渡场景的背景精灵
	cocos2d::Sprite* boatSprite;
	if (mapName == "smallmap/whole3.tmx" || (mapName == "smallmap/fire.tmx" && objectMap == "smallmap/whole3.tmx")) {
		boatSprite = cocos2d::Sprite::create("CloseNormal.png");
	}
	else {
		boatSprite = cocos2d::Sprite::create("CloseSelected.png");
	}

	// 设置精灵的大小与屏幕一样大
	boatSprite->setContentSize(visibleSize);

	// 设置精灵的位置为屏幕中心
	boatSprite->setPosition(visibleSize / 2);

	// 把背景精灵添加到过渡场景
	boatScene->addChild(boatSprite);

	// 添加过渡动画
	auto boatTransition1 = cocos2d::TransitionSlideInT::create(0.5f, boatScene);

	// 释放掉上次场景，展示过渡图像
	cocos2d::Director::getInstance()->replaceScene(boatTransition1);
	std::shared_ptr<Player> player1 = GlobalManager::getInstance().getPlayer();
	// 创建新场景
	_player1->removeFromParent();
	auto newScene = createWithMap(objectMap, false);
	
	// 添加过渡动画
	auto boatTransition2 = cocos2d::TransitionSlideInT::create(0.5f, newScene);

	// 加载新场景，释放掉过渡场景
	cocos2d::Director::getInstance()->replaceScene(boatTransition2);
}

// 传送去相邻地图：跳转至金木水火土村庄城堡，前往迷宫/竞技场或从迷宫/竞技场退出
void MiniMap::FlyToMap(const std::string& objectMap)
{
	CCLOG("flyto111");
	// 获取可见区域的大小
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	// 创建过渡场景
	auto flyScene = cocos2d::Scene::create();

	// 创建过渡场景的背景精灵
	auto flySprite = cocos2d::Sprite::create("UI/X.png");

	// 设置精灵的大小与屏幕一样大
	flySprite->setContentSize(visibleSize);

	// 设置精灵的位置为屏幕中心
	flySprite->setPosition(visibleSize / 2);

	// 把背景精灵添加到过渡场景
	flyScene->addChild(flySprite);

	// 添加过渡动画
	auto flyTransition1 = cocos2d::TransitionSlideInT::create(2.0f, flyScene);

	// 如果是前往迷宫或竞技场
	if (objectMap == "smallmap/maze.tmx" || objectMap == "smallmap/battlefeild.tmx") { 
		// 把上次地图压入栈中，展示过渡图像
		CCLOG("flyto222222");
		cocos2d::Director::getInstance()->pushScene(flyTransition1);
	}
	// 去其他地方
	else { 
		// 把上次场景释放掉，展示过渡图像
		cocos2d::Director::getInstance()->replaceScene(flyTransition1);
	}
	// 如果是从迷宫或竞技场退出
	if (mapName == "smallmap/maze.tmx" || mapName == "smallmap/battlefeild.tmx") { 
		// 创建一个淡出动画
		auto fadeOut = cocos2d::FadeOut::create(2.0f);

		// 在动画完成后调用 popScene
		auto callFunc = cocos2d::CallFunc::create([]() {
			cocos2d::Director::getInstance()->popScene();
			});

		// 创建一个序列，先淡出再调用 popScene
		auto sequence = cocos2d::Sequence::create(fadeOut, callFunc, nullptr);

		// 将序列动作添加到过渡场景
		flyScene->runAction(sequence);
	}
	// 其他转换
	else { 
		// 创建新场景
		this->cleanup();
		auto newScene = createWithMap(objectMap, true);

		// 添加过渡动画
		auto flyTransition2 = cocos2d::TransitionSlideInT::create(0.5f, newScene);

		// 加载新场景，释放掉过渡场景
		cocos2d::Director::getInstance()->replaceScene(flyTransition2);
	}
}