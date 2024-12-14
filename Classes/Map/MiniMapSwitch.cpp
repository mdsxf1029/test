/*2351271 黄弋涵*/
#include "MiniMap.h"
#include "cocos2d.h"

// 划船去相邻地图：金木水火土村庄城堡
void MiniMap::BoatingToMap(const std::string& objectMap)
{
	// 获取可见区域的大小
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	// 创建过渡场景
	auto boatScene = cocos2d::Scene::create();

	// 创建过渡场景的背景精灵
	auto boatSprite = cocos2d::Sprite::create("boat.png");

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

	// 创建新场景
	auto newScene = createWithMap(objectMap, false);

	// 添加过渡动画
	auto boatTransition2 = cocos2d::TransitionSlideInT::create(0.5f, newScene);

	// 加载新场景，释放掉过渡场景
	cocos2d::Director::getInstance()->replaceScene(boatTransition2);
}

// 传送去相邻地图：跳转至金木水火土村庄城堡，前往迷宫/竞技场或从迷宫/竞技场退出
void MiniMap::FlyToMap(const std::string& objectMap)
{
	// 获取可见区域的大小
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	// 创建过渡场景
	auto flyScene = cocos2d::Scene::create();

	// 创建过渡场景的背景精灵
	auto flySprite = cocos2d::Sprite::create("fly.png");

	// 设置精灵的大小与屏幕一样大
	flySprite->setContentSize(visibleSize);

	// 设置精灵的位置为屏幕中心
	flySprite->setPosition(visibleSize / 2);

	// 把背景精灵添加到过渡场景
	flyScene->addChild(flySprite);

	// 添加过渡动画
	auto flyTransition1 = cocos2d::TransitionSlideInT::create(0.5f, flyScene);

	if (objectMap == "maze.tmx" || objectMap == "battle.tmx") { // 如果是前往迷宫或竞技场
		// 把上次地图压入栈中，展示过渡图像
		cocos2d::Director::getInstance()->pushScene(flyTransition1);
	}
	else { // 去其他地方
		// 把上次场景释放掉，展示过渡图像
		cocos2d::Director::getInstance()->replaceScene(flyTransition1);
	}

	if (mapName == "maze.tmx" || mapName == "battle.tmx") { // 如果是从迷宫或竞技场退出
		// 创建一个淡出动画
		auto fadeOut = cocos2d::FadeOut::create(0.5f);

		// 在动画完成后调用 popScene
		auto callFunc = cocos2d::CallFunc::create([]() {
			cocos2d::Director::getInstance()->popScene();
			});

		// 创建一个序列，先淡出再调用 popScene
		auto sequence = cocos2d::Sequence::create(fadeOut, callFunc, nullptr);

		// 将序列动作添加到过渡场景
		flyScene->runAction(sequence);
	}
	else { // 其他转换
		// 创建新场景
		auto newScene = createWithMap(objectMap, true);

		// 添加过渡动画
		auto flyTransition2 = cocos2d::TransitionSlideInT::create(0.5f, newScene);

		// 加载新场景，释放掉过渡场景
		cocos2d::Director::getInstance()->replaceScene(flyTransition2);
	}
}
