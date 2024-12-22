#pragma once
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <functional>
#include "sets\tasks.h"



struct NPCData {
    cocos2d::Sprite* npcSprite;
    std::string npcFunction;  // "chat" 或 "quest"
    std::shared_ptr<Task> ppp;
    int index;
    std::string targetScene;  // 目标场景（与NPC交互后跳转的场景）

    NPCData(cocos2d::Sprite* sprite, const std::string& function, std::shared_ptr<Task> ppp, int index,const std::string& target)
        : npcSprite(sprite), npcFunction(function), ppp(ppp),index(index),targetScene(target) {}
};



class GameScene : public cocos2d::Scene
{
public:
    GameScene();
    virtual ~GameScene();

    static cocos2d::Scene* createScene();
    virtual bool init();                      // 初始化场景
    void update(float delta) override;        // 更新逻辑
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onMouseUp(cocos2d::Event* event);

    CREATE_FUNC(GameScene);

private:
    cocos2d::TMXTiledMap* _tileMap;           // TMX 地图
                   // 玩家角色
    cocos2d::Sprite* _currentDialogueBox; 
    cocos2d::Sprite* _currentChoiceBox;    // 当前显示的对话框
    std::vector<NPCData> _npcList; // NPC 列表

    // 当前任务数据
        struct Quest {
        std::string title;
        std::string description;
        int reward;
        bool isCompleted;
    } _currentQuest;
    int _playerGold = 0;

    void displayTaskOptions(NPCData& npcData); // 显示任务选择弹窗
    void displayTaskPro(NPCData& npcData); // 会发生跳转
    void displayTaskStatus(NPCData& npcData);  // 显示任务状态弹窗
    void displayRewardOptions(NPCData& npcData); // 显示奖励领取弹窗
    void handleQuestAcceptance(NPCData& npcData); // 处理接受任务
    void handleQuestCompletion(NPCData& npcData); // 处理任务完成奖励

    const float playerSpeed = 100.0f;         // 玩家移动速度

    void displayChoice1(cocos2d::Sprite* npc, const std::string& question,
        const std::vector<std::pair<std::string, std::function<void()>>>& choices);
    void displayChoice2(cocos2d::Sprite* npc, const std::string& question,
        const std::vector<std::pair<std::string, std::function<void()>>>& choices);
    void handleChatNPC(cocos2d::Sprite* npc);
    
    void displayDialogue(cocos2d::Sprite* npc, const std::string& text);
    void displayTownInfo(cocos2d::Sprite* npc);
    void displayTownDetails(cocos2d::Sprite* npc);
    void displayQuestInfo(cocos2d::Sprite* npc);
    void displayQuestDetails(cocos2d::Sprite* npc);
    void displayGoodbye(cocos2d::Sprite* npc);
    cocos2d::Scene* getSceneByName(const std::string& sceneName);
};

#endif // __GAME_SCENE_H__
