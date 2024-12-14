#ifndef GLOBAL_MANAGER_H
#define GLOBAL_MANAGER_H

#include <string>
#include <vector>

#include "sets/Player.h"
#include "sets/NPC.h"
#include "sets/tasks.h"
#include "sets/Skills.h"
#include "sets/Items.h"
#include "sets/Elements.h"
#include "sets/Inventory.h"

// 前置声明
class Player;
class Task;
class LowLevelSkill;
class MidLevelSkill;
class HighLevelSkill;
class Weapon;
class Armor;
class Food;
class GameMaterial;
class TaskItem;
class FriendNpc;
class EnemyNpc;
class Element;
class Inventory;

// 全局管理器
class GlobalManager {
private:
	std::shared_ptr<Player> _hero;																						// 玩家
	std::shared_ptr<EnemyNpc>_battleNpc;																				// 战斗NPC
	std::vector <std::shared_ptr< Task >> _tasks;   														            // 任务                                    
	
	std::vector <std::shared_ptr< LowLevelSkill >> _lowLevelSkills; 									    			// 低级技能         
	std::vector<std::shared_ptr<MidLevelSkill>> _midLevelSkills; 									    			// 中级技能                             
	std::vector<std::shared_ptr<HighLevelSkill>> _highLevelSkills;   							        			// 高级技能                     
	
	std::vector<std::shared_ptr<FriendNpc>> _friendNpcs; 									    					// 友方NPC                                
	
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsGold;   							    		        			// 敌方NPC -- 金
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsWood;   							    		        			// 敌方NPC -- 木
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsWater;   							    		        			// 敌方NPC -- 水
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsFire;   							    		        			// 敌方NPC -- 火
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsEarth;   							    		        			// 敌方NPC -- 土
	std::shared_ptr<EnemyNpc> _enemyNpcsBoss;   							    		        					// boss
	std::vector<std::shared_ptr<Weapon>> _weapons;   							    		            			// 武器   
	std::vector<std::shared_ptr<Armor>> _armors;   							    		                			// 护具   
	std::vector<std::shared_ptr<Food>> _foods;       			    		                            			// 食品   
	std::vector<std::shared_ptr<GameMaterial>> _materials;   							    		            	// 材料           
	std::vector<std::shared_ptr<TaskItem>> _taskItems;   							    		                	// 任务物品 
	std::vector<std::shared_ptr<Element>> _elements;   							    		                	    // 元素
	std::shared_ptr<Inventory> _bag;   							    		                	                    // 背包               

	// 构造函数
    GlobalManager() {
		initializeElements();//初始化元素
		initializeTasks();//初始化任务
		initializeSkills();//初始化技能
		initializeFriendNpcs();//初始化友方NPC
		initializePlayer();//初始化玩家
		initializeEnemyNpcs();//初始化敌方NPC
		initializeWeapons();//初始化武器
		initializeArmors();//初始化护具
		initializeFoods();//初始化食品
		initializeMaterials();//初始化材料
		initializeTaskItems();//初始化任务物品 
	}

	
public:

	// 获取全局管理器实例
    static GlobalManager& getInstance() {
        static GlobalManager instance;
        return instance;
    }
														// 设置战斗NPC
	void initializeElements();//初始化
	void initializePlayer();//初始化玩家
	void initializeTasks();//初始化任务
	void initializeSkills();//初始化技能
	void initializeFriendNpcs();//初始化友方NPC
	void initializeEnemyNpcs();//初始化敌方NPC
	void initializeWeapons();//初始化武器
	void initializeArmors();//初始化护具
	void initializeFoods();//初始化食品
	void initializeMaterials();//初始化材料
	void initializeTaskItems();//初始化任务物品 
	void initializeBag();//初始化背包
	

	void setBattleNpc(std::shared_ptr<EnemyNpc> npc) { _battleNpc = npc; }
	// 获取成员变量  

	std::shared_ptr<Player> getPlayer() const { return _hero; }																	// 获取玩家
	const std::vector<std::shared_ptr<Task>>& getTasks() const { return _tasks; }												// 获取任务
	const std::vector<std::shared_ptr<LowLevelSkill>>& getLowLevelSkills() const { return _lowLevelSkills; }					// 获取低级技能
	const std::vector<std::shared_ptr<MidLevelSkill>>& getMidLevelSkills() const { return _midLevelSkills; }					// 获取中级技能
	const std::vector<std::shared_ptr<HighLevelSkill>>& getHighLevelSkills() const { return _highLevelSkills; }					// 获取高级技能
	const std::vector<std::shared_ptr<FriendNpc>>& getFriendNpcs() const { return _friendNpcs; }								// 获取友方NPC
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsGold() const { return _enemyNpcsGold; }							// 获取敌方NPC -- 金
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsWood() const { return _enemyNpcsWood; }							// 获取敌方NPC -- 木
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsWater() const { return _enemyNpcsWater; }							// 获取敌方NPC -- 水
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsFire() const { return _enemyNpcsFire; }							// 获取敌方NPC -- 火
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsEarth() const { return _enemyNpcsEarth; }							// 获取敌方NPC -- 土
	const std::vector<std::shared_ptr<Weapon>>& getWeapons() const { return _weapons; }											// 获取武器
	const std::vector<std::shared_ptr<Armor>>& getArmors() const { return _armors; }											// 获取护具
	const std::vector<std::shared_ptr<Food>>& getFoods() const { return _foods; }												// 获取食品
	const std::vector<std::shared_ptr<GameMaterial>>& getMaterials() const { return _materials; }								// 获取材料
	const std::vector<std::shared_ptr<TaskItem>>& getTaskItems() const { return _taskItems; }									// 获取任务物品
	const std::vector<std::shared_ptr<Element>>& getElements() const { return _elements; }										// 获取元素
	const std::shared_ptr<Inventory> getInventory() const { return _bag; }														// 获取背包		
	const std::shared_ptr<EnemyNpc> getBattleNpc() const { return _battleNpc; }													// 获取战斗NPC
	// 获取背包

    // 防止拷贝构造和赋值
	GlobalManager(const GlobalManager&) = delete;
	GlobalManager& operator=(const GlobalManager&) = delete;

    // 析构函数
    ~GlobalManager() {
		
    }
};





#endif // GLOBAL_MANAGER_H
