#pragma once

#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <string.h>

const std::string MAIN_TASK = "LOOK FOR THE PRINCESS";																		//寻找公主
const std::string MAIN_TASK_DESCRIPTION = "The princess is missing, you need to find her and bring her back to the castle"; //公主失踪，你需要找到她并把她带回城堡

//副任务 一些可以采用的例子

const std::string SIDE_TASK_ONE = "GOLD TASK";															//金
const std::string SIDE_TASK_ONE_DESCRIPTION = "Explore the gold place";									
const std::string SIDE_TASK_ONE_REWARD = "you win the gold";													

const std::string SIDE_TASK_TWO = "WOOD TASK";															//木 
const std::string SIDE_TASK_TWO_DESCRIPTION = "Explore the wood place";
const std::string SIDE_TASK_TWO_REWARD = "skill is update";

const std::string SIDE_TASK_THREE = "EARTH TASK";				         								//土	
const std::string SIDE_TASK_THREE_DESCRIPTION = "Explore the earth place";
const std::string SIDE_TASK_THREE_REWARD = "skill is updated";

const std::string SIDE_TASK_FOUR = "WATER TASK";														//水
const std::string SIDE_TASK_FOUR_DESCRIPTION = "Explore the water place";
const std::string SIDE_TASK_FOUR_REWARD = "skill is updated";


const std::string SIDE_TASK_FIVE = "FIRE TASK";															//火
const std::string SIDE_TASK_FIVE_DESCRIPTION = "Explore the fire place";
const std::string SIDE_TASK_FIVE_REWARD = "skill is updated";

const std::string SIDE_TASK_SIX = "QUIZ1 TASK";															
const std::string SIDE_TASK_SIX_DESCRIPTION = "answer the question";
const std::string SIDE_TASK_SIX_REWARD = "you win gold";

const std::string SIDE_TASK_SEVEN = "QUIZ2 TASK";														
const std::string SIDE_TASK_SEVEN_DESCRIPTION = "answer the question";
const std::string SIDE_TASK_SEVEN_REWARD = "you win gold";

const std::string SIDE_TASK_EIGHT = "GOLDENMINI TASK";												
const std::string SIDE_TASK_EIGHT_DESCRIPTION = "DEFEAT ME";
const std::string SIDE_TASK_EIGHT_REWARD = "you can go";

const std::string SIDE_TASK_NINE = "WOODMINI TASK";																
const std::string SIDE_TASK_NINE_DESCRIPTION = "DEFEAT ME";
const std::string SIDE_TASK_NINE_REWARD = "you can go";

const std::string SIDE_TASK_TEN = "EARTHMINI TASK";															
const std::string SIDE_TASK_TEN_DESCRIPTION = "DEFEAT ME";
const std::string SIDE_TASK_TEN_REWARD = "you can go";

const std::string SIDE_TASK_ELEVEN = "WATERMINI TASK";														
const std::string SIDE_TASK_ELEVEN_DESCRIPTION = "DEFEAT ME";
const std::string SIDE_TASK_ELEVEN_REWARD = "you can go";

const std::string SIDE_TASK_SHIER = "FIREMINI TASK";															
const std::string SIDE_TASK_SHIER_DESCRIPTION = "DEFEAT ME";
const std::string SIDE_TASK_SHIER_REWARD = "you can go";

const std::string SIDE_TASK_SHISAN = "APPLE TASK";															
const std::string SIDE_TASK_SHISAN_DESCRIPTION = "bring fish to me";
const std::string SIDE_TASK_SHISAN_REWARD = "GREAT!";

const std::string SIDE_TASK_SHISI = "TRAVEL TASK";																
const std::string SIDE_TASK_SHISI_DESCRIPTION = "Explore the whole place";
const std::string SIDE_TASK_SHISI_REWARD = "GREAT!";

const std::string SIDE_TASK_SHIWU = "FISH TASK";																	
const std::string SIDE_TASK_SHIWU_DESCRIPTION = "bring fish to me";
const std::string SIDE_TASK_SHIWU_REWARD = "GREAT!";

const std::string SIDE_TASK_SHILIU = "ORE TASK";																	
const std::string SIDE_TASK_SHILIU_DESCRIPTION = "bring ore to me";
const std::string SIDE_TASK_SHILIU_REWARD = "GREAT!";

const std::string NON_TASK = "NON_TASK";															//无任务	
const std::string NON_TASK_DESCRIPTION = "No task";													//无任务描述
class Task {
public:

	Task() noexcept : name(NON_TASK), description(NON_TASK_DESCRIPTION),reward("string"), priority(0) {};//默认构造函数
	Task(const std::string name, const std::string description ,const std::string reward);				//含参构造函数

	void setid(int id) { this->id = id; };															//设置任务id											
	void finish() noexcept;																			//完成任务
	/*get*/
	std::string getTaskName() const { return name; };												//得到任务名字
	std::string getTaskDescription() const { return description; };									//得到任务描述
	std::string getTaskReward() const { return reward; };											//得到任务奖励
	int getid() { return id; };																		//得到任务id
	int state = -1;																					//任务状态
	static int id;																					//任务id
private:
	std::string name;																				//任务名称
	std::string description;																		//任务描述
	std::string reward;																				//任务奖励
	int priority;																					//优先级 
};

#endif
