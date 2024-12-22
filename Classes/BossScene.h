#pragma once

#pragma once

#ifndef __BOSS_SCENE_H__
#define __BOSS_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <functional>
#include "sets/manager.h"
#include "Map/MiniMap.h"
struct bossDATA {
    cocos2d::Sprite* bossSprite;                                                                // NPC 精灵
    std::string bossFunction;                                                                   // "chat" 或 "quest"
    std::string targetScene;                                                                    // 目标场景（与NPC交互后跳转的场景）
    std::shared_ptr<Task> ppp;																	// 任务												
	int index;  																			    // NPC 索引                               
    int taskid;                                                                                 // NPC 索引	
    bossDATA() : bossSprite(nullptr), bossFunction(""), targetScene(""),index(0),ppp(nullptr) {}// 默认构造函数
    bossDATA(cocos2d::Sprite* sprite, const std::string& function, int index, std::shared_ptr<Task> ppp, int taskid, const std::string& target)
        : bossSprite(sprite), bossFunction(function), index(index), ppp(ppp), taskid(taskid), targetScene(target) {
    }
};

class BossScene : public cocos2d::Scene
{
public:
	BossScene();                                                                                // 构造函数
	virtual ~BossScene();																	    // 析构函数

	static cocos2d::Scene* createScene();														// 创建场景
    virtual bool init();                                                                        // 初始化场景
	void update(float delta) override;															// 更新逻辑
	bool IsColliding(cocos2d::Vec2 position);													// 碰撞检测
	void displayChoice1(cocos2d::Sprite* npc, const std::string& question,						// 显示选择对话框1
        const std::vector<std::pair<std::string, std::function<void()>>>& choices);
	void displayChoice2(cocos2d::Sprite* npc, const std::string& question,						// 显示选择对话框2
        const std::vector<std::pair<std::string, std::function<void()>>>& choices);
    void handleChatNPC(cocos2d::Sprite* npc);

	void displayDialogue(cocos2d::Sprite* npc, const std::string& text);						// 显示对话框
	void displayTownInfo(cocos2d::Sprite* npc);													// 显示城镇信息
	void displayTownDetails(cocos2d::Sprite* npc);												// 显示城镇详细信息
	void displayQuestInfo(cocos2d::Sprite* npc);												// 显示任务信息
	void displayQuestDetails(cocos2d::Sprite* npc);											    // 显示任务详细信息
	void displayGoodbye(cocos2d::Sprite* npc);													// 显示再见
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);			// 键盘按下事件
	void displayTaskPro(bossDATA& npcData);														// 显示任务进度

	cocos2d::Sprite* boss;																		// NPC 精灵
    cocos2d::Sprite* _currentDialogueBox;														// 当前显示的对话框
    cocos2d::Sprite* _currentChoiceBox;															// 当前显示的对话框
    CREATE_FUNC(BossScene);
private:
    cocos2d::TMXTiledMap* _tileMap;		                                                        // 地图
	std::shared_ptr<EnemyNpc> rawEnemy;  													    // 敌人
	bossDATA Boss;																				// NPC 数据
};

#endif // __BOSS_SCENE_H__
