#pragma once

#define SKILLS_H

#include <string>
#include"cocos2d.h"
#include "elements.h"

//技能类
 //名称
const std::string ELEMENT_SURGE = "ELEMENT SURGE";													//元素冲击
const std::string Elemental_Torrent = "Elemental Torrent";											//元素洪流
const std::string Energy_Vortex = "Energy Vortex";													//能量漩涡 
// 前向声明
class SkillEffect;  

//技能的基础信息
struct SkillInfo {
	std::string name;																				//姓名
	int attack;																						//攻击力
	float degreerange;																				//攻击角度范围	
	float range;																					//攻击范围
	std::string particleFile;																		// 特效文件路径 
};

class Skill {
public:

	Skill(const SkillInfo& info);
	virtual ~Skill();
	/*set*/
	void setColor(ElementType type);																// 设置技能颜色 
	/*get*/
	const std::string& getName() const { return _info.name; }                                       //得到名字
	int getAttack() const { return _info.attack; }												    //得到攻击力  
	SkillInfo getInfo() { return _info; }															//得到技能信息
	virtual float cast(cocos2d::Node* caster, const cocos2d::Vec2& targetPos);                      //得到释放技能的度数 
	
	bool isInRange(const cocos2d::Vec2& casterPos, const cocos2d::Vec2& targetPos, const cocos2d::Vec2& clickPos) const; // 检查目标是否在攻击范围内
	bool isInRange(const cocos2d::Vec2& casterPos, const cocos2d::Vec2& targetPos) const;								 // 检查目标是否在攻击范围内						
	 
	SkillInfo _info;    																            //技能信息                                    
	cocos2d::ParticleSystemQuad* _effect;                                                           //特效   

};



