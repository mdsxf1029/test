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

class Task {
public:
	Task(std::string& name，std::string& description);
	~Task();
	void finish();//完成任务
protected:

private:
	std::string name;//任务名称
	std::string description;//任务描述
	int proirity;//优先级
	bool isFinished;//是否完成
};

//主任务
Task mainTask(MAIN_TASK，MAIN_TASK_DESCRIPTION);
//副任务
Task sideTaskOne(SIDE_TASK_ONE, SIDE_TASK_ONE_DESCRIPTION);
Task sideTaskTwo(SIDE_TASK_TWO, SIDE_TASK_TWO_DESCRIPTION);
Task sideTaskThree(SIDE_TASK_THREE, SIDE_TASK_THREE_DESCRIPTION);
Task sideTaskFour(SIDE_TASK_FOUR, SIDE_TASK_FOUR_DESCRIPTION);
Task sideTaskFive(SIDE_TASK_FIVE, SIDE_TASK_FIVE_DESCRIPTION);
Task sideTaskSix(SIDE_TASK_SIX, SIDE_TASK_SIX_DESCRIPTION);
Task sideTaskSeven(SIDE_TASK_SEVEN, SIDE_TASK_SEVEN_DESCRIPTION);

//无任务
Task nonTask("NO TASK", "No task now");//用来 敷衍 那些没有任务的NPC 或者是任务已经完成的NPC

#endif
