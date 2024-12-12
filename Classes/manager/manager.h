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
	std::shared_ptr<Player> _hero;                                                                                  // 玩家
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
	std::shared_ptr<Inventory> getInventory() const { return _bag; }
	// 获取背包

    // 防止拷贝构造和赋值
  //  GlobalManager(const GlobalManager&) = delete;                                                       
   // GlobalManager& operator=(const GlobalManager&) = delete;

    // 析构函数
    ~GlobalManager() {
		
    }
};

// 初始化
void GlobalManager::initialize() {
	// 初始化元素 
	_elements.emplace_back(std::make_shared<Element>(ElementType::Gold));				// 金
	_elements.emplace_back(std::make_shared<Element>(ElementType::Wood));				// 木
	_elements.emplace_back(std::make_shared<Element>(ElementType::Water));				// 水
	_elements.emplace_back(std::make_shared<Element>(ElementType::Fire));				// 火
	_elements.emplace_back(std::make_shared<Element>(ElementType::Earth));				// 土


	// 初始化玩家
	_hero = std::make_shared<Player>("try.png");										// 玩家

	// 初始化任务 
	_tasks.emplace_back(std::make_shared<Task>(MAIN_TASK, MAIN_TASK_DESCRIPTION));					// 主线任务
	_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_ONE, SIDE_TASK_ONE_DESCRIPTION));			// 副任务1
	_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_TWO, SIDE_TASK_TWO_DESCRIPTION));			// 副任务2
	_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_THREE, SIDE_TASK_THREE_DESCRIPTION));		// 副任务3
	_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_FOUR, SIDE_TASK_FOUR_DESCRIPTION));		// 副任务4
	_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_FIVE, SIDE_TASK_FIVE_DESCRIPTION));		// 副任务5
	_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SIX, SIDE_TASK_SIX_DESCRIPTION));			// 副任务6
	_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SEVEN, SIDE_TASK_SEVEN_DESCRIPTION));		// 副任务7
	_tasks.emplace_back(std::make_shared<Task>(NON_TASK, NON_TASK_DESCRIPTION));					// 无任务
	
	// 初始化技能
	_lowLevelSkills.emplace_back(std::make_shared<LowLevelSkill>(ELEMENT_SURGE));					// 低级技能
	_midLevelSkills.emplace_back(std::make_shared<MidLevelSkill>(Elemental_Torrent));				// 中级技能
	_highLevelSkills.emplace_back(std::make_shared<HighLevelSkill>(Energy_Vortex));					// 高级技能
	_highLevelSkills.emplace_back(std::make_shared<HighLevelSkill>(Arcane_Blast));					// 组合技能

	// 初始化友方NPC
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(PRINCESS));								// 公主
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(KING));									// 国王
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(FishStoreManager));						// 鱼商
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(WeaponStoreManager));						// 武器商
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(VegetableStoreManager));					// 蔬菜商
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(OreStoreManager));							// 矿石商

	// 初始化敌方NPC
	// 金
	_enemyNpcsGold.emplace_back(std::make_shared<EnemyNpc>(ElementType::Gold, 2, _lowLevelSkills[0]));		
	_enemyNpcsGold.emplace_back(std::make_shared<EnemyNpc>(ElementType::Gold, 1, _midLevelSkills[0]));
	// 木
	_enemyNpcsWood.emplace_back(std::make_shared<EnemyNpc>(ElementType::Wood, 2, _lowLevelSkills[0]));
	_enemyNpcsWood.emplace_back(std::make_shared<EnemyNpc>(ElementType::Wood, 1, _midLevelSkills[0]));
	// 土
	_enemyNpcsEarth.emplace_back(std::make_shared<EnemyNpc>(ElementType::Earth, 2, _lowLevelSkills[0]));
	_enemyNpcsEarth.emplace_back(std::make_shared<EnemyNpc>(ElementType::Earth, 1, _midLevelSkills[0]));
	// 水
	_enemyNpcsWater.emplace_back(std::make_shared<EnemyNpc>(ElementType::Water, 2, _lowLevelSkills[0]));
	_enemyNpcsWater.emplace_back(std::make_shared<EnemyNpc>(ElementType::Water, 1, _midLevelSkills[0]));
	// 火
	_enemyNpcsFire.emplace_back(std::make_shared<EnemyNpc>(ElementType::Fire, 2, _lowLevelSkills[0]));
	_enemyNpcsFire.emplace_back(std::make_shared<EnemyNpc>(ElementType::Fire, 1, _midLevelSkills[0]));

	// 初始化Boss
	ElementType type = _hero->getPlayerElement();					
	_enemyNpcsBoss = std::make_shared<EnemyNpc>(type, 3, _highLevelSkills[0]);

	// 初始化物品
	// 武器
	_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_RING));						
	_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_CRYSTAL));
	_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_SCROLL));
	// 护具
	_armors.emplace_back(std::make_shared<Armor>(HELMET));
	_armors.emplace_back(std::make_shared<Armor>(ARMOR));
	_armors.emplace_back(std::make_shared<Armor>(SHOES));
	// 食品
	_foods.emplace_back(std::make_shared<Food>(FISH));													//鱼
	_foods.emplace_back(std::make_shared<Food>(FRUIT));													//水果
	_foods.emplace_back(std::make_shared<Food>(VEGETABLE));												//蔬菜
	_foods.emplace_back(std::make_shared<Food>(HERB));													//草药
	_foods.emplace_back(std::make_shared<Food>(MEAT));													//肉
	_foods.emplace_back(std::make_shared<Food>(MUSHROOM));												//蘑菇
	_foods.emplace_back(std::make_shared<Food>(RICE));													//稻谷
	_foods.emplace_back(std::make_shared<Food>(APPLE));													//苹果
	// 材料
	_materials.emplace_back(std::make_shared<GameMaterial>(TREE));										//树
	_materials.emplace_back(std::make_shared<GameMaterial>(WOOD));										//木头
	_materials.emplace_back(std::make_shared<GameMaterial>(STONE));										//石头
	_materials.emplace_back(std::make_shared<GameMaterial>(GOLD_MINE));									//金矿
	_materials.emplace_back(std::make_shared<GameMaterial>(CHEST));										//宝箱
	_taskItems.emplace_back(std::make_shared<TaskItem>(KEY));											//钥匙
	_taskItems.emplace_back(std::make_shared<TaskItem>(LETTER));										//信件
}
#endif // GLOBAL_MANAGER_H
