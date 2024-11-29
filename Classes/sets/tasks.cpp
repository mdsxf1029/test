#include "tasks.h"
#include"sets_variables.h"
 
Task::Task(std::string name, std::string description) : name(name), description(description)
{
	//初始化任务状态
	isFinished = false; //初始化为未完成

	//初始化优先级
	if (name == "MAIN_TASK")
		priority = 2;
	else if (name == "nonTask")
	{
		isFinished = true;
		priority = 0;
	}
	else
		priority = 1;
}

//完成任务
void Task::finish() noexcept
{
	//如果未完成， 状态改为完成
	if (!isFinished)
		isFinished = true;

	//完成任务时调用该函数  具体调用条件 看游戏状态
}