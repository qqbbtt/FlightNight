#ifndef __GAME_ITEM_H__
#define __GAME_ITEM_H__

#include "cocos2d.h"
#include "TagList.h"

USING_NS_CC;

/*------------------------------------------------------------------------------------
| CLASS 명  : GameItem
| 설    명  : 아이템
|------------------------------------------------------------------------------------*/
class GameItem : public cocos2d::Layer
{
private:
	cocos2d::Layer*		layerScene;		// 스크린 레이어
	float				fSpeed;			// 아이템 떨어지는 속도
	Vector<Sprite*>		Items;			// 아이템 스프라이트 벡터
	bool				isItem;			// 아이템을 습득 시 true.

public:
//	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
//	CREATE_FUNC(GamePlayer);


	void initItem(cocos2d::Layer* lay);		// 게임화면 레이어값과 아이템 설정값 초기화
	void setItem(float delta);				// 움직이는 아이템 셋팅	
	void resetItem(Ref *sender);			// 아이템이 화면 밖으로 이동하면 스프라이트 해제
	void resetisItem(float delta);			// 아이템 습득시
	void updateItem();
	bool getisItem();

};


#endif // __GAME_ITEM_H__
