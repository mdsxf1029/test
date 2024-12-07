#pragma once

#ifndef SKILLS_H
#define SKILLS_H

#include <string>
//一些技能 来自gpt
/*
元素冲击 (Elemental Surge)
描述：释放元素的力量，对目标造成伤害。

奥术爆发 (Arcane Blast)
描述：施放一种强大的奥术能量，造成范围伤害。

能量漩涡 (Energy Vortex)
描述：召唤一个能量漩涡，吸引并击中附近的敌人。
混沌之光 (Chaos Light)
描述：释放混沌的能量，造成随机元素伤害。
 
元素洪流 (Elemental Torrent)
描述：释放一股强大的元素洪流，冲击目标。 */
//技能类

//基础技能  低中高
const std::string ELEMENT_SURGE = "ELEMENT SURGE";//元素冲击
const std::string Elemental_Torrent = "Elemental Torrent";//元素洪流
const std::string Energy_Vortex = "Energy Vortex";//能量漩涡
//组合技  先后调用先前的来触发
const std::string Arcane_Blast = "Arcane Blast";//奥术爆发


class Skill {
public:
	Skill(const std::string name);
	virtual ~Skill();

	std::string name;//技能名称 
};

class LowLevelSkill : public Skill {
public:
	LowLevelSkill(std::string name);
	virtual ~LowLevelSkill();

	int attack;//伤害
};

class MidLevelSkill : public Skill {
public:
	MidLevelSkill(std::string name);
	virtual ~MidLevelSkill();

	int attack;//伤害
};
class HighLevelSkill : public Skill {
public:
	HighLevelSkill(std::string name);
	virtual ~HighLevelSkill();

	int attack;//伤害
};


#endif
