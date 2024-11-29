#include"skills.h"

//技能类
Skill::Skill(std::string& name) :name(name) {};
Skill::~Skill() {};

//低级技能
LowLevelSkill::LowLevelSkill(std::string& name) :Skill(name) 
{
	attack = 10;
};
LowLevelSkill::~LowLevelSkill() {};

//中级技能
MidLevelSkill::MidLevelSkill(std::string& name) :Skill(name)
{
	attack = 20;
};
MidLevelSkill::~MidLevelSkill() {};

//高级技能
HighLevelSkill::HighLevelSkill(std::string& name) :Skill(name)
{
	attack = 30;
};
HighLevelSkill::~HighLevelSkill() {};
