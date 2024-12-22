#include <locale>
#include <codecvt>
#include "ui/CocosGUI.h"
#include "ChooseElement.h"
#include "Sets/manager.h"
#include "Map/MiniMap.h"
#include "NicknameLayer.h"

std::shared_ptr<Player> player2 = GlobalManager::getInstance().getPlayer();

bool ChooseElementLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto bg = LayerColor::create(Color4B::WHITE, 2000, 1000);
	bg->setPosition(Vec2(0, 0));                                                                    // 背景层位置
	this->addChild(bg);
	createChooseUI();

	return true;
}

ChooseElementLayer* ChooseElementLayer::create() {
    ChooseElementLayer* ret = new ChooseElementLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

void ChooseElementLayer::createChooseUI()
{
    // 提示玩家选择元素
    auto instructionLabel = Label::createWithSystemFont("Please Choose One", "fonts/arial", 36);
    instructionLabel->setPosition(Vec2(1000, 700));                                                 // 居中偏上的位置
    instructionLabel->setColor(Color3B::BLACK);
    this->addChild(instructionLabel);

    // 定义五个元素的名称、图片文件和对应的 ElementType
    std::vector<std::tuple<std::string, std::string, ElementType>> elements = {
        {"GOLD", "GOLD1.png", ElementType::Gold},
        {"WOOD", "WOOD1.png", ElementType::Wood},
        {"WATER", "WATER1.png", ElementType::Water},
        {"FIRE", "FIRE.png", ElementType::Fire},
        {"EARTH", "EARTH.png", ElementType::Earth}
    };

    // 设置每个按钮的位置
    float startX = 500;
    float startY = 400;
    float spacing = 300;                                                                            // 按钮之间的间距

    // 图片和按钮的大小
    float buttonSize = 120.0f;                                                                      // 按钮的大小
    float imageSize = 400.0f;                                                                       // 图片的大小

    for (size_t i = 0; i < elements.size(); ++i)
    {
        // 创建按钮
        auto button = ui::Button::create("UI/X.png", "UI/X.png");
        button->setPosition(Vec2(startX + i * spacing, startY+75));
        button->setContentSize(Size(buttonSize, buttonSize));                                       // 设置按钮大小


        // 创建人物图像
        auto sprite = Sprite::create(std::get<1>(elements[i]));
        sprite->setPosition(Vec2(startX + i * spacing, startY - 150));                                  // 图片稍微低一些
        sprite->setContentSize(Size(imageSize, imageSize));                                             // 设置图片大小


        // 创建标签
        auto elementLabel = Label::createWithSystemFont(std::get<0>(elements[i]), "Arial", 24);
        elementLabel->setPosition(Vec2(startX + i * spacing, startY + 150));                            // 标签在按钮上方
        elementLabel->setColor(Color3B::BLACK);

        // 按钮点击事件
        button->addClickEventListener([this, i, elements](Ref* sender) {
            // 设置选择的元素
            player2->setPlayerElement(std::get<2>(elements[i]));                                        // 设置玩家的元素类型

            // 设置人物形象
            std::string imageName = std::get<1>(elements[i]);                                           // 获取对应的元素图片
            player2->setCharacterImage(imageName);                                                      // 假设有这个方法来设置人物形象
            // 切换场景
            auto nicknameLayer = NicknameLayer::create();
            Director::getInstance()->getRunningScene()->addChild(nicknameLayer);                        // 添加到顶层场景
            });

        // 将按钮、图像和标签添加到场景中
		this->addChild(button);                                                                         // 添加按钮
		this->addChild(sprite);     													                // 添加图片                
		this->addChild(elementLabel);       									                        // 添加标签                      

        // Close the popup (remove this layer)
        this->removeFromParentAndCleanup(true);  // This will remove the layer from parent and clean up
    }
}
