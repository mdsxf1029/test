#pragma once

#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <string.h>

const string MAIN_TASK = "LOOK FOR THE PRINCESS";//寻找公主

//辅助任务 一些可以采用的例子
const string SIDE_TASK_ONE = "LOOK FOR THE TREASURE";//探索迷宫，找到宝藏
const string SIDE_TASK_TWO = "DEFEAT THE MONSTER";//击败怪物
const string SIDE_TASK_THREE = "HELP THE VILLAGERS";//帮助村民 
const string SIDE_TASK_FOUR = "FIND THE WAY OUT";//找到出口
const string SIDE_TASK_FIVE = "FIND THE SECRET";//找到秘密
const string SIDE_TASK_SIX = "FIND THE TREASURE";//找到宝藏
const string SIDE_TASK_SEVEN = "FIND THE KEY";//找到钥匙

class Task {
public:
	Task();
	virtual ~Task();
protected:

private:

};

class MainTask :public Task
{
public:


protected:

private:

};
class SideTask : public Task
{
public:


protected:


private:


};


#endif
