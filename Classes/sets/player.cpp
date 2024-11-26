//creator: 冯俊财 2353924
//description: 玩家类的实现
#include <string>
#include <string.h>

#include "elements.h"
# include "player.h"
/*
* class player 的含参构造函数
* player 代表游戏中的玩家角色。   创建实例是 将其 设定为 hero 便于组中成员 完成代码
* names 玩家名字 element 玩家元素属性 1金 2木 3水 4火 5土
* level 初始化为0 hp初始化为50 attack初始化为10
*/

player::player(string& names, int element) :name(names), level(0), hp(50), attrack(10)
{
	switch (elemnt)
	{
		case 1:
			player_element = ElementType::Gold;
			break;
		case 2:
			player_element = ElementType::Wood;
			break;
		case 3:
			player_element = ElementType::Water;
			break;
		case 4:
			player_element = ElementType::Fire;
			break;
		case 5:
			player_element = ElementType::Earth;
			break;
		default:
			player_element = ElementType::Gold;
			break;
	}
}
/*
* name:upgrade 
* level ++， hp+25， attack+5
*/
void player::upgrade()
{
	level++;//等级加1
	hp += UPGRADE_HP;//血量增加
	attack += UPGRADE_ATTACK;//攻击力增加
}
