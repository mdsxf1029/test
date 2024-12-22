#pragma once
#include "AudioEngine.h"
#include "Sets/manager.h"

using namespace cocos2d::experimental;

class AudioManager {
public:
	static AudioManager& getInstance()                               //获取实例 音频
    {
		static AudioManager instance;                               //静态局部变量
		return instance;                                            //返回实例
    }

    void playIntroMusic()                                           //播放音乐
    {
		if (!hasPlayedIntroMusic)								    //如果没有播放音乐
        {
			AudioEngine::play2d("intro.mp3", false, 1.0f);		    //播放音乐
			hasPlayedIntroMusic = true;							    //设置为播放音乐
        }
    }

	void resetIntroMusicFlag()									    //重置音乐标志
    {
		hasPlayedIntroMusic = false;								 //设置为没有播放音乐
    }

private:
	AudioManager() : hasPlayedIntroMusic(false) {} 			   //构造函数
    bool hasPlayedIntroMusic;
};

