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


//构造函数 初始化姓名 元素属性 等级血量攻击力等等
Player::Player() : level(0), hp(PLAYRT_BASE_HP), attack(PLAYRR_BASE_ATTACK), isAlive(true)
{
	state = PlayerState::NORMAL;												//初始化状态
	name = "hero";																//初始化名字
	int elemnt = 1;															    //初始化元素属性  开始界面时候，通过选择元素属性
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

	//初始化
	my_armor = nullptr;																				//护甲
	my_helmet = nullptr;																			//头盔
	my_shoes = nullptr;																				//鞋子
	weapon = nullptr;																				//武器
	position = Vec2(0, 0);																			//初始位置 
} 
//升级
void Player::Upgrade()																				//升级
{
	level++;																						//等级加1
	max_hp += PLAYER_UPGRADE_HP;																	//血量增加
	hp = max_hp;																					//血量回复满
	basic_attack += PLAYER_UPGRADE_ATTACK;															//攻击力增加
}
//受伤
void Player::TakeDamage(int damage)																	//玩家受到伤害											
{
	if ((hp - damage) > 0)
	{
		hp -= damage;																				//血量减少
	}
	else
	{
		hp = 0;																						//血量为0
		isAlive = false;																			//玩家死亡								
	}
}
//治疗
void Player::Heal(int heal_hp)																		//玩家治疗							
{
	if(hp>0&&hp<max_hp)																				//如果血量不足，但不是0
		hp += heal_hp;																				//血量增加
	if (hp > max_hp)																				//如果血量大于最大血量
		hp = max_hp;																				//血量回复满
}
//获取玩家的当前血量
int Player::getHp() const																			//获取玩家的当前血量
{
	return this->hp;
}
//获取玩家的攻击力
int Player::getAttack() const																		// 获取玩家的攻击力
{
	return this->attack;
}

std::string Player::GetName() const {return this->name;}											// 获取玩家的名字		
int Player::getMaxHp() const {return max_hp; }														// 获取玩家的最大血量
int Player::getSpeed() const {return SPEED; }														// 获取玩家的移动速度
int Player::GetLevel() const {return this->level;}													// 获取玩家的等级


Vec2 Player::Move(EventKeyboard::KeyCode keyCode)													// 玩家移动
{
	Vec2 next_position = position;																	// 下一个位置					
	CCLOG("position:%f %f", position.x, position.y);
	if (isMoving)																					//如果正在移动
	{																								//获取下一个位置
		switch (keyCode)
		{
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
				next_position.y += SPEED * Director::getInstance()->getDeltaTime();
				isMoving = false;
				break;
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				next_position.y -= SPEED * Director::getInstance()->getDeltaTime();
				isMoving = false;
				break;
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				next_position.x -= SPEED * Director::getInstance()->getDeltaTime();
				isMoving = false;
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				next_position.x += SPEED * Director::getInstance()->getDeltaTime();
				isMoving = false;
				break;
			default:
				break;
		}
	}
	CCLOG("next_position:%f %f", next_position.x, next_position.y);
	return next_position;																			//返回下一个位置
}

//设定坐标
void Player::setPosition(const Vec2& newPosition) {
	position = newPosition;																			// 更新坐标成员
}

//图像
bool Player::initWithFile(const std::string& filename)												//初始化图像文件							
{
	if (!Sprite::initWithFile(filename)) {
		;
		return false;
	}
	return true;
}
 