#ifndef __GAME_MISSILE_H__
#define __GAME_MISSILE_H__

#include "cocos2d.h"
#include "TagList.h"

USING_NS_CC;

/*------------------------------------------------------------------------------------
| CLASS ��  : GameMissile
| ��    ��  : �̻���
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


	void initMissile(cocos2d::Layer* lay);				// ����ȭ�� ���̾�� �÷��̾� �ױ� �� ����
	void setMissile(float delta, bool item);			// �����̴� �̻��� ����
	void resetMissile(Ref *sender);						// �̻����� ȭ�� ������ �̵��ϸ� ��������Ʈ ����
	void updateMissile(bool item);

};


#endif // __GAME_MISSILE_H__
