
#include "manager.h"

// 初始化
void GlobalManager::initializeElements() {
	// 初始化元素 
	_elements.emplace_back(std::make_shared<Element>(ElementType::Gold));				// 金
	_elements.emplace_back(std::make_shared<Element>(ElementType::Wood));				// 木
	_elements.emplace_back(std::make_shared<Element>(ElementType::Water));				// 水
	_elements.emplace_back(std::make_shared<Element>(ElementType::Fire));				// 火
	_elements.emplace_back(std::make_shared<Element>(ElementType::Earth));				// 土
}
void GlobalManager::initializePlayer() {

	// 初始化玩家
	_hero = std::make_shared<Player>();										// 玩家
}
void GlobalManager::initializeTasks() {
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
}
void GlobalManager::initializeSkills() {
	// 初始化技能
	_lowLevelSkills.emplace_back(std::make_shared<LowLevelSkill>(ELEMENT_SURGE));					// 低级技能
	_midLevelSkills.emplace_back(std::make_shared<MidLevelSkill>(Elemental_Torrent));				// 中级技能
	_highLevelSkills.emplace_back(std::make_shared<HighLevelSkill>(Energy_Vortex));					// 高级技能
	_highLevelSkills.emplace_back(std::make_shared<HighLevelSkill>(Arcane_Blast));					// 组合技能
}
void GlobalManager::initializeFriendNpcs() {
	// 初始化友方NPC
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(PRINCESS));								// 公主
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(KING));									// 国王
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(FishStoreManager));						// 鱼商
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(WeaponStoreManager));						// 武器商
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(VegetableStoreManager));					// 蔬菜商
	_friendNpcs.emplace_back(std::make_shared<FriendNpc>(OreStoreManager));							// 矿石商
}
void GlobalManager::initializeEnemyNpcs() {
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
}
void GlobalManager::initializeWeapons() {
	// 初始化物品
	// 武器
	_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_RING));
	_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_CRYSTAL));
	_weapons.emplace_back(std::make_shared<Weapon>(MAGIC_SCROLL));
}
void GlobalManager::initializeArmors() {
	// 护具
	_armors.emplace_back(std::make_shared<Armor>(HELMET));
	_armors.emplace_back(std::make_shared<Armor>(ARMOR));
	_armors.emplace_back(std::make_shared<Armor>(SHOES));
}
void GlobalManager::initializeFoods() {

	// 食品
	_foods.emplace_back(std::make_shared<Food>(FISH));													//鱼
	_foods.emplace_back(std::make_shared<Food>(FRUIT));													//水果
	_foods.emplace_back(std::make_shared<Food>(VEGETABLE));												//蔬菜
	_foods.emplace_back(std::make_shared<Food>(HERB));													//草药
	_foods.emplace_back(std::make_shared<Food>(MEAT));													//肉
	_foods.emplace_back(std::make_shared<Food>(MUSHROOM));												//蘑菇
	_foods.emplace_back(std::make_shared<Food>(RICE));													//稻谷
	_foods.emplace_back(std::make_shared<Food>(APPLE));													//苹果
}

void GlobalManager::initializeMaterials() {
	// 材料
	_materials.emplace_back(std::make_shared<GameMaterial>(TREE));										//树
	_materials.emplace_back(std::make_shared<GameMaterial>(WOOD));										//木头
	_materials.emplace_back(std::make_shared<GameMaterial>(STONE));										//石头
	_materials.emplace_back(std::make_shared<GameMaterial>(GOLD_MINE));									//金矿
	_materials.emplace_back(std::make_shared<GameMaterial>(CHEST));										//宝箱
}
void GlobalManager::initializeTaskItems() {
	_taskItems.emplace_back(std::make_shared<TaskItem>(KEY));											//钥匙
	_taskItems.emplace_back(std::make_shared<TaskItem>(LETTER));										//信件
}
void GlobalManager::initializeBag() {
	_bag = std::make_shared<Inventory>();																//背包
}