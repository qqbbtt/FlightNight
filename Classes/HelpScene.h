#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include "cocos2d.h"
#include "MenuScene.h"
#include "DataScene.h"

#pragma execution_character_set("utf-8")


USING_NS_CC;
using namespace std;


/*------------------------------------------------------------------------------------
| CLASS 명  : HelpScene
| 설    명  : 도움말 화면
|------------------------------------------------------------------------------------*/
class HelpScene : public cocos2d::Layer
{
private:
	float				SizeW;					// 화면 가로
	float				SizeH;					// 화면 세로

	cocos2d::Scene* gamese;


public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(HelpScene);

	void initBackGround();				// 배경화면 초기화
	void initMenu();					// 메뉴 초기화

	void menuCallback(Ref *sender);		// 메뉴 선택시 호출

};

#endif // __HELP_SCENE_H__
