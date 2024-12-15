#ifndef __MINI_MAP_H__
#define __MINI_MAP_H__

#include "cocos2d.h"
#include <string>

// 地图类
/* 调用示例：
	auto miniMapScene = MiniMap::createWithMap("gold1.tmx", true);
	cocos2d::Director::getInstance()->replaceScene(miniMapScene);
*/
class MiniMap : public cocos2d::Scene
{
public:
	// 构造函数
	MiniMap(const std::string& mapFile = "village.tmx", bool fly = true) :mapName(mapFile), isFly(fly), tiledMap(nullptr), player(nullptr), keyboardListener(nullptr) {}
	MiniMap(const std::string& map, bool fly);

	// 创建方法
	static cocos2d::Scene* createWithMap(const std::string&mapName,bool fly);

	// 自用初始化
	bool initWithMap(const std::string&mapName);

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

	// 查找相邻地图
	void GetNeighborMap(std::string& map1, std::string& map2);

	// 按钮回调函数
	void ButtonCallback(Ref* sender);


private:
	std::string mapName; // 当前地图的名称
	bool isFly; // 是否传送
	cocos2d::TMXTiledMap* tiledMap; // 当前地图的瓦片地图
	cocos2d::Sprite* player; // 玩家精灵
	cocos2d::EventListenerKeyboard* keyboardListener; // 键盘监听器
};

#endif // __MINI_MAP_H__