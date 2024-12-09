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
	Player* _hero;                                                                                  // 玩家
	std::vector<Task> _tasks;   														            // 任务                                    
	std::vector<LowLevelSkill> _lowLevelSkills; 									    			// 低级技能         
	std::vector<MidLevelSkill> _midLevelSkills; 									    			// 中级技能                             
	std::vector<HighLevelSkill> _highLevelSkills;   							        			// 高级技能                     
	std::vector<FriendNpc> _friendNpcs; 									    					// 友方NPC                                
	std::vector<EnemyNpc> _enemyNpcs;   							    		        			// 敌方NPC                            
	std::vector<Weapon> _weapons;   							    		            			// 武器   
	std::vector<Armor> _armors;   							    		                			// 护具   
	std::vector<Food> _foods;       			    		                            			// 食品   
	std::vector<GameMaterial> _materials;   							    		            	// 材料           
	std::vector<TaskItem> _taskItems;   							    		                	// 任务物品 
	std::vector<Element> _elements;   							    		                	    // 元素
	Inventory _bag;   							    		                	                    // 背包               

	// 构造函数
    GlobalManager() {
		initialize();                                                                               // 初始化
    }

	void initialize();//初始化

public:

	// 获取全局管理器实例
    static GlobalManager& getInstance() {
        static GlobalManager instance;
        return instance;
    }

	// 获取成员变量
	Player* getPlayer() { return _hero; }                                                                           // 获取玩家
	const std::vector<Task>& getTasks() const { return _tasks; }												    // 获取任务
	const std::vector<LowLevelSkill>& getLowLevelSkills() const { return _lowLevelSkills; } 					    // 获取低级技能
	const std::vector<MidLevelSkill>& getMidLevelSkills() const { return _midLevelSkills; } 						// 获取中级技能
	const std::vector<HighLevelSkill>& getHighLevelSkills() const { return _highLevelSkills; } 				    	// 获取高级技能
	const std::vector<FriendNpc>& getFriendNpcs() const { return _friendNpcs; } 								    // 获取友方NPC
	const std::vector<EnemyNpc>& getEnemyNpcs() const { return _enemyNpcs; }    					                // 获取敌方NPC
	const std::vector<Weapon>& getWeapons() const { return _weapons; } 										        // 获取武器
	const std::vector<Armor>& getArmors() const { return _armors; } 										        // 获取护具
	const std::vector<Food>& getFoods() const { return _foods; } 										            // 获取食品
	const std::vector<GameMaterial>& getMaterials() const { return _materials; } 								    // 获取材料
	const std::vector<TaskItem>& getTaskItems() const { return _taskItems; } 									    // 获取任务物品
	const std::vector<Element>& getElements() const { return _elements; } 						    			    // 获取元素
	Inventory& getInventory() { return _bag; } 									                                    // 获取背包

    // 防止拷贝构造和赋值
    GlobalManager(const GlobalManager&) = delete;                                                       
    GlobalManager& operator=(const GlobalManager&) = delete;

    // 析构函数
    ~GlobalManager() {
        delete _hero;                                                                                               // 释放玩家资源
		delete& _bag;                                                                                               // 释放背包资源
		delete[] & _tasks;                                                                                          // 释放任务资源
		delete[] & _lowLevelSkills;                                                                                 // 释放低级技能资源
		delete[] & _midLevelSkills;                                                                                 // 释放中级技能资源
		delete[] & _highLevelSkills;                                                                                // 释放高级技能资源
		delete[] & _friendNpcs;                                                                                     // 释放友方NPC资源
		delete[] & _enemyNpcs;                                                                                      // 释放敌方NPC资源
		delete[] & _weapons;                                                                                        // 释放武器资源
		delete[] & _armors;                                                                                         // 释放护具资源
		delete[] & _foods;                                                                                          // 释放食品资源
		delete[] & _materials;                                                                                      // 释放材料资源
		delete[] & _taskItems;                                                                                      // 释放任务物品资源
		delete[] & _elements;                                                                                        // 释放元素资源
    }
};

// 初始化
void GlobalManager::initialize() {
	// 初始化元素
	_elements.emplace_back(ElementType::Gold);																// 金
	_elements.emplace_back(ElementType::Wood);																// 木		
	_elements.emplace_back(ElementType::Water);																// 水			
	_elements.emplace_back(ElementType::Fire);																// 火		
	_elements.emplace_back(ElementType::Earth);																// 土						

	// 初始化玩家
	_hero = new Player("try.png");

	// 初始化任务
	_tasks.emplace_back(MAIN_TASK, MAIN_TASK_DESCRIPTION);
	_tasks.emplace_back(SIDE_TASK_ONE, SIDE_TASK_ONE_DESCRIPTION);
	_tasks.emplace_back(SIDE_TASK_TWO, SIDE_TASK_TWO_DESCRIPTION);
	_tasks.emplace_back(SIDE_TASK_THREE, SIDE_TASK_THREE_DESCRIPTION);
	_tasks.emplace_back(SIDE_TASK_FOUR, SIDE_TASK_FOUR_DESCRIPTION);
	_tasks.emplace_back(SIDE_TASK_FIVE, SIDE_TASK_FIVE_DESCRIPTION);
	_tasks.emplace_back(SIDE_TASK_SIX, SIDE_TASK_SIX_DESCRIPTION);
	_tasks.emplace_back(SIDE_TASK_SEVEN, SIDE_TASK_SEVEN_DESCRIPTION);
	_tasks.emplace_back(NON_TASK, NON_TASK_DESCRIPTION);

	// 初始化技能
	_lowLevelSkills.emplace_back(ELEMENT_SURGE);															// 元素冲击
	_midLevelSkills.emplace_back(Elemental_Torrent);														// 元素洪流				
	_highLevelSkills.emplace_back(Energy_Vortex);															// 能量漩涡								
	_highLevelSkills.emplace_back(Arcane_Blast);															// 奥术爆发													

	// 初始化友方NPC
	_friendNpcs.emplace_back(PRINCESS);                                                                      // 公主
	_friendNpcs.emplace_back(KING); 														    			 // 国王 

	_friendNpcs.emplace_back(FishStoreManager); 														 // 服装商
	_friendNpcs.emplace_back(WeaponStoreManager); 														 // 武器商
	_friendNpcs.emplace_back(VegetableStoreManager); 													 // 食品商
	_friendNpcs.emplace_back(OreStoreManager); 														     // 技能商

	// 初始化敌方NPC
	//金
	_enemyNpcs.emplace_back(ElementType::Gold, 2, Elemental_Torrent);                                           //低级金怪物
	_enemyNpcs.emplace_back(ElementType::Gold, 1, ELEMENT_SURGE);   								            //高级金怪物                  
	//木
	_enemyNpcs.emplace_back(ElementType::Wood, 2, Elemental_Torrent);                                           //低级木怪物
	_enemyNpcs.emplace_back(ElementType::Wood, 1, ELEMENT_SURGE);   								            //高级木怪物
	//土
	_enemyNpcs.emplace_back(ElementType::Earth, 2, Elemental_Torrent);                                          //低级土怪物
	_enemyNpcs.emplace_back(ElementType::Earth, 1, ELEMENT_SURGE);                                              //高级土怪物
	//水
	_enemyNpcs.emplace_back(ElementType::Water, 2, Elemental_Torrent);                                          //低级水怪物
	_enemyNpcs.emplace_back(ElementType::Water, 1, ELEMENT_SURGE);      					                    //高级水怪物
	//火
	_enemyNpcs.emplace_back(ElementType::Fire, 2, Elemental_Torrent);       			                        //低级火怪物
	_enemyNpcs.emplace_back(ElementType::Fire, 1, ELEMENT_SURGE);    			                                //高级火怪物

	ElementType type = _hero->getPlayerElement();
	_enemyNpcs.emplace_back(type, 3, Energy_Vortex);                                                               //boss


	// 其他敌方NPC可以按照需要继续添加

	// 初始化物品
	// 武器
	_weapons.emplace_back(MAGIC_RING);																	// 魔戒
	_weapons.emplace_back(MAGIC_CRYSTAL);																// 魔晶
	_weapons.emplace_back(MAGIC_SCROLL);																// 魔卷
	// 护具
	_armors.emplace_back(HELMET);																		// 头盔						
	_armors.emplace_back(ARMOR);																		// 盔甲						
	_armors.emplace_back(SHOES);																		// 鞋子					
	// 食品
	_foods.emplace_back(FISH);																			// 鱼
	_foods.emplace_back(FRUIT);																			// 水果				
	_foods.emplace_back(VEGETABLE);																		// 蔬菜						
	_foods.emplace_back(HERB);																			// 草药					
	_foods.emplace_back(MEAT);																			// 肉				
	_foods.emplace_back(MUSHROOM);																		// 蘑菇			
	_foods.emplace_back(RICE);																			// 米饭							
	_foods.emplace_back(APPLE);																			// 苹果					
	// 材料
	_materials.emplace_back(TREE);																		// 树
	_materials.emplace_back(WOOD);																		// 木材
	_materials.emplace_back(STONE);																		// 石头
	_materials.emplace_back(GOLD_MINE);																	// 金矿
	_materials.emplace_back(CHEST);																		// 宝箱	
	_taskItems.emplace_back(KEY);																		// 钥匙
	_taskItems.emplace_back(LETTER);																	// 信						


}
#endif // GLOBAL_MANAGER_H
