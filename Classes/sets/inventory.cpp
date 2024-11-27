//2353924 冯俊财
//inverntory 为玩家的背包 的函数实现

//Inventory(int size) :size(size), items(0) {};
Inventory::~Inventory() {};

//界面
//展示背包
void Inventory::showInventory()
{
	//遍历背包
	//显示背包中的物品 png
	//显示物品的名字（鼠标点击之后，旁边的界面）
	//显示物品的数量（同上）
	//显示物品的属性（同上）  种类 效果之类
	//显示物品的等级（同上）
	//显示物品的是否装备（同上） 
}
//操作
//添加物品
bool Inventory::addItem(Item* item)
{
	if (items.size() < size)
	{
		items.push_back(item);
		item_num++;
		return true;
	}
	else
	{
		//背包满了
		return false;
	}
} 

//移除物品
void Inventory::removeItem(Item* item) 
{
	for (int i=0;i<BAG_SIZE;i++)
	{
		if (items[i] == item)
		{
			items.erase(items.begin() + i);
			item_num--;
			break;
		}
	}

}

//使用物品
void Inventory::useItem(Item* item)
{
	//使用物品
	//根据物品的种类，调用不同的函数
	//如果是武器，调用攻击函数
	//如果是护具，调用防御函数
	//如果是食品，调用回复函数
	//如果是材料，调用合成函数
	//如果是任务物品，调用任务函数
} 

//得到大小
int Inventory::getSize() 
{}

//是否满了
bool Inventory::isFull() 
{}
