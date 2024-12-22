#include "cocos2d.h"
#include "SmallTask/MazeGame.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

// 若无法加载，转换tmx渲染方案

bool MazeGame::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// 创建并初始化玩家精灵
	player = Sprite::create("HelloWorld.png");											// 默认向右
	if (player == nullptr)																// 确保精灵创建成功
	{
		CCLOG("Failed to create player sprite!");
		return false;
	}

	player->setScale(5000.0f);															// 放大精灵
	player->setPosition(Director::getInstance()->getVisibleSize().width / 2 + player_X * TILE_SIZE, Director::getInstance()->getVisibleSize().height / 2 + (MAZE_HEIGHT - player_Y) * TILE_SIZE);
	this->addChild(player,5);

	// 注册键盘事件监听器
	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MazeGame::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	generateMaze();																		// 初始化迷宫
	renderMaze();																		// 渲染迷宫

	return true;
}

MazeGame* MazeGame::create()
{
	srand(time(0));

	// 创建迷宫数组
	MazeGame* mazeGame = new MazeGame();												// 创建游戏实例
	if (mazeGame && mazeGame->init())													// 初始化游戏
	{
		return mazeGame;																// 返回游戏实例
	}
	else
	{
		delete mazeGame;
		return nullptr;
	}
}

void MazeGame::generateMaze()
{
	CCLOG("Generating maze...");

	// 初始化迷宫数组
	maze.resize(MAZE_HEIGHT + 2, std::vector<char>(MAZE_WIDTH + 2, '#'));  // 增加边框

	// 填充迷宫，0 为通道，X 为墙
	for (int i = 1; i <= MAZE_HEIGHT; i++)
	{
		for (int j = 1; j <= MAZE_WIDTH; j++)
		{
			maze[i][j] = rand() % 2 ? '0' : 'X';
		}
	}

	// 随机选择起点和终点
	player_X = rand() % MAZE_WIDTH + 1;
	player_Y = rand() % MAZE_HEIGHT + 1;
	maze[player_X][player_Y] = 'S';											// 标记起点

	int exit_X, exit_Y;
	do
	{
		exit_X = rand() % MAZE_WIDTH + 1;
		exit_Y = rand() % MAZE_HEIGHT + 1;
	} while (exit_X == player_X && exit_Y == player_Y);						// 确保终点不与起点重合 
	maze[exit_X][exit_Y] = 'E';												// 标记终点 
	CCLOG("Maze generated.");												// 输出迷宫生成成功
}

void MazeGame::renderMaze()
{
	CCLOG("Rendering maze...");

	for (int i = 0; i < MAZE_HEIGHT + 2; i++)
	{
		for (int j = 0; j < MAZE_WIDTH + 2; j++) 
		{
			char tile = maze[i][j];
			if (tile == 'S')
			{
				// 绘制起点
				auto startSprite = Sprite::create("Maze/apple.png");
				if (startSprite)
				{
					startSprite->setScale(50.0f);  // 放大精灵
					startSprite->setPosition(Director::getInstance()->getVisibleSize().width / 2 + j * TILE_SIZE, Director::getInstance()->getVisibleSize().height / 2 + (MAZE_HEIGHT - i) * TILE_SIZE);
					this->addChild(startSprite);
					CCLOG("Placed start sprite at (%d, %d)", Director::getInstance()->getVisibleSize().width / 2 + j * TILE_SIZE, Director::getInstance()->getVisibleSize().height / 2 + (MAZE_HEIGHT - i) * TILE_SIZE);
				}
			}
			else if (tile == 'E')
			{
				// 绘制终点
				auto endSprite = Sprite::create("Maze/strawberry.png");
				if (endSprite) 
				{
					endSprite->setScale(50.0f);  // 放大精灵
					endSprite->setPosition(Director::getInstance()->getVisibleSize().width / 2 + j * TILE_SIZE, Director::getInstance()->getVisibleSize().height / 2 + (MAZE_HEIGHT - i) * TILE_SIZE);
					this->addChild(endSprite);
					CCLOG("Placed end sprite at (%d, %d)", j * TILE_SIZE, (MAZE_HEIGHT - i) * TILE_SIZE);
				}
			}
			else if (tile == 'X') 
			{
				// 绘制墙壁
				auto wallSprite = Sprite::create("Maze/blue_ghost.png");
				if (wallSprite) 
				{
					wallSprite->setScale(500000.0f);  // 放大精灵
					wallSprite->setPosition(Director::getInstance()->getVisibleSize().width / 2 + j * TILE_SIZE, Director::getInstance()->getVisibleSize().height / 2 + (MAZE_HEIGHT - i) * TILE_SIZE);
					this->addChild(wallSprite,100);
					CCLOG("Placed wall sprite at (%d, %d)", j * TILE_SIZE, (MAZE_HEIGHT - i) * TILE_SIZE);
				}
			}
		}
	}

	CCLOG("Maze rendered.");
}


void MazeGame::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	// 删除旧的玩家精灵
	if (player)
	{
		this->removeChild(player);											// 删除之前的精灵
	}

	int newPlayerX = player_X;
	int newPlayerY = player_Y;

	if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		newPlayerY = player_Y + 1;
		if (maze[newPlayerX][newPlayerY] != 'X')							// 如果不是墙，则移动
		{
			player->setTexture("Maze/pacman_up.png");
		}
	}
	else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		newPlayerY = player_Y - 1;
		if (maze[newPlayerX][newPlayerY] != 'X')							// 如果不是墙，则移动
		{
			player->setTexture("Maze/pacman_down.png");
		}
	}
	else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		newPlayerX = player_X - 1;
		if (maze[newPlayerX][newPlayerY] != 'X')							// 如果不是墙，则移动
		{
			player->setTexture("Maze/pacman_left.png");
		}
	}
	else if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		newPlayerX = player_X + 1;
		if (maze[newPlayerX][newPlayerY] != 'X')							// 如果不是墙，则移动
		{
			player->setTexture("Maze/pacman_right.png");
		}
	}

	// 更新玩家坐标并移动精灵
	if (maze[newPlayerX][newPlayerY] != 'X')								// 如果新的位置是可走的
	{
		player_X = newPlayerX;
		player_Y = newPlayerY;
		player->setScale(50.0f);  // 放大精灵
		player->setPosition(player_X * TILE_SIZE, (MAZE_HEIGHT - player_Y) * TILE_SIZE);

																			// 将新的精灵添加到场景
		this->addChild(player);

																			// 检查玩家是否到达终点
		if (maze[player_X][player_Y] == 'E')								// 到达终点
		{
			auto winLabel = Label::createWithTTF("You Win!", "fonts/Marker Felt.ttf", 64); // 显示胜利提示
			winLabel->setPosition(Director::getInstance()->getVisibleSize() / 2);		   // 居中显示
			winLabel->setTextColor(Color4B::YELLOW);
			this->addChild(winLabel);													   // 确保提示在最上层
			CCLOG("Player has won the game!");											   // 停止游戏或其他操作
			return;
		}
	}
}
