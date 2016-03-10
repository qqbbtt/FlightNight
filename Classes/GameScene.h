#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GamePlayer.h"
#include "GameMissile.h"
#include "GameItem.h"
#include "GameEnemy.h"
#include "TagList.h"


USING_NS_CC;

/*------------------------------------------------------------------------------------
| CLASS ��  : GameScene
| ��    ��  : ���� ȭ��
|------------------------------------------------------------------------------------*/
class GameScene : public cocos2d::Layer
{
private:
	GamePlayer			Player;			// �÷��̾� �����	
	GameMissile			Missile;		// �̻���
	GameItem			Item;			// ������
	GameEnemy			Enemy;			// �� �����


public:
	static cocos2d::Scene* createScene();

	virtual bool init();				// ���ӿ� ������ ��� ���� �ʱ�ȭ

	// a selector callback
	void menuCloseCallback	(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);


	void initBackGround		();					// ���� ���ȭ�� �ʱ�ȭ
	void scheduleMissile(float delta);			// �̻��� ������
	void scheduleItem(float delta);				// ������ ������
	void scheduleEnemy(float delta);				// �� ����� ������
	void update(float delta);					// ������Ʈ
	void resetisItem(float delta);

};

#endif // __GAME_SCENE_H__
