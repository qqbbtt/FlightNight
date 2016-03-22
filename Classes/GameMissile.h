#ifndef __GAME_MISSILE_H__
#define __GAME_MISSILE_H__

#include "cocos2d.h"
#include "TagList.h"

USING_NS_CC;

/*------------------------------------------------------------------------------------
| CLASS 명  : GameMissile
| 설    명  : 미사일
|------------------------------------------------------------------------------------*/
class GameMissile : public cocos2d::Layer
{
private:
	cocos2d::Layer*		layerScene;			// 게임화면 레이어값
	float				fSpeed;				// 미사일 속도
	Vector<Sprite*>		Missiles;			// 미사일 vector

public:
//	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
//	CREATE_FUNC(GamePlayer);


	void initMissile(cocos2d::Layer* lay);					// 게임화면 레이어값과 플레이어 테그 값 셋팅

	void setMissile(float delta, bool item);				// 움직이는 미사일 셋팅 (플레이어 미사일)
	void setMissile(float delta, Vector<Sprite*> enemy);	// 움직이는 미사일 셋팅 (적비행기 미사일)

	void resetMissile(Ref *sender);							// 스프라이트 해제
	void updateMissile(bool item);
	Vector<Sprite*>	getSprMissiles();						// 미사일 vecotr 리턴

};


#endif // __GAME_MISSILE_H__
