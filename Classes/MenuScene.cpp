#include "MenuScene.h"
#include "FlightNightDataBase.h"

USING_NS_CC;


Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	// 메뉴 배경화면 초기화
	initBackGround();

	// 메뉴 초기화
	initMenu();

	// DB 생성
	FNDB.createDatabase();

//	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("game/bgm.mp3");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("menu/Darker_Thoughts.mp3", true);

    return true;
}



void MenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif 

}

/*------------------------------------------------------------------------------------
| 함 수 명  : initBackGround(void)
| 매개변수  :
| 리 턴 값  :
| 설    명  : 메뉴 배경화면 초기화
|------------------------------------------------------------------------------------*/
void MenuScene::initBackGround()
{
	auto spr = Sprite::create("menu/menu.jpg");
	spr->setAnchorPoint(Point::ZERO);
	spr->setPosition(Point::ZERO);
	spr->setScaleX(Director::getInstance()->getWinSize().width / 640);
	spr->setScaleY(Director::getInstance()->getWinSize().height / 400);
//	spr->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(spr);

}


/*------------------------------------------------------------------------------------
| 함 수 명  : initMenu(void)
| 매개변수  :
| 리 턴 값  :
| 설    명  : 메뉴 초기화
|------------------------------------------------------------------------------------*/
void MenuScene::initMenu()
{
	// 메뉴 아이템 셋팅 
	auto menu_0 = MenuItemImage::create("menu/play-0.png", "menu/play-1.png", CC_CALLBACK_1(MenuScene::menuCallback, this));
	auto menu_1 = MenuItemImage::create("menu/help-0.png", "menu/help-1.png", CC_CALLBACK_1(MenuScene::menuCallback, this));
	auto menu_2 = MenuItemImage::create("menu/option-0.png", "menu/option-1.png", CC_CALLBACK_1(MenuScene::menuCallback, this));
	auto menu_3 = MenuItemImage::create("menu/quit-0.png", "menu/quit-1.png", CC_CALLBACK_1(MenuScene::menuCallback, this));

	// 메뉴에 지정한 ID 입력
	menu_0->setTag(ID_MENU::PLAY);
	menu_1->setTag(ID_MENU::HELP);
	menu_2->setTag(ID_MENU::OPTION);
	menu_3->setTag(ID_MENU::QUIT);

	// 메뉴 생성
	auto menu = Menu::create(menu_0, menu_1, menu_2, menu_3, NULL);

	// 화면 가운데에 20픽셀 간격으로 배치
	menu->alignItemsVerticallyWithPadding(20);

	// 화면에 뿌리기
	this->addChild(menu);
}


/*------------------------------------------------------------------------------------
| 함 수 명  : menuCallback(Ref *sender)
| 매개변수  : sender = 메뉴 터치 시 넘어오는 값.
| 리 턴 값  :
| 설    명  : 메뉴 터치 시 화면 전환.
|------------------------------------------------------------------------------------*/
void MenuScene::menuCallback(Ref *sender)
{
	auto menu = (MenuItem*)sender;

	switch (menu->getTag())
	{
		// 게임 플레이
		case ID_MENU::PLAY:
		{
			SimpleAudioEngine::getInstance()->playEffect("menu/button.mp3");
			auto scene = TransitionFadeTR::create(1.0, GameScene::createScene());
			Director::getInstance()->replaceScene(scene);
			break;
		}

		// 도움말
		case ID_MENU::HELP:
		{
			SimpleAudioEngine::getInstance()->playEffect("menu/button.mp3");
			auto scene = TransitionFadeTR::create(1.0, HelpScene::createScene());
			Director::getInstance()->replaceScene(scene);
			break;
		}
			

		// 옵션
		case ID_MENU::OPTION:
		{
			SimpleAudioEngine::getInstance()->playEffect("menu/button.mp3");
			break;
		}

		// 종료
		case ID_MENU::QUIT:
		{
			SimpleAudioEngine::getInstance()->playEffect("menu/button.mp3");
			Director::getInstance()->end();

			#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
							  exit(0);
			#endif 

			break;
		}

		default:
			break;
	}
}