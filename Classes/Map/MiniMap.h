#ifndef __MINI_MAP_H__
#define __MINI_MAP_H__

#include "cocos2d.h"
#include <string>

// 地图类：建议调用时先创建对象，传参地图文件名和是否传送，再调用成员函数
class MiniMap : public cocos2d::Scene
{
public:
	// 构造函数
	MiniMap() :mapName(""), isFly(true), tiledMap(nullptr), player(nullptr), keyboardListener(nullptr) {}
	MiniMap(const std::string& map, bool fly);

	// 创建方法
	static cocos2d::Scene* createScene();

	// 初始化
	 bool init();

	// 析构函数
	 ~MiniMap()
	 {
		 StopListening();
	 }

	// 设置监听器
	void StartListening();

	// 按键按下的回调函数
	void OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// 按键释放的回调函数
	void OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// 清理监听器
	void StopListening();
	
	// 划船去相邻地图：金木水火土村庄
    void BoatingToMap(const std::string& objectMap);

	// 传送去相邻地图：跳转和前往迷宫/竞技场或从迷宫/竞技场退出
	void FlyToMap(const std::string& objectMap);
	
	// 更新人物位置
	void UpdatePlayerPosition(const cocos2d::EventKeyboard::KeyCode keyCode);
	
	//带参宏创建create函数
	CREATE_FUNC(MiniMap);

private:
	std::string mapName; // 当前地图的名称
	bool isFly; // 是否传送
	cocos2d::TMXTiledMap* tiledMap; // 当前地图的瓦片地图
	cocos2d::Sprite* player; // 玩家精灵
	cocos2d::EventListenerKeyboard* keyboardListener; // 键盘监听器
};

#endif // __MINI_MAP_H__