#ifndef __GAME_ITEM_H__
#define __GAME_ITEM_H__

#include "cocos2d.h"
#include "TagList.h"

USING_NS_CC;

/*------------------------------------------------------------------------------------
| CLASS ��  : GameItem
| ��    ��  : ������
|------------------------------------------------------------------------------------*/
class GameItem : public cocos2d::Layer
{
private:
	cocos2d::Layer*		layerScene;			// ����ȭ�� ���̾
	float				fSpeed;				// ������ �������� �ӵ�
	Vector<Sprite*>		BufItems;			// ���� ������ ��������Ʈ vector
	Vector<Sprite*>		DebufItems;			// ����� ������ ��������Ʈ vector
	int					Type;				// ������ ����

public:
//	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
//	CREATE_FUNC(GamePlayer);


	void initItem (cocos2d::Layer* lay);		// ����ȭ�� ���̾�� ������ �ʱ�ȭ
	void setItem (float delta);					// �����̴� ������ ����	
	void resetItem (Ref *sender);				// ��������Ʈ ����
	void updateBufItem (Ref *sender);			// �浹 �� ���� ������ �ʱ�ȭ 
	void updateDebufItem (Ref *sender);			// �浹 �� ����� ������ �ʱ�ȭ 
	int getType ();								// ������ ���� ����
	void setType (int ty);						// ������ ���� ����

	Vector<Sprite*>	getBufSprItems();					// ���� ������ vecotr ����
	Vector<Sprite*>	getDebufSprItems();					// ����� ������ vecotr ����

};


#endif // __GAME_ITEM_H__
