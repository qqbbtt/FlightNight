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
	cocos2d::Layer*		layerScene;		// ��ũ�� ���̾�
	float				fSpeed;			// ������ �������� �ӵ�
	Vector<Sprite*>		Items;			// ������ ��������Ʈ ����
	bool				isItem;			// �������� ���� �� true.

public:
//	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
//	CREATE_FUNC(GamePlayer);


	void initItem(cocos2d::Layer* lay);		// ����ȭ�� ���̾�� ������ ������ �ʱ�ȭ
	void setItem(float delta);				// �����̴� ������ ����	
	void resetItem(Ref *sender);			// �������� ȭ�� ������ �̵��ϸ� ��������Ʈ ����
	void resetisItem(float delta);			// ������ �����
	void updateItem();
	bool getisItem();

};


#endif // __GAME_ITEM_H__
