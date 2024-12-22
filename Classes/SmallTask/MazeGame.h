#pragma once
#ifndef _MAZE_GAME_
#define _MAZE_GAME_

#include "cocos2d.h"
#include <vector>
USING_NS_CC;

class MazeGame :public cocos2d::Scene
{
public:
	MazeGame(){}  // 构造函数初始化游戏未完成
	
	static MazeGame* create();
	bool init();

    void generateMaze();                                                                // 生成一个简单的迷宫
	void renderMaze();                                                                  // 渲染迷宫
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);  // 键盘事件处理

private:
	const int MAZE_WIDTH = 100;
	const int MAZE_HEIGHT = 100;
	const int TILE_SIZE = 16.0f;

	std::vector<std::vector<char>> maze;                                                // 迷宫数组
	Sprite* player;                                                                     // 玩家精灵	
	int player_X, player_Y;                                                             // 记录玩家在迷宫中位置
};

#endif _MAZE_GAME_