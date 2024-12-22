#include "QuizGame.h"
#include "ui/CocosGUI.h"
#include"Map\MiniMap.h"
USING_NS_CC;

QuizGame* QuizGame::create()
{
	QuizGame* ret = new QuizGame();                                 // 创建游戏实例
	if (ret && ret->init())										    // 初始化游戏
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}

bool QuizGame::init()
{
    // 初始化题库
    questions.push_back({ "What is 2 + 2?", {"3", "4", "5", "6"}, 1 });
    questions.push_back({ "What is the capital of France?", {"Berlin", "Madrid", "Paris", "Rome"}, 2 });
    questions.push_back({ "Which is the largest planet?", {"Earth", "Jupiter", "Mars", "Venus"}, 1 });
    questions.push_back({ "Who wrote 'Romeo and Juliet'?", {"Shakespeare", "Dickens", "Hemingway", "Austen"}, 0 });
    questions.push_back({ "What is the speed of light?", {"3 x 10^8 m/s", "3 x 10^6 m/s", "3 x 10^10 m/s", "300 m/s"}, 0 });
    questions.push_back({ "Which is the longest river in the world?", {"Amazon", "Nile", "Yangtze", "Mississippi"}, 1 });
    questions.push_back({ "What is the square root of 64?", {"6", "8", "10", "12"}, 1 });
    questions.push_back({ "What is the capital of Japan?", {"Seoul", "Beijing", "Tokyo", "Osaka"}, 2 });
    questions.push_back({ "Which element has the chemical symbol 'O'?", {"Oxygen", "Osmium", "Ozone", "Oganesson"}, 0 });
    questions.push_back({ "Who painted the Mona Lisa?", {"Picasso", "Da Vinci", "Van Gogh", "Rembrandt"}, 1 });
    questions.push_back({ "What is the largest ocean on Earth?", {"Atlantic", "Indian", "Arctic", "Pacific"}, 3 });

    totalQuestions = questions.size();
    CCLOG("Total questions: %d", totalQuestions);                   // 日志输出总题数
     
    shuffleQuestions();                                             //打乱出题顺序    
    CCLOG("Questions shuffled.");                                   // 输出题目已打乱

	createExitButton();                                             // 创建退出按钮
	displayQuestion();											    // 显示问题*/
    return true;
}

void QuizGame::createExitButton()
{
    auto exitButton = cocos2d::ui::Button::create("CloseNormal.png", "CloseSelected.png");
    if (!exitButton)
    {
        CCLOGERROR("Failed to create exit button.");
        return;
    }

    // 设置按钮位置（屏幕右上角）
	auto visibleSize = Director::getInstance()->getVisibleSize();               // 获取屏幕尺寸
	auto origin = Director::getInstance()->getVisibleOrigin();				    // 获取屏幕原点
	exitButton->setPosition(cocos2d::Vec2(600, 400));						    // 设置按钮位置

    // 设置按钮点击事件
    exitButton->addClickEventListener([](Ref* sender) {
        CCLOG("Exit button clicked. Exiting game.");
        auto newScene = MiniMap::createWithMap("smallmap/whole3.tmx", false);
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, newScene));  // 退出游戏
        });
     
	this->addChild(exitButton, 10);                                             // 添加按钮到场景
}

void QuizGame::shuffleQuestions()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(questions.begin(), questions.end(), g);

    CCLOG("Questions shuffled randomly.");                                      // 输出已打乱题目的日志
}

void QuizGame::shuffleOptions(int questionIndex)
{
    auto& currentQ = questions[questionIndex];
     
    std::string correctOption = currentQ.options[currentQ.correctAnswerIndex]; // 保存当前正确答案内容

    // 打乱选项
	std::random_device rd;                                                      // 随机设备
	std::mt19937 g(rd());                                                       // 随机数引擎
	std::shuffle(currentQ.options.begin(), currentQ.options.end(), g);          // 打乱选项

    // 更新正确答案索引
    auto it = std::find(currentQ.options.begin(), currentQ.options.end(), correctOption);
    currentQ.correctAnswerIndex = std::distance(currentQ.options.begin(), it);

    CCLOG("Options for question %d shuffled. New correct answer index: %d", questionIndex, currentQ.correctAnswerIndex);
}


bool QuizGame::displayQuestion()
{
    if (currentQuestion >= questions.size())
    {
        ::MessageBoxA(NULL, "You've completed all questions!", "Quiz", MB_OK);  // 如果没有更多问题，游戏结束
        CCLOG("Game completed. All questions answered.");                       // 输出游戏已完成
        return true;
    }
     
	auto& currentQ = questions[currentQuestion];                                              // 获取当前问题                               
    CCLOG("Displaying question %d: %s", currentQuestion + 1, currentQ.questionText.c_str());  // 输出当前显示的问题

    // 显示问题
    auto questionLabel = cocos2d::Label::createWithSystemFont(currentQ.questionText, "fonts/arial.ttf", 24);
    questionLabel->setTextColor(cocos2d::Color4B::WHITE);
    questionLabel->setPosition(cocos2d::Vec2(1800, 800));
    this->addChild(questionLabel, 1);
    this->setLocalZOrder(101);

    // 打乱选项
    shuffleOptions(currentQuestion);

    // 显示答案选项
    for (int i = 0; i < currentQ.options.size(); ++i)
    {
        auto button = cocos2d::MenuItemLabel::create(cocos2d::Label::createWithSystemFont(currentQ.options[i], "Arial", 24),
            [this, i](Ref* sender) {
                onAnswerSelected(i);
            });
        button->setPosition(cocos2d::Vec2(1800, 700 - i * 50));
        auto menu = cocos2d::Menu::create(button, nullptr);
        menu->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(menu);
        CCLOG("Option %d: %s", i + 1, currentQ.options[i].c_str());  // 输出每个选项
    }

    return false;
}

void QuizGame::onAnswerSelected(int answerIndex)
{
    auto& currentQ = questions[currentQuestion];

    CCLOG("Answer selected for question %d: Option %d", currentQuestion + 1, answerIndex + 1);  // 输出选择的答案选项

    // 检查玩家答案
    if (answerIndex == currentQ.correctAnswerIndex)
    {
        ::MessageBoxA(NULL, "Correct!", "Quiz", MB_OK);
        CCLOG("Answer is correct!");                                                    // 输出答案正确的日志

        correctAnswersCount++;  // 答对题目数量增加

        // 检查是否答对了 3 道题
        if (correctAnswersCount >= 3)
        {
            ::MessageBoxA(NULL, "Congratulations! You've answered 3 questions correctly!", "Quiz", MB_OK);
            CCLOG("Player answered 3 questions correctly. Game success.");  // 输出游戏成功的日志
            return;
        }
    }
    else
    {
        ::MessageBoxA(NULL, "Wrong answer! Starting over.", "Quiz", MB_OK);
        CCLOG("Answer is wrong. Restarting the quiz.");                                 // 输出答案错误并重启的日志
        currentQuestion = 0;                                                            // 如果答错，重新开始
        shuffleQuestions();                                                             // 重新打乱问题顺序
        this->removeAllChildren();                                                      // 移除当前所有子节点
		createExitButton();                                                             // 创建退出按钮
        displayQuestion();                                                              // 重新显示问题
        return;
    }

    // 切换到下一个问题
    ++currentQuestion;
    CCLOG("Moving to next question %d", currentQuestion + 1);                           // 输出当前移动到下一个问题

                                                                                        // 如果所有问题都已回答，返回 true
    if (currentQuestion >= questions.size())
    {
        ::MessageBoxA(NULL, "You've completed all questions!", "Quiz", MB_OK);
        CCLOG("All questions answered, game completed.");                               // 输出游戏完成日志
        return;
    }
    this->removeAllChildren();                                                          // 移除当前所有子节点
	createExitButton(); 															    // 创建退出按钮                          
    displayQuestion();                                                                  // 显示下一个问题
}
