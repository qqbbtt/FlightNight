#ifndef __GAME_ENEMY_H__
#define __GAME_ENEMY_H__

#include "cocos2d.h"
#include "TagList.h"

USING_NS_CC;

/*------------------------------------------------------------------------------------
| CLASS ��  : GameEnemy
| ��    ��  : �� �����
|------------------------------------------------------------------------------------*/
class GameEnemy : public cocos2d::Layer
{
private:
	cocos2d::Layer*		layerScene;			// ����ȭ�� ���̾
	float				fSpeed;				// ����� �������� �ӵ�
	Vector<Sprite*>		Enemies;			// ����� ��������Ʈ ����

public:
//	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
//	CREATE_FUNC(GameEnemy);


	void initEnemy(cocos2d::Layer* lay);		// ����ȭ�� ���̾�� ������ ������ �ʱ�ȭ
	void setEnemy(float delta);					// �����̴� ������ ����	
	void resetEnemy(Ref *sender);				// ��������Ʈ ����
	Vector<Sprite*>	getSprEnemies();			// ������� vecotr ����


//	void resetisItem(float delta);			// ������ �����
//	void updateItem();
//	bool getisItem();

};


#endif // __GAME_ENEMY_H__
