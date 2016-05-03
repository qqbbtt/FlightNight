#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "MenuScene.h"

USING_NS_CC;


/*------------------------------------------------------------------------------------
| CLASS ��  : GameOverScene
| ��    ��  : ���ӿ��� ȭ��
|------------------------------------------------------------------------------------*/
class GameOverScene : public cocos2d::Layer
{
private:
	cocos2d::EventListenerTouchOneByOne* listener;		// ��ġ �̺�Ʈ
	bool isTouch;										// ��ġ Ȯ��

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(GameOverScene);



	void menuCallback	(Ref *sender);								// ���� ���ý� ȣ��
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);	// ��ġ ����
	virtual void onTouchEnded(Touch *touch, Event *unused_event);	// ��ġ���� ���� ���� ȭ�� ��ȯ
};

#endif // __GAMEOVER_SCENE_H__
