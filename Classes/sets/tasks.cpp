#include "tasks.h"

//构造函数  用于初始化 任务名称 任务描述 优先级 主任务优先级为2 副任务优先级为1 任务状态为未完成
Task::Task(std::string& name，std::string& description) :name(name), description(description)
{
	//初始化任务状态
	isFinished = false;//初始化为未完成

	//初始化优先级
	if (name == MAIN_TASK)
		proirity = 2;
	else if (name == nonTask)
	{
		isFinished = true;
		proirity = 0;
	}
	else
		proirity = 1;
	
}

//析构函数
Task::~Task() {};

//完成任务
void Task::finish()
{
	//如果未完成， 状态改为完成
	if(!isFinished)
		isFinished = true;

	//完成任务时调用该函数  具体调用条件 看游戏状态
}
