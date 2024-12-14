//creator: 冯俊财 2353924
//description: 玩家类的实现
#include <string>
#include <string.h>

#include "elements.h"
# include "player.h"

#include "items.h"
/*
* class player 的含参构造函数
* player 代表游戏中的玩家角色。   创建实例是 将其 设定为 hero 便于组中成员 完成代码
* names 玩家名字 element 玩家元素属性 1金 2木 3水 4火 5土
* level 初始化为0 hp初始化为50 attack初始化为10
*/

constexpr int PLAYRT_BASE_HP = 50;//玩家初始血量
constexpr int PLAYER_UPGRADE_HP = 25;//升级增加的血量
constexpr int PLAYRR_BASE_ATTACK = 10;//玩家初始攻击力
constexpr int PLAYER_UPGRADE_ATTACK = 5;//升级增加的攻击力
constexpr int SPEED = 200;//移动速度

//构造函数 初始化姓名 元素属性 等级血量攻击力等等
Player::Player() : level(0), hp(PLAYRT_BASE_HP), attack(PLAYRR_BASE_ATTACK), isAlive(true)
{
	state = PlayerState::NORMAL;

	std::cout << "为你的英雄起一个名字吧：";
	std::cin >> name;
	 
	int elemnt = 0;
	// 1金 2木 3水 4火 5土
	//这里通过界面选择元素属性
	std::cin >> elemnt;//暂且先用cin代替

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

	//初始时 装备
	my_armor = nullptr;//护甲
	my_helmet = nullptr;//头盔
	my_shoes = nullptr;//鞋子
	//初始时 武器
	weapon = nullptr;//武器为空

	position = Vec2(0, 0);//初始位置
	//初始化背包
	bag = Inventory();
}
/*
* name:upgrade
* level ++， hp+25， attack+5
*/
void Player::Upgrade()
{
	level++;//等级加1
	max_hp += PLAYER_UPGRADE_HP;//血量增加
	hp = max_hp;//血量回复满
	basic_attack += PLAYER_UPGRADE_ATTACK;//攻击力增加
}


// 玩家攻击敌人
void Player::AttackEnemy(EnemyNpc& enemy, EventKeyboard::KeyCode KEY)
{//攻击敌人
	switch (KEY)
	{
		case EventKeyboard::KeyCode::KEY_0:
		//	Attack(enemy, elementSurge);
			break;
		case EventKeyboard::KeyCode::KEY_1:
			//攻击
	//		Attack(enemy, elementalTorrent);
			break;
		case EventKeyboard::KeyCode::KEY_2:
			//攻击
		//	Attack(enemy, energyVortex);
			break;
		default:
			break;
	}
	int damage = attack;
	if (damage > 0) {
		enemy.hp -= damage;
		// 显示攻击效果
	}

	enemy.TakeDamage(attack);
}

// 玩家受到伤害
void Player::TakeDamage(int damage)
{
	if ((hp - damage) > 0)
	{
		hp -= damage;
	}
	else
	{
		hp = 0;
		isAlive = false;
		//玩家死亡
//退出战斗场景
	//游戏结束 或者 返回上一个存档点 或者退出战斗场景
	}
}

// 玩家治疗  
// heal_hp 治疗的血量
void Player::Heal(int heal_hp)
{
	if ((hp + heal_hp) <= max_hp)
	{
		hp += heal_hp;
	}
	else
	{
		hp = max_hp;
	}
}


// 获取玩家的当前血量
int Player::GetHp() const
{
	return this->hp;
}

// 获取玩家的名字
std::string Player::GetName() const
{
	return this->name;
}

// 获取玩家的等级
int Player::GetLevel() const
{
	return this->level;
}

// 移动 需要坐标
Vec2 Player::Move(EventKeyboard::KeyCode keyCode)
{
	Vec2 next_position = position;
	if (isMoving)//如果正在移动
	{
		switch (keyCode)
		{
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
				next_position.y += SPEED * Director::getInstance()->getDeltaTime()*level;
				break;
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				next_position.y -= SPEED * Director::getInstance()->getDeltaTime() * level;
				break;
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				next_position.x -= SPEED * Director::getInstance()->getDeltaTime() * level;
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				next_position.x += SPEED * Director::getInstance()->getDeltaTime() * level;
				break;
			default:
				break;
		}
	}
	return next_position;
}
//设定坐标
void Player::setPosition(const Vec2& newPosition){
	position = newPosition;                 //更新坐标存储
	Node::setPosition(position);            //更新地图上显示的坐标
}
//图像

bool Player::initWithFile(const std::string& filename)
{
	if (!Sprite::initWithFile(filename)) {
		std::cerr << "无法加载文件：" << filename << std::endl;
		return false;
	}
	return true;
}
