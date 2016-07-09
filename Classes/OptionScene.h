#ifndef __OPTION_SCENE_H__
#define __OPTION_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "MenuScene.h"
#include "FlightNightDataBase.h"

#pragma execution_character_set("utf-8")


USING_NS_CC;
using namespace std;


/*------------------------------------------------------------------------------------
| CLASS 명  : OptionScene
| 설    명  : 옵션을 체크하는 화면
|------------------------------------------------------------------------------------*/
class OptionScene : public cocos2d::Layer
{
private:
	float				SizeW;					// 화면 가로
	float				SizeH;					// 화면 세로
	bool				iMusic;					// 배경 음악

	cocos2d::Scene* gamese;


public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(OptionScene);

	void initBackGround();				// 배경화면 초기화
	void initMenu();					// 메뉴 초기화
	void initLabel();

	void menuCallback(Ref *sender);		// 메뉴 선택시 호출
	void menuView();					// 메뉴 선택 후 화면 전환

};

#endif // __OPTION_SCENE_H__
