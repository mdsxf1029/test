#include "QuizGame.h"
USING_NS_CC;

QuizGame* QuizGame::create()
{
    QuizGame* ret = new QuizGame();
    if (ret && ret->init())
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

    totalQuestions = questions.size();
    CCLOG("Total questions: %d", totalQuestions);  // 日志输出总题数

    // 打乱问题顺序
    shuffleQuestions();
    CCLOG("Questions shuffled.");  // 输出题目已打乱

    displayQuestion();
    return true;
}

void QuizGame::shuffleQuestions()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(questions.begin(), questions.end(), g);

    CCLOG("Questions shuffled randomly.");  // 输出已打乱题目的日志
}

void QuizGame::shuffleOptions(int questionIndex)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(questions[questionIndex].options.begin(), questions[questionIndex].options.end(), g);

    CCLOG("Options for question %d shuffled.", questionIndex);  // 日志输出选项已打乱
}

bool QuizGame::displayQuestion()
{
    if (currentQuestion >= questions.size())
    {
        // 如果没有更多问题，游戏结束
        cocos2d::MessageBox("You've completed all questions!", "Quiz");
        CCLOG("Game completed. All questions answered.");  // 输出游戏已完成
        return true;
    }

    // 获取当前问题
    auto& currentQ = questions[currentQuestion];
    CCLOG("Displaying question %d: %s", currentQuestion + 1, currentQ.questionText.c_str());  // 输出当前显示的问题

    // 显示问题
    auto questionLabel = cocos2d::Label::createWithSystemFont(currentQ.questionText, "Arial", 24);
    questionLabel->setPosition(cocos2d::Vec2(400, 300));
    this->addChild(questionLabel);

    // 打乱选项
    shuffleOptions(currentQuestion);

    // 显示答案选项
    for (int i = 0; i < currentQ.options.size(); ++i)
    {
        auto button = cocos2d::MenuItemLabel::create(cocos2d::Label::createWithSystemFont(currentQ.options[i], "Arial", 24),
            [this, i](Ref* sender) {
                onAnswerSelected(i);
            });
        button->setPosition(cocos2d::Vec2(400, 250 - i * 50));
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
        cocos2d::MessageBox("Correct!", "Quiz");
        CCLOG("Answer is correct!");  // 输出答案正确的日志
    }
    else
    {
        cocos2d::MessageBox("Wrong answer! Starting over.", "Quiz");
        CCLOG("Answer is wrong. Restarting the quiz.");  // 输出答案错误并重启的日志
        currentQuestion = 0;  // 如果答错，重新开始
        shuffleQuestions();   // 重新打乱问题顺序
        this->removeAllChildren();  // 移除当前所有子节点
        displayQuestion();    // 重新显示问题
        return;
    }

    // 切换到下一个问题
    ++currentQuestion;
    CCLOG("Moving to next question %d", currentQuestion + 1);  // 输出当前移动到下一个问题

    // 如果所有问题都已回答，返回 true
    if (currentQuestion >= questions.size())
    {
        cocos2d::MessageBox("You've completed all questions!", "Quiz");
        CCLOG("All questions answered, game completed.");  // 输出游戏完成日志
        return;
    }

    this->removeAllChildren();  // 移除当前所有子节点
    displayQuestion();          // 显示下一个问题
}
