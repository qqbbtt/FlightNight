#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

//#pragma comment(lib, "sqlite3.lib")
#include "cocos2d.h"

#include "GameScene.h"


USING_NS_CC;
using namespace std;


// 메뉴 ID
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
| CLASS 명  : MenuScene
| 설    명  : 메뉴 화면
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

	void initBackGround();				// 메뉴 배경화면 초기화
	void initMenu();					// 메뉴 초기화

	void menuCallback(Ref *sender);		// 메뉴 선택시 호출

};

#endif // __MENU_SCENE_H__
