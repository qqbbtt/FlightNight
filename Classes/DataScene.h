#ifndef __DATA_SCENE_H__
#define __DATA_SCENE_H__

#include "cocos2d.h"
#include "MenuScene.h"
#include "HelpScene.h"
#include "FlightNightDataBase.h"

#pragma execution_character_set("utf-8")


USING_NS_CC;
using namespace std;


/*------------------------------------------------------------------------------------
| CLASS ��  : DataScene
| ��    ��  : ������ �����ִ� ȭ��
|------------------------------------------------------------------------------------*/
class DataScene : public cocos2d::Layer
{
private:
	float				SizeW;					// ȭ�� ����
	float				SizeH;					// ȭ�� ����

	cocos2d::Scene* gamese;


public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(DataScene);

	void initBackGround();				// ���ȭ�� �ʱ�ȭ
	void initMenu();					// �޴� �ʱ�ȭ
	void initLabel();

	void menuCallback(Ref *sender);		// �޴� ���ý� ȣ��
	void menuView();					// ������ ���� ���� ȭ��

};

#endif // __DATA_SCENE_H__
