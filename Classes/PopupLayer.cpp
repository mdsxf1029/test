#include "PopupLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
//背包弹窗
PopupLayer::PopupLayer() : _messageLabel(nullptr) {
}

PopupLayer::~PopupLayer() {
}

bool PopupLayer::init(const std::string& message) {
    if (!LayerColor::init()) {
        return false;
    }

                                                                                                                // 设置背景颜色和透明度
    this->setColor(Color3B(0, 0, 255));                                                                         // 背景颜色为蓝色
    this->setOpacity(255);                                                                                      // 设置透明度
    this->setContentSize(Size(400, 222));                                                                       // 设置弹窗的大小
    this->setPosition(Vec2(600, 444));                                                                          // 设置弹窗的位置（根据需要调整）
                                                                                                                // 创建消息标签，使用自定义字体
    _messageLabel = Label::createWithTTF(message, "fonts/Arial.ttf",30);                                        // 设置字体大小
                                                                                                                // 获取屏幕中心
    _messageLabel->setPosition(Vec2(200, 111));

    _messageLabel->setTextColor(Color4B::YELLOW);                                                               // 设置字体颜色
    _messageLabel->setOpacity(255);                                                                             // 设置透明度
    this->addChild(_messageLabel,99);
    CCLOG("Showing popup with message: ZITI%s", message.c_str());                                               // 确保这条日志被打印出来
                                                                                                                // 创建关闭按钮
    auto closeButton = ui::Button::create("CloseNormal.png");
    closeButton->setPosition(Vec2(200, 0));                                                                     // 设置关闭按钮的位置
    closeButton->addClickEventListener([=](Ref* sender) {
        this->removeFromParent();                                                                               // 关闭弹窗
        });
    this->addChild(closeButton);

    return true;
}

PopupLayer* PopupLayer::create(const std::string& message) {
    PopupLayer* ret = new PopupLayer();
    if (ret && ret->init(message)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}
