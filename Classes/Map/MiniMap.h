#ifndef __MINI_MAP_H__
#define __MINI_MAP_H__

#include "cocos2d.h"
#include <string>
#include <vector>
#include <functional>
#include "Sets/tasks.h"
#include "Sets/manager.h"
#include "Sets/items.h"
#include "HelloWorldScene.h"

struct NPCData {
	cocos2d::Sprite* npcSprite;																						// NPC 精灵												
	std::string npcFunction;																						// "chat" 或 "quest"
	std::shared_ptr<Task> ppp;																						// 任务												
	int index;																										// NPC 索引
	int taskid;																										// task 索引							
	std::string targetScene;																						// 目标场景（与NPC交互后跳转的场景）

	NPCData(cocos2d::Sprite* sprite, const std::string& function, int index,std::shared_ptr<Task> ppp,int taskid, const std::string& target)
		: npcSprite(sprite), npcFunction(function), index(index), ppp(ppp), taskid(taskid), targetScene(target) {}  //构造函数																												// 构造函数
};

struct ItemList {
	cocos2d::Sprite* itemSprite;																					// 物品精灵
	int index;																										// 物品索引
	int id;																											// 物品 ID
	Vec2 position;																									// 物品位置

	ItemList(cocos2d::Sprite* sprite, int index,int id,Vec2 position)
		: itemSprite(sprite), index(index), id(id), position(position) {}											// 构造函数
};
class MiniMap : public cocos2d::Scene
{
public:
	
	MiniMap(const std::string& mapFile = "village.tmx", bool fly = true)												// 构造函数
	:mapName(mapFile), isFly(fly), tiledMap(nullptr),  keyboardListener(nullptr), _currentDialogueBox(nullptr),
		_currentChoiceBox(nullptr) {}		

	static cocos2d::Scene* createWithMap(const std::string& mapName, bool fly);											// 创建小地图场景								
	/*自用初始化*/ 
	bool initWithMap(const std::string& mapName);																		// 初始化地图
	void update(float delta) override;																					// 更新逻辑
	bool IsColliding(cocos2d::Vec2 position);																			// 碰撞检测
	void createTaskMenu();																								// 创建任务菜单
	void createBigMap();																								// 创建大地图
	void createBackpack();																								// 创建背包
	void openBackpack();																								// 打开背包

	/*析构函数*/ 
	 ~MiniMap()
	 {
		 StopListening();
	 }

	void StartListening();																							//设置键盘事件监听器
	void OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);								// 按键按下的回调函数
	void OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);								// 按键释放的回调函数
	void StopListening();																							// 停止监听键盘事件								
	
 	void BoatingToMap(const std::string& objectMap);																// 划船去相邻地图	 
	void FlyToMap(const std::string& objectMap);																	// 传送去相邻地图
	
	void UpdatePlayerPosition(const cocos2d::EventKeyboard::KeyCode keyCode);										// 更新人物位置
	void GetNeighborMap(std::string& newMap1, std::string& newMap2, int& map1, int& map2);							// 获取相邻地图
	void ButtonCallback(Ref* sender);																				// 按钮回调函数
	
	//void onEnter() override;																						// 进入场景
	//void onEnterTransitionDidFinish() override;																	// 进入场景后

///private:
	std::string mapName;																							// 当前地图的名称
	bool isFly;																										// 是否传送

	std::vector<NPCData> _npcList;																					// NPC 列表
	std::vector<ItemList> goldoreItems;																				// 金矿石物品列表
	std::vector<ItemList> appleItems;																				// 苹果物品列表

	cocos2d::TMXTiledMap* tiledMap;																					// 当前地图的瓦片地图
	cocos2d::EventListenerKeyboard* keyboardListener;																// 键盘监听器
	cocos2d::Sprite* _currentDialogueBox;																			// 当前显示的对话框
	cocos2d::Sprite* _currentChoiceBox;																				// 当前显示的对话框
	cocos2d::Node* npcNode;																							// NPC 节点
	cocos2d::Node* itemNode;																						// 物品节点
	cocos2d::Scene* getSceneByName(const std::string& sceneName);													// 获取场景
	Vec2 touchLocation;																								// 用来存储触摸位置
	Vec2 preposition;																								// 用来存储人物上一个位置

	void displayTaskOptions(NPCData& npcData);																		// 显示任务选择弹窗
	void displayTaskPro(NPCData& npcData);																			// 会发生跳转
	void displayTaskStatus(NPCData& npcData);																		// 显示任务状态弹窗
	void displayRewardOptions(NPCData& npcData);																	// 显示奖励领取弹窗
	void handleQuestAcceptance(NPCData& npcData);																	// 处理接受任务
	void handleQuestCompletion(NPCData& npcData);																	// 处理任务完成奖励
	void displayChoice1(cocos2d::Sprite* npc, const std::string& question,											// 展示选择框1
		const std::vector<std::pair<std::string, std::function<void()>>>& choices);										
	void displayChoice2(cocos2d::Sprite* npc, const std::string& question,											// 展示选择框2
		const std::vector<std::pair<std::string, std::function<void()>>>&choices); 

	void handleChatNPC(cocos2d::Sprite* npc);																		// 处理 NPC 对话
	void displayDialogue(cocos2d::Sprite* npc, const std::string& text);											// 展示对话框	
	void displayTownInfo(cocos2d::Sprite* npc);																		// 展示城镇信息
	void displayTownDetails(cocos2d::Sprite* npc);																	// 展示城镇详情
	void displayQuestInfo(cocos2d::Sprite* npc);																	// 展示任务信息
	void displayQuestDetails(cocos2d::Sprite* npc);																	// 展示任务详情
	void displayGoodbye(cocos2d::Sprite* npc);																		// 展示再见
	void checkPickUpItems();																						// 检查拾取物品	
	void PickUpInteraction(ItemList* item);																			// 拾取物品交互									
	void restorePositionsAfterPop();																				//恢复人物位置
	void verifySprites();																							//验证精灵
	void onEnter();
	void onEnterTransitionDidFinish();
};

#endif // __MINI_MAP_H__