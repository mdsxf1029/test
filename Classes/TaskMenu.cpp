#include "TaskMenu.h"
#include "ui/UIScrollView.h"
#include "ui/UIButton.h"

USING_NS_CC;

bool TaskMenu::init()																		// 初始化
{
	if (!Layer::init())
	{
		CCLOGERROR("TaskMenu::init: Failed to initialize Layer.");
		return false;
	}
	const auto& taskList = GlobalManager::getInstance().getTasks();							// 获取任务列表	
	tasks = taskList;																		// 存储任务列表
	createTaskMenu();																		// 创建任务菜单
	return true;
}

void TaskMenu::createTaskMenu()																// 创建任务菜单
{
	auto menuBg = LayerColor::create(Color4B(0, 0, 0, 180), 200, 200);						// 设置任务菜单背景宽200，高300
	if (!menuBg)
	{
		CCLOGERROR("TaskMenu::createTaskMenu: Failed to create menu background.");			// 创建背景失败
	}

	Vec2 center = Director::getInstance()->getVisibleSize() / 2;							// 获取屏幕中心
	menuBg->setPosition(Director::getInstance()->getVisibleSize().width / 2 + 750,			
						Director::getInstance()->getVisibleSize().height / 2+300);			// 位于右上角
	this->addChild(menuBg);																	// 添加背景

	/* 滑动视图*/
	auto scrollView = ui::ScrollView::create();												// 创建滑动视图
	if (!scrollView)
	{
		CCLOGERROR("TaskMenu::createTaskMenu: Failed to create ScrollView.");				// 创建滑动视图失败
	}

	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);							// 垂直滚动
	scrollView->setContentSize(Size(200, 200));												// 滑动视图尺寸与背景一致
	scrollView->setInnerContainerSize(Size(200, tasks.size() * 40));						// 假设有更多内容
	scrollView->setPosition(Vec2(0, 0));													// 设置滑动视图位置
	menuBg->addChild(scrollView);															// 将滑动视图添加到背景中

	/*设置滑动条样式*/ 
	scrollView->setScrollBarEnabled(true);													// 启用滑动条
	scrollView->setScrollBarColor(Color3B::WHITE);											// 设置滑动条颜色
	scrollView->setScrollBarOpacity(300);													// 设置滑动条透明度
	scrollView->setScrollBarAutoHideEnabled(false);											// 滑动条不自动隐藏

	/*添加任务项*/ 
	for (size_t i = 0; i < tasks.size(); ++i)												// 遍历任务列表
	{
		auto task = tasks[i];																// 获取第i个任务		
		if (task->state >= 0)																// 如果任务状态大于等于0
		{
			auto taskButton = ui::Button::create("UI/UI_Flat_Bar01a.png", "UI/UI_Flat_Bar01a.png");						// 创建任务按钮
			if (!taskButton)
			{
				CCLOGERROR("TaskMenu::createTaskMenu: Failed to create task button for Task %d.", i + 1);				// 创建任务按钮失败	
				continue;																								// 继续下一个任务
			}
			taskButton->setScale(6.0);														// 设置按钮放大 放大按钮图片的比例

			Vec2 buttonPosition = Vec2(100, scrollView->getInnerContainerSize().height - (i * 40) - 50);				// 计算按钮位置
			taskButton->setPosition(buttonPosition);																	// 设置按钮位置

			taskButton->addClickEventListener([=](Ref* sender) {														// 添加按钮点击事件
				this->showTaskDetails("Task details: \n" + task->getTaskDescription());									// 显示任务详情
				});

			// 将按钮添加到滚动视图中
			scrollView->addChild(taskButton);

			// 创建 Label 并设置其位置（放在按钮底部）
			auto label = Label::createWithSystemFont(task->getTaskName(), "Arial", 12);									// 使用合适的字体和大小
			label->setTextColor(Color4B::BLACK);																		// 设置字体颜色
			label->setPosition(Vec2(buttonPosition.x, buttonPosition.y - taskButton->getContentSize().height / 2));		// 调整 Label 的位置
			scrollView->addChild(label);																				// 将 Label 添加到滚动视图中
		}
	}
}

void TaskMenu::showTaskDetails(const std::string& taskDetails)										// 显示任务详情
{
	// 弹窗
	auto detailLayer = LayerColor::create(Color4B(50, 50, 50, 230), 200, 200);						// 创建一个半透明的背景
	if (!detailLayer)
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create detail layer.");					// 创建背景失败
	}

	detailLayer->setAnchorPoint(Vec2(0.5, 0.5));													// 设置锚点
	detailLayer->setPosition(Director::getInstance()->getVisibleSize().width / 2,					// 设置位置
		Director::getInstance()->getVisibleSize().height / 2);										
	this->addChild(detailLayer);																	// 添加背景

	auto closeButton = ui::Button::create("UI/X.png");												// 创建关闭按钮
	if (!closeButton)
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create close button.");					// 创建关闭按钮失败
	} 

	closeButton->setPosition(Vec2(200, 200));														// 设置关闭按钮位置
	closeButton->addClickEventListener([=](Ref* sender) {											// 添加点击事件
		detailLayer->removeFromParent();															// 移除弹窗
		});
	detailLayer->addChild(closeButton);																// 添加关闭按钮

	auto detailLabel = Label::createWithSystemFont(taskDetails, "fonts/arial.ttf", 12);				// 创建任务详情 Label
	if (!detailLabel)																				// 如果创建失败
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create detail label.");					// 创建任务详情 Label 失败
	}

	detailLabel->setPosition(Vec2(150, 100));														// 设置位置
	detailLabel->setColor(Color3B::WHITE);															// 设置颜色
	detailLayer->addChild(detailLabel);																// 添加任务详情 Label
}