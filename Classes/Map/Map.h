#pragma once
#include <iostream>
#include <vector>
using namespace std;

// 特殊点结构体
struct special_point
{
	int x;
	int y;
	int type; // 特殊点类型：出生点0，怪兽1，迷宫2，钓鱼3，采药4，小动物5
};

// 更新地图类设计，不分基类子类，不同地图为地图类的不同对象
class Map
{
public:
	// 请补充大小地图之间切换的函数

	/*函数名：SwitchBetweenSmallMaps
	  函数功能：小地图之间锚点的切换
	  参数列表：
		  role_coord_x，role_coord_y：人物当前所在坐标，通过交互系统获取，从域外地图跳回时需要用到。
		  object_map：需要跳转的对象，通过交互系统获取，决定跳转到哪个地图去。
	  返回值：是否成功跳转，成功则为true
	*/
	bool SwitchBetweenSmallMaps(const int& role_coord_x, const int& role_coord_y, const int& object_map);

	/*函数名：PanM
	  函数功能：地图展示时的平移
	  参数列表：
		  role_coord_x，role_coord_y：人物当前所在坐标，通过交互系统获取。
	  返回值：无
	*/
	void Pan(const int& role_coord_x, const int& role_coord_y);

	// 请补充地图缩放函数

private:
	vector<int> before_jump_point; // 保存跳转之前的人物坐标
	bool fog; // 是否存在迷雾，有迷雾为true
	vector<special_point> special_points; // 结构体数组，存储特殊点坐标，类型：出生点0，怪兽1，迷宫2，钓鱼3，采药4，小动物5
};
