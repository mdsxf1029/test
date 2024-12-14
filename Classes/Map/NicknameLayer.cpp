#include "NicknameLayer.h"
#include "ui/CocosGUI.h"
#include "SettingScene.h"
#include <locale>
#include <codecvt>

using cocos2d::ui::TextField;
using cocos2d::ui::Button;
USING_NS_CC;
//³õÊ¼µÇÂ¼µ¯´°
std::string g_PlayerName = "";

NicknameLayer::NicknameLayer() : _textField(nullptr) {}

NicknameLayer::~NicknameLayer() {}

bool NicknameLayer::init() {
    if (!LayerColor::init()) {
        CCLOG("NicknameLayer initialization failed");
        return false;
    }

    // Set background color and opacity
    this->setColor(Color3B(0, 0, 225));  // Set background color to blue
    this->setOpacity(180);  // Set opacity
    this->setContentSize(Size(5000, 3000));  // Set popup size
    this->setPosition(Vec2(3500, 1000));  // Set popup position

    CCLOG("Popup Layer size: %f x %f, position: %f, %f", this->getContentSize().width, this->getContentSize().height, this->getPositionX(), this->getPositionY());

    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();

    // Create the text field for user to input the nickname
    _textField = TextField::create("Enter your nickname", "../Resources/Fonts/arial.ttf", 100);
    _textField->setContentSize(Size(600, 100));  // Set larger text field size to ensure text fits
    _textField->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));  // Set position at the center of the screen
    _textField->setMaxLength(20);  // Set maximum character length
    _textField->setMaxLengthEnabled(true);
    _textField->setTextColor(cocos2d::Color4B(255, 255, 255, 255));  // Set text color to white
    this->addChild(_textField);

    // Create a label for showing the nickname or prompt message
    auto promptLabel = Label::createWithTTF("Enter your nickname", "../Resources/Fonts/arial.ttf", 50);
    promptLabel->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 - 200));  // Set label position
    promptLabel->setTextColor(cocos2d::Color4B(255, 0, 0, 255));  // Set prompt text color to red
    this->addChild(promptLabel);

    // Add event listener for the text field
    _textField->addEventListener([promptLabel](Ref* sender, TextField::EventType type) {
        if (type == TextField::EventType::INSERT_TEXT || type == TextField::EventType::DELETE_BACKWARD) {
            auto textField = dynamic_cast<TextField*>(sender);
            std::string nickname = textField->getString();
            if (nickname.empty()) {
                promptLabel->setString("Enter your nickname");
            }
            else {
                promptLabel->setString("Welcome, " + nickname);  // Show welcome message
            }
        }
        });

    // Create confirm button
    auto confirmButton = Button::create("CloseNormal.png", "CloseSelected.png");
    confirmButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 - 350));  // Set button position
    confirmButton->addClickEventListener([=](Ref* sender) {
        std::string nickname = _textField->getString();  // Get the player's nickname
        CCLOG("Player nickname: %s", nickname.c_str());

        if (nickname.empty()) {
            promptLabel->setString("Nickname cannot be empty!");  // Show error message if nickname is empty
        }
        else if (!isValidString(nickname)) {
            promptLabel->setString("Nickname contains invalid characters!");  // Show error message if nickname contains invalid characters
        }
        else {
            g_PlayerName = nickname;  // Store the player's nickname
            CCLOG("Player nickname saved: %s", g_PlayerName.c_str());

            // Close the popup (remove this layer)
            this->removeFromParentAndCleanup(true);  // This will remove the layer from parent and clean up
            auto sc = Setting::createScene();
            Director::getInstance()->replaceScene(sc);
        }
        });
    this->addChild(confirmButton);

    return true;
}

// Check if the character is valid
bool NicknameLayer::isValidCharacter(const char32_t ch)
{
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
        return true;
    }
    if (ch >= '0' && ch <= '9') {
        return true;
    }
    if ((ch >= 0x4E00 && ch <= 0x9FFF) || (ch >= 0x3400 && ch <= 0x4DBF)) {
        return true;
    }
    return false;
}

// Check if the nickname string is valid
bool NicknameLayer::isValidString(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::u32string utf32str = converter.from_bytes(str);
    for (auto ch : utf32str) {
        if (!isValidCharacter(ch)) {
            return false;
        }
    }
    return true;
}

NicknameLayer* NicknameLayer::create() {
    NicknameLayer* ret = new NicknameLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}
