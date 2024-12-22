#include "TaskMenu.h"
#include "ui/UIScrollView.h"
#include "ui/UIButton.h"

USING_NS_CC;

bool TaskMenu::init()
{
	if (!Layer::init())
	{
		CCLOGERROR("TaskMenu::init: Failed to initialize Layer.");
		return false;
	}

	// 从 GlobalManager 获取任务列表
	const auto& taskList = GlobalManager::getInstance().getTasks();
	tasks = taskList;																		// 存储任务列表

	createTaskMenu();

	return true;
}

void TaskMenu::createTaskMenu()
{
	// 设置任务菜单背景
	auto menuBg = LayerColor::create(Color4B(0, 0, 0, 180), 200, 200);						// 宽200，高300
	if (!menuBg)
	{
		CCLOGERROR("TaskMenu::createTaskMenu: Failed to create menu background.");
	}

	Vec2 center = Director::getInstance()->getVisibleSize() / 2;
	menuBg->setPosition(Director::getInstance()->getVisibleSize().width / 2+750, 
						Director::getInstance()->getVisibleSize().height / 2+300);			// 位于右上角
	this->addChild(menuBg);

	// 滑动视图
	auto scrollView = ui::ScrollView::create();
	if (!scrollView)
	{
		CCLOGERROR("TaskMenu::createTaskMenu: Failed to create ScrollView.");
	}

	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setContentSize(Size(200, 200));												// 滑动视图尺寸与背景一致
	scrollView->setInnerContainerSize(Size(200, tasks.size() * 40));						// 假设有更多内容
	scrollView->setPosition(Vec2(0, 0));
	menuBg->addChild(scrollView);

	// 设置滑动条样式
	scrollView->setScrollBarEnabled(true);													// 启用滑动条
	scrollView->setScrollBarColor(Color3B::WHITE);											// 设置滑动条颜色
	scrollView->setScrollBarOpacity(300);													// 设置滑动条透明度
	scrollView->setScrollBarAutoHideEnabled(false);

	// 添加任务项
	for (size_t i = 0; i < tasks.size(); ++i)
	{
		auto task = tasks[i];
		
		if (task->state >= 0)
		{
			// 创建按钮
			auto taskButton = ui::Button::create("UI/UI_Flat_Bar01a.png", "UI/UI_Flat_Bar01a.png");
			if (!taskButton)
			{
				CCLOGERROR("TaskMenu::createTaskMenu: Failed to create task button for Task %d.", i + 1);
				continue;
			}


			// 设置按钮放大
			taskButton->setScale(6.0);															// 放大按钮图片的比例

			// 计算按钮位置
			Vec2 buttonPosition = Vec2(100, scrollView->getInnerContainerSize().height - (i * 40) - 50);
			taskButton->setPosition(buttonPosition);																// 设置按钮位置

			// 添加按钮点击事件
			taskButton->addClickEventListener([=](Ref* sender) {
				this->showTaskDetails("Task details: \n" + task->getTaskDescription());
				});

			// 将按钮添加到滚动视图中
			scrollView->addChild(taskButton);

			// 创建 Label 并设置其位置（放在按钮底部）
			auto label = Label::createWithSystemFont(task->getTaskName(), "Arial", 12);								// 使用合适的字体和大小
			label->setTextColor(Color4B::BLACK);
			label->setPosition(Vec2(buttonPosition.x, buttonPosition.y - taskButton->getContentSize().height / 2));  // 调整 Label 的位置
			scrollView->addChild(label);
		}
	}
}

void TaskMenu::showTaskDetails(const std::string& taskDetails)
{
	// 弹窗
	auto detailLayer = LayerColor::create(Color4B(50, 50, 50, 230), 200, 200);
	if (!detailLayer)
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create detail layer.");
	}

	detailLayer->setAnchorPoint(Vec2(0.5, 0.5));
	detailLayer->setPosition(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height / 2);
	this->addChild(detailLayer);

	auto closeButton = ui::Button::create("UI/X.png");
	if (!closeButton)
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create close button.");
	} 

	closeButton->setPosition(Vec2(200, 200));
	closeButton->addClickEventListener([=](Ref* sender) {
		detailLayer->removeFromParent();
		});
	detailLayer->addChild(closeButton);

	auto detailLabel = Label::createWithSystemFont(taskDetails, "fonts/arial.ttf", 12);
	if (!detailLabel)
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create detail label.");
	}

	detailLabel->setPosition(Vec2(150,100));
	detailLabel->setColor(Color3B::WHITE);
	detailLayer->addChild(detailLabel);
}