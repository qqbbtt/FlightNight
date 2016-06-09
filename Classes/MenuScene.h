#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

//#pragma comment(lib, "sqlite3.lib")
#include "cocos2d.h"

#include "GameScene.h"


USING_NS_CC;
using namespace std;


// �޴� ID
namespace ID_MENU
{
	enum {
		PLAY = 0,
		HELP,
		OPTION,
		QUIT
	};
}

/*------------------------------------------------------------------------------------
| CLASS ��  : MenuScene
| ��    ��  : �޴� ȭ��
|------------------------------------------------------------------------------------*/
class MenuScene : public cocos2d::Layer
{
private:
	cocos2d::Scene* gamese;


public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);

	void initBackGround();				// �޴� ���ȭ�� �ʱ�ȭ
	void initMenu();					// �޴� �ʱ�ȭ

	void menuCallback(Ref *sender);		// �޴� ���ý� ȣ��

};

#endif // __MENU_SCENE_H__
