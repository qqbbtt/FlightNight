#ifndef __GAME_ENEMY_H__
#define __GAME_ENEMY_H__

#include "cocos2d.h"
#include "TagList.h"

USING_NS_CC;

/*------------------------------------------------------------------------------------
| CLASS 명  : GameEnemy
| 설    명  : 적 비행기
|------------------------------------------------------------------------------------*/
class GameEnemy : public cocos2d::Layer
{
private:
	cocos2d::Layer*		layerScene;			// 스크린 레이어
	int					padding;			// 비행기 위치에 관련
	float				fSpeed;				// 비행기 떨어지는 속도
	Vector<Sprite*>		Enemies;			// 비행기 스프라이트 벡터

public:
//	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
//	CREATE_FUNC(GameEnemy);


	void initEnemy(cocos2d::Layer* lay);		// 게임화면 레이어값과 아이템 설정값 초기화
	void setEnemy(float delta);				// 움직이는 아이템 셋팅	
	void resetEnemy(Ref *sender);			// 아이템이 화면 밖으로 이동하면 스프라이트 해제


//	void resetisItem(float delta);			// 아이템 습득시
//	void updateItem();
//	bool getisItem();

};


#endif // __GAME_ENEMY_H__
