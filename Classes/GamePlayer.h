#ifndef __GAME_PLAYER_H__
#define __GAME_PLAYER_H__

#include "cocos2d.h"
#include "TagList.h"

USING_NS_CC;

/*------------------------------------------------------------------------------------
| CLASS ��  : GamePlayer
| ��    ��  : �÷��̾��� �����
|------------------------------------------------------------------------------------*/
class GamePlayer : public cocos2d::Layer
{
private:
	cocos2d::Layer*			layerScene;			// ���̾
	Point posStartTouch,	posStartPlayer;		// ����� ��ġ �� �̵���

public:
//	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
//	CREATE_FUNC(GamePlayer);


	void initPlayer(cocos2d::Layer* lay);					// �÷��̾� ����� �ʱ�ȭ
	bool onTouchBegan(Touch *touch, Event *unused_event);	// �÷��̾� ����� ��ġ
	void onTouchMoved(Touch *touch, Event *unused_event);	// �÷��̾� ����� ��ġ �ϸ鼭 �̵�

};

//extern GamePlayer Player;

#endif // __GAME_PLAYER_H__
