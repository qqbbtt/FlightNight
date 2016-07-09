#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include "cocos2d.h"
#include "MenuScene.h"
#include "DataScene.h"

#pragma execution_character_set("utf-8")


USING_NS_CC;
using namespace std;


/*------------------------------------------------------------------------------------
| CLASS ��  : HelpScene
| ��    ��  : ���� ȭ��
|------------------------------------------------------------------------------------*/
class HelpScene : public cocos2d::Layer
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
	CREATE_FUNC(HelpScene);

	void initBackGround();				// ���ȭ�� �ʱ�ȭ
	void initMenu();					// �޴� �ʱ�ȭ

	void menuCallback(Ref *sender);		// �޴� ���ý� ȣ��

};

#endif // __HELP_SCENE_H__
