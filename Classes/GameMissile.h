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
	cocos2d::Layer*		layerScene;
	float				fSpeed;
	Vector<Sprite*>		Missiles;

public:
//	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
//	CREATE_FUNC(GamePlayer);


	void initMissile(cocos2d::Layer* lay);				// 게임화면 레이어값과 플레이어 테그 값 셋팅
	void setMissile(float delta, bool item);			// 움직이는 미사일 셋팅
	void resetMissile(Ref *sender);						// 미사일이 화면 밖으로 이동하면 스프라이트 해제
	void updateMissile(bool item);

};


#endif // __GAME_MISSILE_H__
