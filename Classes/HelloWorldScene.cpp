/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h" 
#include "SimpleAudioEngine.h"  
#include <ChooseElement.h>
#include <Map/SettingScene.h>
#include "Map/MiniMap.h"
#include <ui/UITextField.h>


USING_NS_CC;
// 玩家昵称

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// 打印有用的错误信息，而不是在文件不存在时发生段错误  
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    // 1. super init first  
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////  
    // 2. 添加一个带有 "X" 图像的菜单项，点击它可以退出程序  
    //    您可以自行修改。  

    // 关闭按钮  
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' 和 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // 创建菜单，它是一个 autorelease 对象  
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 3. 在此处添加更多代码...  

    // 开始精灵  
    Sprite* startSpriteNormal = Sprite::create("play-up.png");
    Sprite* startSpriteSelected = Sprite::create("play-down.png");

    if (startSpriteNormal == nullptr || startSpriteSelected == nullptr)
    {
        problemLoading("'play-up.png' 或 'play-down.png'");
    }
    else
    {
        auto startMenuItem = MenuItemSprite::create(startSpriteNormal, startSpriteSelected, CC_CALLBACK_1(HelloWorld::menuItem1Callback1, this));
        float x = origin.x + visibleSize.width - startMenuItem->getContentSize().width / 2 - 100;           // 调整位置以避免与关闭按钮重叠  
        float y = origin.y + startMenuItem->getContentSize().height / 2 + 50;
        startMenuItem->setPosition(Vec2(x, y));
        Menu* mu = Menu::create(startMenuItem, NULL);
        mu->setPosition(Vec2::ZERO);
        this->addChild(mu);
    }

    // 救公主的标题  
    auto label = Label::createWithTTF("Save the Princess", "fonts/Marker Felt.ttf", 36);                    // 字体大小调整为合理范围  
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // 将标签放置在屏幕顶部中心  
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));
        // 添加标签为子节点  
        this->addChild(label, 1);
    }

    // 救公主图片  
    auto sprite = Sprite::create("SavePrincess.png");
    if (sprite == nullptr)
    {
        problemLoading("'SavePrincess.png'");
    }
    else
    {
        // 将精灵置于屏幕中心稍偏上方  
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x - 20, visibleSize.height / 2 + origin.y + 100));
        // 添加精灵为子节点  
        this->addChild(sprite, 0);
    }

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    // 关闭 cocos2d-x 游戏场景并退出应用程序  
    Director::getInstance()->end();

    /* 如果需要在不退出应用程序的情况下，导航回原生 iOS 屏幕（如果存在），请不要使用上面的 Director::getInstance()->end()，而是触发在 RootViewController.mm 中创建的自定义事件，如下所示 */

    // EventCustom customEndEvent("game_scene_close_event");  
    // _eventDispatcher->dispatchEvent(&customEndEvent);  
}

// 初始界面点击 play 后的响应  
void HelloWorld::menuItem1Callback1(Ref* pSender)
{
    MenuItem* item = dynamic_cast<MenuItem*>(pSender);
    if (item)
    {
        log("Touch Help Menu Item %p", item);

        // 在点击 Play 后弹出昵称输入弹窗
        auto ChooseElementLayer = ChooseElementLayer::create();

        Director::getInstance()->getRunningScene()->addChild(ChooseElementLayer);  // 添加到顶层场景         
    }
}
