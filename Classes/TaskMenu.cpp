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

	CCLOG("TaskMenu::init: Successfully initialized Layer.");
	this->createTaskMenu();
	return true;
}

void TaskMenu::createTaskMenu()
{
	CCLOG("TaskMenu::createTaskMenu: Creating task menu.");

	// 设置任务菜单背景
	auto menuBg = LayerColor::create(Color4B(0, 0, 0, 180), 800, 900);                     // 宽200，高300
	if (!menuBg)
	{
		CCLOGERROR("TaskMenu::createTaskMenu: Failed to create menu background.");
	}

	Vec2 center = Director::getInstance()->getVisibleSize() / 2;
	menuBg->setPosition(Director::getInstance()->getVisibleSize().width / 2+3550, 
						Director::getInstance()->getVisibleSize().height / 2+1000);    // 位于右上角
	this->addChild(menuBg);
	CCLOG("TaskMenu::createTaskMenu: Menu background created at position (%.2f, %.2f).",
		menuBg->getPositionX(), menuBg->getPositionY());

	// 滑动视图
	auto scrollView = ui::ScrollView::create();
	if (!scrollView)
	{
		CCLOGERROR("TaskMenu::createTaskMenu: Failed to create ScrollView.");
	}

	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->setContentSize(Size(800, 900));                                          // 滑动视图尺寸与背景一致
	scrollView->setInnerContainerSize(Size(800, taskNames.size() * 200));                  // 假设有更多内容
	scrollView->setPosition(Vec2(0, 0));
	menuBg->addChild(scrollView);
	CCLOG("TaskMenu::createTaskMenu: ScrollView created with content size (200, 300).");

	// 设置滑动条样式
	scrollView->setScrollBarEnabled(true);                       // 启用滑动条
	scrollView->setScrollBarColor(Color3B::WHITE);               // 设置滑动条颜色
	scrollView->setScrollBarOpacity(300);                        // 设置滑动条透明度
	scrollView->setScrollBarAutoHideEnabled(false);

	// 添加任务项
	for (int i = 0; i < taskNames.size(); ++i)
	{
		// 创建按钮
		auto taskButton = ui::Button::create("UI/UI_Flat_Bar01a.png", "UI/UI_Flat_Bar01a.png");
		if (!taskButton)
		{
			CCLOGERROR("TaskMenu::createTaskMenu: Failed to create task button for Task %d.", i + 1);
			continue;
		}

		// 设置按钮放大
		taskButton->setScale(5.0);  // 放大按钮图片的比例

		// 计算按钮位置
		Vec2 buttonPosition = Vec2(400, scrollView->getInnerContainerSize().height - (i * 180) - 90);
		taskButton->setPosition(buttonPosition);

		// 添加按钮点击事件
		taskButton->addClickEventListener([=](Ref* sender) {
			CCLOG("TaskMenu::createTaskMenu: Task %d button clicked.", i + 1);
			this->showTaskDetails("Task details: " + taskNames[i]);
			});

		// 将按钮添加到滚动视图中
		scrollView->addChild(taskButton);

		// 创建 Label 并设置其位置（放在按钮底部）
		auto label = Label::createWithSystemFont(taskNames[i], "Arial", 60);  // 使用合适的字体和大小
		label->setTextColor(Color4B::BLACK);
		label->setPosition(Vec2(buttonPosition.x, buttonPosition.y - taskButton->getContentSize().height / 2));  // 调整 Label 的位置
		scrollView->addChild(label);

		CCLOG("TaskMenu::createTaskMenu: Task %d button created at position (%.2f, %.2f).", i + 1, buttonPosition.x, buttonPosition.y);
	}


	/*// 添加任务项
	for (int i = 0; i < taskNames.size(); ++i)
	{
		auto taskButton = ui::Button::create("UI/UI_Flat_Bar01a.png", "UI/UI_Flat_Bar01a.png");  // 还没找具体图片
		if (!taskButton)
		{
			CCLOGERROR("TaskMenu::createTaskMenu: Failed to create task button for Task %d.", i + 1);
			continue;
		}

		taskButton->setScale(4.0); // 将按钮图片放大1.5倍
		auto label = Label::createWithSystemFont(taskNames[i], "Arial", 50);
		label->setTextColor(Color4B::WHITE);
		label->setPosition(Vec2(100, scrollView->getInnerContainerSize().height - (i * 180) - 90));
		scrollView->addChild(label);
		/*taskButton->setTitleText(taskNames[i]);
		taskButton->setTitleFontSize(30);
		taskButton->setTitleColor(Color3B::BLACK);
		taskButton->setPosition(Vec2(370, scrollView->getInnerContainerSize().height - (i * 180) - 90));                          // 动态计算位置
		taskButton->addClickEventListener([=](Ref* sender) {
			CCLOG("TaskMenu::createTaskMenu: Task %d button clicked.", taskNames[i].c_str());
			this->showTaskDetails("Task detals: " + taskNames[i]);
			});
		scrollView->addChild(taskButton);
		CCLOG("TaskMenu::createTaskMenu: Task %d button created at position (%.2f, %.2f).",
			taskNames[i].c_str(), taskButton->getPositionX(), taskButton->getPositionY());
	}*/
}

void TaskMenu::showTaskDetails(const std::string& taskDetails)
{
	// 弹窗
	auto detailLayer = LayerColor::create(Color4B(50, 50, 50, 230), 1500, 1000);
	if (!detailLayer)
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create detail layer.");
	}

	detailLayer->setPosition(Director::getInstance()->getVisibleSize().width / 2+500,
		Director::getInstance()->getVisibleSize().height / 2);
	this->addChild(detailLayer);
	CCLOG("TaskMenu::showTaskDetails: Detail layer created at position (%.2f, %.2f).",
		detailLayer->getPositionX(), detailLayer->getPositionY());

	auto closeButton = ui::Button::create("UI/X.png");
	if (!closeButton)
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create close button.");
	} 

	closeButton->setPosition(Vec2(1500, 990));
	closeButton->addClickEventListener([=](Ref* sender) {
		CCLOG("TaskMenu::showTaskDetails: Close button clicked, removing detail layer.");
		detailLayer->removeFromParent();
		});
	detailLayer->addChild(closeButton);
	CCLOG("TaskMenu::showTaskDetails: Close button added to detail layer.");

	auto detailLabel = Label::createWithSystemFont(taskDetails, "fonts/arial.ttf", 60);
	if (!detailLabel)
	{
		CCLOGERROR("TaskMenu::showTaskDetails: Failed to create detail label.");
	}

	detailLabel->setPosition(Vec2(875, 500));
	detailLabel->setColor(Color3B::WHITE);
	detailLayer->addChild(detailLabel);
	CCLOG("TaskMenu::showTaskDetails: Detail label added with text: %s", taskDetails.c_str());
}