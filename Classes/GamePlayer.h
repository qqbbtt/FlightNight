#ifndef __GAME_PLAYER_H__
#define __GAME_PLAYER_H__

#include "cocos2d.h"
#include "TagList.h"

USING_NS_CC;

/*------------------------------------------------------------------------------------
| CLASS 명  : GamePlayer
| 설    명  : 플레이어의 비행기
|------------------------------------------------------------------------------------*/
class GamePlayer : public cocos2d::Layer
{
private:
	cocos2d::EventListenerTouchOneByOne* listener;
	
	cocos2d::Layer*			layerScene;			// 게임화면 레이어값
	Point posStartTouch,	posStartPlayer;		// 비행기 터치 및 이동값

public:
//	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
//	CREATE_FUNC(GamePlayer);


	void initPlayer		(cocos2d::Layer* lay);					// 플레이어 비행기 초기화
	bool onTouchBegan	(Touch *touch, Event *unused_event);	// 플레이어 비행기 터치
	void onTouchMoved	(Touch *touch, Event *unused_event);	// 플레이어 비행기 터치 하면서 이동
	void ChangeScene	();										// 화면 전환 시 모든 이벤트 입력 중단
};


#endif // __GAME_PLAYER_H__
