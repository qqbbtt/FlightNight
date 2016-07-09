#ifndef __DATA_SCENE_H__
#define __DATA_SCENE_H__

#include "cocos2d.h"
#include "MenuScene.h"
#include "HelpScene.h"
#include "FlightNightDataBase.h"

#pragma execution_character_set("utf-8")


USING_NS_CC;
using namespace std;


/*------------------------------------------------------------------------------------
| CLASS 명  : DataScene
| 설    명  : 순위를 보여주는 화면
|------------------------------------------------------------------------------------*/
class DataScene : public cocos2d::Layer
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
	CREATE_FUNC(DataScene);

	void initBackGround();				// 배경화면 초기화
	void initMenu();					// 메뉴 초기화
	void initLabel();

	void menuCallback(Ref *sender);		// 메뉴 선택시 호출
	void menuView();					// 데이터 정보 정렬 화면

};

#endif // __DATA_SCENE_H__
