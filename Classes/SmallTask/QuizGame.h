#pragma once
#ifndef _QUIZ_GAME_
#define _QUIZ_GAME_

#include "cocos2d.h"
#include <vector>
USING_NS_CC;

class QuizGame :public cocos2d::Scene
{
public:
	QuizGame() :currentQuestion(0) {}

	static QuizGame* create();

	bool init() override;
	void createExitButton();
	bool displayQuestion();
	void onAnswerSelected(int answerIndex);

	// 题库：每个问题由问题内容和选项组成
	struct Question
	{
		std::string questionText;             // 问题文本
		std::vector<std::string> options;     // 选项
		int correctAnswerIndex;               // 正确答案的索引
	};

	std::vector<Question> questions;          // 题库
	int currentQuestion;                      // 当前问题索引
	int totalQuestions;                       // 总问题数
	int correctAnswersCount;

private:
	void shuffleQuestions();                  // 打乱问题顺序
	void shuffleOptions(int questionIndex);   // 打乱答案顺序
};

#endif _QUIZ_GAME_