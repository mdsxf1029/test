#include "BackpackLayer.h"
#include "PopupLayer.h"
#include "ui/UIScrollView.h"
#include "manager.h"
#include "items.h"

USING_NS_CC;
std::vector<std::shared_ptr<Item>> items;
BackpackLayer::BackpackLayer()
    : _backpack(nullptr) // 默认初始化为 nullptr
{
}

BackpackLayer::~BackpackLayer()
{
}

bool BackpackLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    // 背包界面的背景颜色
    auto background = LayerColor::create(Color4B::WHITE, 3100, 2600);
    background->setPosition(Vec2(2500, 1000));  // 背包层的位置
    this->addChild(background);

    createBackpackUI();

    return true;
}



void BackpackLayer::onItemClicked(Ref* sender)
{
    // 处理物品点击事件
    CCLOG("Item clicked!");
}

// 创建背包界面 UI
void BackpackLayer::createBackpackUI()
{
    // 获取背包中所有物品（可以通过 GlobalManager 获取）
    const auto& weaponsList = GlobalManager::getInstance().getWeapons();
    const auto& armorsList = GlobalManager::getInstance().getArmors();
    const auto& foodsList = GlobalManager::getInstance().getFoods();
    const auto& materialsList = GlobalManager::getInstance().getMaterials();

    // 清空之前的物品
    items.clear();

    // 遍历所有物品并添加到 items 容器
    for (const auto& weapon : weaponsList) {
        items.push_back(weapon);  // 将 weapon 添加到 items 容器中
    }

    for (const auto& armor : armorsList) {
        items.push_back(armor);  // 将 armor 添加到 items 容器中
    }

    for (const auto& food : foodsList) {
        items.push_back(food);  // 将 food 添加到 items 容器中
    }

    for (const auto& material : materialsList) {
        items.push_back(material);  // 将 material 添加到 items 容器中
    }


    // 创建滚动视图，用于显示物品
    auto scrollView = ui::ScrollView::create();
    scrollView->setContentSize(Size(3100, 2600));  // 设置滚动视图的大小
    scrollView->setPosition(Vec2(2500, 1000));  // 设置滚动视图的位置
    scrollView->setBounceEnabled(true);  // 启用回弹效果
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);  // 垂直滚动
    this->addChild(scrollView);

    // 设置滚动视图的内部容器大小（适应所有物品）
    scrollView->setInnerContainerSize(Size(760, 1000));  // 内部容器的高度足够容纳多个物品

    // 每个按钮的宽度
    const float itemWidth = 765; // 物品按钮的宽度
    const float itemHeight = 765; // 物品按钮的高度
    const float scrollViewWidth = 3800; // 滚动视图的宽度

    // 每行可以放多少个物品
    int itemsPerRow = static_cast<int>(scrollViewWidth / itemWidth);

    // 创建物品的图标图片映射（物品名称与图片之间的对应关系）
    std::map<std::string, std::string> itemImageMap = {
     {"HELMET", "helmet.png"},
     {"ARMOR", "armor.png"},
     {"SHOES", "shoes.png"},
     {"MAGIC_RING", "magic_ring.png"},
     {"MAGIC_CRYSTAL", "magic_crystal.png"},
     {"MAGIC_SCROLL", "magic_scroll.png"},
     {"FISH", "fish.png"},
     {"FRUIT", "fruit.png"},
     {"VEGETABLE", "vegetable.png"},
     {"HERB", "herb.png"},
     {"MEAT", "meat.png"},
     {"MUSHROOM", "mushroom.png"},
     {"RICE", "rice.png"},
     {"APPLE", "apple.png"},
     {"TREE", "tree.png"},
     {"WOOD", "wood.png"},
     {"GOLD_MINE", "gold_mine.png"},
     {"STONE", "stone.png"},
     {"CHEST", "chest.png"},
     {"KEY", "key.png"},
     {"LETTER", "letter.png"}
    };

    int i = 0;
    for (const auto& item :items) {
        // 处理每个物品，获取对应图片等
        std::string itemImage = itemImageMap[item->getItemName()];

        // 计算当前物品在当前行的 x 坐标
        int row = i / itemsPerRow;
        int col = i % itemsPerRow;

        float xPos = 380 + (col * itemWidth);
        float yPos = 2200 - (row * itemHeight);

        auto itemButton = ui::Button::create(itemImage, itemImage);
        itemButton->setPosition(Vec2(xPos, yPos));
        itemButton->setTitleText(std::to_string(item->getNum()));
        itemButton->setTitleFontSize(24);

        itemButton->addClickEventListener([=](Ref* sender) {
            CCLOG("Clicked item: %s", item->getItemName().c_str());

            // 弹出物品已配备的提示框
            std::string message = "has been equipped";
            auto popup = PopupLayer::create(message);
            auto scene = Director::getInstance()->getRunningScene();
            if (scene) {
                scene->addChild(popup, 999);  // 确保弹窗显示在最上层
            }

            // 弹窗显示2秒后自动消失
            popup->runAction(Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
            });

        scrollView->addChild(itemButton);
        i++;
    }
}

// 设置背包数据（物品）
void BackpackLayer::setBackpack(Backpack* backpack)
{
    _backpack = backpack;  // 设置背包数据
    createBackpackUI();  // 更新背包 UI
}

// 创建静态的 create 方法，简化创建对象的过程
BackpackLayer* BackpackLayer::create()
{
    BackpackLayer* ret = new BackpackLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}
