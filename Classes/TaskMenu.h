#pragma once
#ifndef _TASK_MENU_
#define _TASK_MENU_

#include "cocos2d.h"
#include "Sets/manager.h"
USING_NS_CC;

class TaskMenu :public cocos2d::Layer
{
public:
	CREATE_FUNC(TaskMenu);  // 自动生成静态 create 方法

	virtual bool init();


private:
	// 任务列表，存储 Task 对象
	std::vector<std::shared_ptr<Task>> tasks;

	void createTaskMenu();
	void showTaskDetails(const std::string& taskDetails);
};

#endif _TASK_MENU_