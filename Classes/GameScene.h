#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "sqlite3.h"

#include "MenuScene.h"
#include "GamePlayer.h"
#include "GameMissile.h"
#include "GameItem.h"
#include "GameEnemy.h"
#include "GameData.h"
#include "TagList.h"
#include "GameOverScene.h"


USING_NS_CC;
using namespace CocosDenshion;


/*------------------------------------------------------------------------------------
| CLASS 명  : GameScene
| 설    명  : 게임 화면
|------------------------------------------------------------------------------------*/
class GameScene : public cocos2d::Layer
{
private:
	GamePlayer			Player;					// 플레이어 비행기	
	GameMissile			PlayerMissile;			// 플레이어 미사일
	GameMissile			EnemyMissile;			// 적비행기 미사일
	GameItem			Item;					// 아이템
	GameEnemy			Enemy;					// 적비행기
	GameData			gmData;
	cocos2d::Layer*		layerScene;				// 게임화면 레이어값
	float				SizeW;					// 화면 가로
	float				SizeH;					// 화면 세로
	float				speedPl;				// 플레이어 미사일 속도
	float				speedEn;				// 적비행기 미사일 속도
	


public:
	static cocos2d::Scene* createScene();


	virtual bool init();				// 게임에 관련한 모든 설정 초기화

	// a selector callback
	void menuCloseCallback	(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);


	void initBackGround();						// 게임 배경화면 초기화
	void initLabel();							// 라벨 초기화
	void scheduleEnMissile(float delta);		// 적비행기 미사일 스케쥴
	void schedulePlMissile(float delta);		// 플레이어 미사일 스케쥴
	void scheduleItem(float delta);				// 아이템 스케쥴
	void scheduleEnemy(float delta);			// 적 비행기 스케쥴
	void update(float delta);					// 업데이트
	void updateLabel();							// 라벨 업데이트
	void resetItem(float delta);				// 아이템 리셋
	void resetEnemy(float delta);
	void changeScene();							// 화면 전환
	void initSound();							// 사운드 초기화
};

#endif // __GAME_SCENE_H__
