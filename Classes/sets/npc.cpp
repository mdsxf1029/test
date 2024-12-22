
#include "tasks.h" 
#include"skills.h"
#include "npc.h"
#include "Sets/manager.h"

//前置声明
class Skill;

//基类 NPC类
//构造函数 传入名称
NPC::NPC(const std::string name) : name(name) {} 

//子类
//友方NPC
//构造函数
FriendNpc::FriendNpc(const std::string name) : name(name)
{

}

void FriendNpc::GiveTask()
{

}

//敌方NPC   
//构造函数 传入元素类型和等级 
EnemyNpc::EnemyNpc(ElementType element, int level, std::shared_ptr<Skill>skill, std::string afilename) :
	element(element), level(level), isAlive(true), skill(skill), filename(afilename)
{
	hp = ENEMY_HP * level;														//初始化血量
	maxHp = hp;																	//最大血量
	basic_attack = ENEMY_ATTACK * level;										//初始化攻击力
	attack = basic_attack + skill->getInfo().attack;							//攻击力
};

void EnemyNpc::TakeDamage(int damage)											//敌人受到伤害
{
	if ((hp - damage) > 0)														//如果血量-伤害大于0
	{
		hp -= damage;															//正常扣血
	}
	else																		//否则 hp=0
	{
		hp = 0;
		isAlive = false;														//死亡
	}
}
  


void EnemyNpc::setPosition(Vec2 position)							//设置位置
{
	this->position = position;
	Sprite::setPosition(position);
};


bool EnemyNpc::initWithFile()                                         //加载图像
{
	if (!Sprite::initWithFile(filename)) {
		std::cerr << "无法加载文件：" << filename << std::endl;
		return false;
	}
	return true;
}
