#pragma once
#include <vector>
#include "cocos2d.h"

//特殊点类型
#define BORN_POINT 0 // 出生点
#define MONSTER 1 // 怪兽
#define MAZE 2 // 迷宫
#define FISHING 3 // 钓鱼
#define HERB_GATHERING 4 // 采药
#define ANIMALS 5 // 小动物

// 特殊点结构体
struct SpecialPoint
{
	int x;
	int y;
	int type; // 特殊点类型
};

// 地图类
class Map : public cocos2d::Layer
{
public:
	// 构造函数
	Map();
	Map(const std::string& name);

	// 创建方法
	static cocos2d::Scene* createScene();

	// 初始化
	virtual bool init();

	// 析构函数
	virtual ~Map() = default;

	/*函数名：SwitchBetweenSmallMaps
	  函数功能：小地图之间锚点的切换
	  参数列表：
		  roleWorldPosition：人物当前所在世界坐标，通过交互系统获取，从域外地图跳回时需要用到。
		  object_map：需要跳转的对象，通过交互系统获取，决定跳转到哪个地图去。
	  返回值：是否成功跳转，成功则为true
	*/
	virtual bool SwitchBetweenSmallMaps(const std::string& object_map);

	/*函数名：Pan
	  函数功能：地图展示时的平移
	  参数列表：
		  roleWorldPosition：人物当前所在世界坐标，通过交互系统获取。
		  keyCode：人物前进方向，键盘控制，通过交互系统获取。
	  返回值：无
	*/
	void Pan(const cocos2d::Vec2& roleWorldPosition, const cocos2d::EventKeyboard::KeyCode keyCode);

	//带参宏创建create函数
	CREATE_FUNC(Map);

protected:
	std::string mapName; // 当前地图的名称
	cocos2d::TMXTiledMap* tiledMap; // 当前地图的瓦片地图
};
