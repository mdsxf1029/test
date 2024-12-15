#pragma once

#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <string.h>

const std::string MAIN_TASK = "LOOK FOR THE PRINCESS";//寻找公主
const std::string MAIN_TASK_DESCRIPTION = "The princess is missing, you need to find her and bring her back to the castle";//公主失踪，你需要找到她并把她带回城堡

//副任务 一些可以采用的例子
const std::string SIDE_TASK_ONE = "LOOK FOR THE TREASURE";//探索迷宫，找到宝藏
const std::string SIDE_TASK_ONE_DESCRIPTION = "The treasure is hidden in the maze, you need to find it";//宝藏藏在迷宫中，你需要找到它

const std::string SIDE_TASK_TWO = "DEFEAT THE MONSTER";//击败怪物
const std::string SIDE_TASK_TWO_DESCRIPTION = "The monster is blocking the way, you need to defeat it";//怪物挡住了去路，你需要击败它

const std::string SIDE_TASK_THREE = "HELP THE VILLAGERS";//帮助村民 
const std::string SIDE_TASK_THREE_DESCRIPTION = "The villagers are in trouble, you need to help them";//村民们遇到了麻烦，你需要帮助他们

const std::string SIDE_TASK_FOUR = "FIND THE WAY OUT";//找到出口
const std::string SIDE_TASK_FOUR_DESCRIPTION = "There is a maze, you need to find the way out";//有一个迷宫，你需要找到出口

const std::string SIDE_TASK_FIVE = "FIND THE SECRET";//找到秘密
const std::string SIDE_TASK_FIVE_DESCRIPTION = "There is a secret hidden in the castle, you need to find it";//城堡中有一个秘密，你需要找到它

const std::string SIDE_TASK_SIX = "FIND THE TREASURE";//找到宝藏
const std::string SIDE_TASK_SIX_DESCRIPTION = "The treasure is hidden in the forest, you need to find it";//宝藏藏在森林中，你需要找到它

const std::string SIDE_TASK_SEVEN = "FIND THE KEY";//找到钥匙
const std::string SIDE_TASK_SEVEN_DESCRIPTION = "The key is hidden in the cave, you need to find it";//钥匙藏在洞穴中，你需要找到它

const std::string NON_TASK = "NON_TASK";//无任务	
const std::string NON_TASK_DESCRIPTION = "No task";//无任务描述

const std::string MAIN_TASK_GOLD = "TASK_GOLD";//金任务
const std::string MAIN_TASK_GOLD_DESCRIPTION = "TASK_GOLD";//待补充

const std::string MAIN_TASK_WOOD = "TASK_WOOD";//木任务
const std::string MAIN_TASK_WOOD_DESCRIPTION = "TASK_WOOD";//待补充

const std::string MAIN_TASK_WATER = "TASK_WATER";//水任务
const std::string MAIN_TASK_WATER_DESCRIPTION = "TASK_WATER";//待补充

const std::string MAIN_TASK_FIRE = "TASK_FIRE";//火任务
const std::string MAIN_TASK_FIRE_DESCRIPTION = "TASK_FIRE";//待补充

const std::string MAIN_TASK_EARTH = "TASK_EARTH";//土任务
const std::string MAIN_TASK_EARTH_DESCRIPTION = "TASK_EARTH";//待补充

class Task {
public:

	Task() noexcept : name(NON_TASK), description(NON_TASK_DESCRIPTION), priority(0), isFinished(false) {};//默认构造函数
	Task(const std::string name, const std::string description);//含参构造函数
	void finish() noexcept;//完成任务
	std::string getTaskName() const { return name; };
	std::string getTaskDescription() const { return description; };
	bool isTaskFinished() const { return isFinished; };

protected:

private:
	std::string name;//任务名称
	std::string description;//任务描述
	int priority;//优先级
	bool isFinished;//是否完成
};



#endif
