#ifndef GLOBAL_MANAGER_H
#define GLOBAL_MANAGER_H

#include <string>
#include <vector>
#include <memory>
#include "sets/player.h"
#include "sets/nPC.h"
#include "sets/tasks.h"
#include "sets/skills.h"
#include "sets/items.h"
#include "sets/elements.h"

// 前置声明

struct SkillInfo;
class Player;
class Task;
class Skill;
class Weapon;
class Armor;
class Food;
class GameMaterial;
class TaskItem;
class FriendNpc;
class EnemyNpc;
class Element;

// 全局管理器
class GlobalManager {
private:
	std::shared_ptr<Player> _hero;																						// 玩家
	std::shared_ptr<EnemyNpc>_battleNpc;																				// 战斗NPC
	std::vector <std::shared_ptr< Task >> _tasks;   														            // 任务                                    


	std::vector<std::shared_ptr<SkillInfo>> skillInfoList;   														    // 技能信息列表
	std::vector<std::shared_ptr<Skill>>skillList;	  														            // 技能列表												

	std::vector<std::shared_ptr<FriendNpc>> _friendNpcs; 									    						// 友方NPC                                
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsGold;   							    		        			// 敌方NPC -- 金
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsWood;   							    		        			// 敌方NPC -- 木
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsWater;   							    		        			// 敌方NPC -- 水
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsFire;   							    		        			// 敌方NPC -- 火
	std::vector<std::shared_ptr<EnemyNpc>> _enemyNpcsEarth;   							    		        			// 敌方NPC -- 土
	std::shared_ptr<EnemyNpc> _enemyNpcsBoss;   							    		        						// boss
	std::vector<std::shared_ptr<Weapon>> _weapons;   							    		            				// 武器   
	std::vector<std::shared_ptr<Armor>> _armors;   							    		                				// 护具   
	std::vector<std::shared_ptr<Food>> _foods;       			    		                            				// 食品   
	std::vector<std::shared_ptr<GameMaterial>> _materials;   							    		            		// 材料           
	std::vector<std::shared_ptr<TaskItem>> _taskItems;   							    		                		// 任务物品 
	std::vector<std::shared_ptr<Element>> _elements;   							    		                			// 元素
	std::string _lastMap;
	// 构造函数
	GlobalManager() {
		// 初始化
		_elements.emplace_back(std::make_shared<Element>(ElementType::Gold));											// 金
		_elements.emplace_back(std::make_shared<Element>(ElementType::Wood));											// 木
		_elements.emplace_back(std::make_shared<Element>(ElementType::Water));											// 水
		_elements.emplace_back(std::make_shared<Element>(ElementType::Fire));											// 火
		_elements.emplace_back(std::make_shared<Element>(ElementType::Earth));											// 土

		// 初始化玩家
		try {
			_hero = std::make_shared<Player>();																			// 玩家
			if(_hero==nullptr){
				throw std::runtime_error("Player initialization failed: null pointer");
			}
		}
		catch (const std::exception& e) {
			CCLOG("Exception during initialization: %s", e.what());
			throw;
		}
		// 初始化任务 
		_tasks.emplace_back(std::make_shared<Task>(MAIN_TASK, MAIN_TASK_DESCRIPTION, SIDE_TASK_ONE_REWARD));					// 主线任务
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_ONE, SIDE_TASK_ONE_DESCRIPTION,SIDE_TASK_ONE_REWARD));				// 副任务1
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_TWO, SIDE_TASK_TWO_DESCRIPTION,SIDE_TASK_TWO_REWARD));				// 副任务2
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_THREE,SIDE_TASK_THREE_DESCRIPTION,SIDE_TASK_THREE_REWARD));		// 副任务3
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_FOUR, SIDE_TASK_FOUR_DESCRIPTION,SIDE_TASK_FOUR_REWARD));			// 副任务4
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_FIVE, SIDE_TASK_FIVE_DESCRIPTION,SIDE_TASK_FIVE_REWARD));			// 副任务5 
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SIX, SIDE_TASK_SIX_DESCRIPTION, SIDE_TASK_SIX_REWARD));			// 副任务6		
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SEVEN, SIDE_TASK_SEVEN_DESCRIPTION, SIDE_TASK_SEVEN_REWARD));		// 副任务7	
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_EIGHT, SIDE_TASK_EIGHT_DESCRIPTION, SIDE_TASK_EIGHT_REWARD));		// 副任务8
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_NINE, SIDE_TASK_NINE_DESCRIPTION, SIDE_TASK_NINE_REWARD));			// 副任务9
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_TEN, SIDE_TASK_TEN_DESCRIPTION, SIDE_TASK_TEN_REWARD));			// 副任务10
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_ELEVEN, SIDE_TASK_ELEVEN_DESCRIPTION, SIDE_TASK_ELEVEN_REWARD));	// 副任务11	
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SHIER, SIDE_TASK_SHIER_DESCRIPTION, SIDE_TASK_SHIER_REWARD));		// 副任务12
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SHISAN, SIDE_TASK_SHISAN_DESCRIPTION, SIDE_TASK_SHISAN_REWARD));	// 副任务13
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SHISI, SIDE_TASK_SHISI_DESCRIPTION, SIDE_TASK_SHISI_REWARD));		// 副任务14
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SHIWU, SIDE_TASK_SHIWU_DESCRIPTION, SIDE_TASK_SHIWU_REWARD));		// 副任务14
		_tasks.emplace_back(std::make_shared<Task>(SIDE_TASK_SHILIU, SIDE_TASK_SHILIU_DESCRIPTION, SIDE_TASK_SHILIU_REWARD));	// 副任务14

		_tasks.emplace_back(std::make_shared<Task>(NON_TASK, NON_TASK_DESCRIPTION, SIDE_TASK_ONE_REWARD));						// 无任务

		// 初始化友方NPC
		_friendNpcs.emplace_back(std::make_shared<FriendNpc>(PRINCESS));														// 公主
		_friendNpcs.emplace_back(std::make_shared<FriendNpc>(KING));															// 国王
		_friendNpcs.emplace_back(std::make_shared<FriendNpc>(FishStoreManager));												// 鱼商
		_friendNpcs.emplace_back(std::make_shared<FriendNpc>(WeaponStoreManager));												// 武器商
		_friendNpcs.emplace_back(std::make_shared<FriendNpc>(VegetableStoreManager));											// 蔬菜商
		_friendNpcs.emplace_back(std::make_shared<FriendNpc>(OreStoreManager));													// 矿石商

		// 初始化技能
		skillInfoList.emplace_back(std::make_shared<SkillInfo>(SkillInfo{ "Element_Surge",  5,  90.0f,500.0f,"fire.plist" }));			//技能:Element_Surge
		skillInfoList.emplace_back(std::make_shared<SkillInfo>(SkillInfo{ "Element_Torrent",10,  200.0f,360.0f,"fire1.plist" }));		//技能:Element_Torrent
		skillInfoList.emplace_back(std::make_shared<SkillInfo>(SkillInfo{ "Energy_Vortex",  10,  300.0f,60.0f,"fireball2.plist" }));	//技能:Energy_Vortex 
		skillInfoList.emplace_back(std::make_shared<SkillInfo>(SkillInfo{ "Element_Surge",  5,  50.0f,500.0f,"enemyskill1.plist" }));	//技能:Element_Surge
		skillInfoList.emplace_back(std::make_shared<SkillInfo>(SkillInfo{ "Element_Torrent",10,  100.0f,360.0f,"enemyskill2.plist" }));	//技能:Element_Torrent
		skillInfoList.emplace_back(std::make_shared<SkillInfo>(SkillInfo{ "Energy_Vortex",  10,  150.0f,60.0f,"enemyskill3.plist" }));	//技能:Energy_Vortex 

		// 初始化技能
		std::shared_ptr<Skill> skill0 = std::make_shared<Skill>(*skillInfoList.at(0));											// 低级技能
		std::shared_ptr<Skill> skill1 = std::make_shared<Skill>(*skillInfoList.at(1));											// 中级技能
		std::shared_ptr<Skill> skill2 = std::make_shared<Skill>(*skillInfoList.at(2));											// 高级技能
		std::shared_ptr<Skill> enemyskill1 = std::make_shared<Skill>(*skillInfoList.at(3));										// 低级技能
		std::shared_ptr<Skill> enemyskill2 = std::make_shared<Skill>(*skillInfoList.at(4));										// 中级技能
		std::shared_ptr<Skill> enemyskill3 = std::make_shared<Skill>(*skillInfoList.at(5));										// 高级技能 
		try {
			if (skill0 == nullptr) {
				throw std::runtime_error("Skill0 initialization failed: null pointer");
			}
			if (skill1 == nullptr) {
				throw std::runtime_error("Skill1 initialization failed: null pointer");
			}
			if (skill2 == nullptr) {
				throw std::runtime_error("Skill2 initialization failed: null pointer");
			}
			if (enemyskill1 == nullptr) {
				throw std::runtime_error("Skill3 initialization failed: null pointer");
			}
			if (enemyskill2 == nullptr) {
				throw std::runtime_error("Skill4 initialization failed: null pointer");
			}
			if (enemyskill3 == nullptr) {
				throw std::runtime_error("Skill5 initialization failed: null pointer");
			}
		}
		catch (const std::exception& e) {
			CCLOG("Exception during initialization: %s", e.what());
			throw;
		}
		// 技能列表
		skillList.emplace_back(skill0);
		skillList.emplace_back(skill1);
		skillList.emplace_back(skill2);
		skillList.emplace_back(enemyskill1);
		skillList.emplace_back(enemyskill2);
		skillList.emplace_back(enemyskill3);

		// 金
		_enemyNpcsGold.emplace_back(std::make_shared<EnemyNpc>(ElementType::Gold, 1, enemyskill1, "gold1monster1.png"));
		_enemyNpcsGold.emplace_back(std::make_shared<EnemyNpc>(ElementType::Gold, 2, enemyskill2, "gold1monster2.png"));
		// 木
		_enemyNpcsWood.emplace_back(std::make_shared<EnemyNpc>(ElementType::Wood, 1, enemyskill1, "enemywood1.png"));
		_enemyNpcsWood.emplace_back(std::make_shared<EnemyNpc>(ElementType::Wood, 2, enemyskill2, "enemywood2.png"));
		// 土
		_enemyNpcsEarth.emplace_back(std::make_shared<EnemyNpc>(ElementType::Earth, 1, enemyskill1, "enemyearth1.png"));
		_enemyNpcsEarth.emplace_back(std::make_shared<EnemyNpc>(ElementType::Earth, 2, enemyskill2, "enemyearth2.png"));
		// 水
		_enemyNpcsWater.emplace_back(std::make_shared<EnemyNpc>(ElementType::Water, 1, enemyskill1, "whole3monster1.png"));
		_enemyNpcsWater.emplace_back(std::make_shared<EnemyNpc>(ElementType::Water, 2, enemyskill2, "whole3monster2.png"));
		// 火
		_enemyNpcsFire.emplace_back(std::make_shared<EnemyNpc>(ElementType::Fire, 1, enemyskill1, "firemonster1.png"));
		_enemyNpcsFire.emplace_back(std::make_shared<EnemyNpc>(ElementType::Fire, 2, enemyskill2, "firemonster2.png"));

		// 初始化Boss
		ElementType type = _hero->getElement();
		_enemyNpcsBoss = std::make_shared<EnemyNpc>(type, 3, enemyskill3, "enemyboss.png");

		//初始化武器
		_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_RING));									    //武器1
		_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_CRYSTAL));									    //武器2	
		_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_SCROLL));									    //武器3

		_armors.emplace_back(std::make_shared<Armor>(HELMET));											    //头盔
		_armors.emplace_back(std::make_shared<Armor>(ARMOR));											    //护甲
		_armors.emplace_back(std::make_shared<Armor>(SHOES));											    //鞋子

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
		
		// 上一个地图
		_lastMap = "";
	}

public:

	// 获取全局管理器实例
	static GlobalManager& getInstance() {
		static GlobalManager instance;
		return instance;
	}
	
	void setBattleNpc(std::shared_ptr<EnemyNpc> npc) { _battleNpc = npc; }														// 设置战斗NPC
	void setLastMap(std::string map) { _lastMap = map; }																		// 设置上一个地图
	
	// 获取成员变量  
	std::shared_ptr<Player> getPlayer() const { return _hero; }																	// 获取玩家
	const std::vector<std::shared_ptr<Task>>& getTasks() const { return _tasks; }												// 获取任务
	const std::vector<std::shared_ptr<SkillInfo>>& getSkillInfos() const { return skillInfoList; }								// 获取技能信息
	const std::vector<std::shared_ptr<Skill>>& getSkills() const { return skillList; }											// 获取技能
	const std::vector<std::shared_ptr<FriendNpc>>& getFriendNpcs() const { return _friendNpcs; }								// 获取友方NPC
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsGold() const { return _enemyNpcsGold; }							// 获取敌方NPC -- 金
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsWood() const { return _enemyNpcsWood; }							// 获取敌方NPC -- 木
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsWater() const { return _enemyNpcsWater; }							// 获取敌方NPC -- 水
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsFire() const { return _enemyNpcsFire; }							// 获取敌方NPC -- 火
	const std::vector<std::shared_ptr<EnemyNpc>>& getEnemyNpcsEarth() const { return _enemyNpcsEarth; }							// 获取敌方NPC -- 土
	const std::shared_ptr<EnemyNpc> getEnemyNpcsBoss() const { return _enemyNpcsBoss; }											// 获取boss
	const std::vector<std::shared_ptr<Weapon>>& getWeapons() const { return _weapons; }											// 获取武器
	const std::vector<std::shared_ptr<Armor>>& getArmors() const { return _armors; }											// 获取护具
	const std::vector<std::shared_ptr<Food>>& getFoods() const { return _foods; }												// 获取食品
	const std::vector<std::shared_ptr<GameMaterial>>& getMaterials() const { return _materials; }								// 获取材料
	const std::vector<std::shared_ptr<TaskItem>>& getTaskItems() const { return _taskItems; }									// 获取任务物品
	const std::vector<std::shared_ptr<Element>>& getElements() const { return _elements; }										// 获取元素
	const std::shared_ptr<EnemyNpc> getBattleNpc() const { return _battleNpc; }													// 获取战斗NPC
	std::string getLastMap() const { return _lastMap; }													     					// 获取上一个地图
	
	// 防止拷贝构造和赋值
	GlobalManager(const GlobalManager&) = delete;
	GlobalManager& operator=(const GlobalManager&) = delete;

	// 析构函数
	~GlobalManager() {}
};
#endif // GLOBAL_MANAGER_H
