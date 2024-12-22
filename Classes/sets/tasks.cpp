#include "tasks.h"

int Task::id = 0;
Task::Task(std::string name, std::string description, std::string reward) : name(name), description(description),reward(reward)
{
	//初始化
	if (name == "MAIN_TASK")
		priority = 2;
	else if (name == "nonTask")
	{
		state = true;
		priority = 0;
	}
	else
		priority = 1;
}

//完成任务
void Task::finish() noexcept                               //完成任务时调用该函数
{
	//如果未完成， 状态改为完成
	if (state==0)
		state = 1;
}
