#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "MenuScene.h"

USING_NS_CC;


/*------------------------------------------------------------------------------------
| CLASS 명  : GameOverScene
| 설    명  : 게임오버 화면
|------------------------------------------------------------------------------------*/
class GameOverScene : public cocos2d::Layer
{
private:
	cocos2d::EventListenerTouchOneByOne* listener;		// 터치 이벤트
	bool isTouch;										// 터치 확인

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(GameOverScene);



	void menuCallback	(Ref *sender);								// 종료 선택시 호출
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);	// 터치 시작
	virtual void onTouchEnded(Touch *touch, Event *unused_event);	// 터치에서 손을 때면 화면 전환
};

#endif // __GAMEOVER_SCENE_H__
