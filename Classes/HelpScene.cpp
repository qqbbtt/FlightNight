#include "HelpScene.h"

USING_NS_CC;


Scene* HelpScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = HelpScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelpScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	// 화면 사이즈
	SizeW = Director::getInstance()->getWinSize().width;
	SizeH = Director::getInstance()->getWinSize().height;

	// 메뉴 배경화면 초기화
	initBackGround();

	// 메뉴 초기화
	initMenu();

//	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("game/bgm.mp3");
//	SimpleAudioEngine::getInstance()->playBackgroundMusic("menu/Darker_Thoughts.mp3", true);

    return true;
}



void HelpScene::menuCloseCallback(Ref* pSender)
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
| 설    명  : 배경화면 초기화
|------------------------------------------------------------------------------------*/
void HelpScene::initBackGround()
{
	auto spr = Sprite::create("menu/menu.jpg");
	spr->setAnchorPoint(Point::ZERO);
	spr->setPosition(Point::ZERO);
	spr->setScaleX(SizeW / 640);
	spr->setScaleY(SizeH / 400);
//	spr->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(spr);

	auto label = Label::createWithTTF("게임 방법", "fonts/hans punch.ttf", 60);
	label->setPosition(Point(SizeW / 2, (SizeH / 4) * 3.2f));
	this->addChild(label);
}


/*------------------------------------------------------------------------------------
| 함 수 명  : initMenu(void)
| 매개변수  :
| 리 턴 값  :
| 설    명  : 메뉴 초기화
|------------------------------------------------------------------------------------*/
void HelpScene::initMenu()
{
	// 메뉴 아이템 셋팅
	auto menu_Next = MenuItemImage::create("menu/Next_0.png", "menu/Next_1.png", CC_CALLBACK_1(HelpScene::menuCallback, this));
	menu_Next->setTag(TAG_HELP_NEXT);
	menu_Next->setScale(0.1f);
	
	auto menu1 = Menu::create(menu_Next, NULL);
	menu1->setAnchorPoint(Point(1, 0));
	menu1->setPosition(Point(SizeW - 50, 50));
	this->addChild(menu1);

	auto menu_Back = MenuItemImage::create("menu/Back_0.png", "menu/Back_1.png", CC_CALLBACK_1(HelpScene::menuCallback, this));
	menu_Back->setTag(TAG_HELP_BACK);
	menu_Back->setScale(0.1f);

	auto menu2 = Menu::create(menu_Back, NULL);
	menu2->setAnchorPoint(Point(1, 0));
	menu2->setPosition(Point(50, 50));
	this->addChild(menu2);

}


/*------------------------------------------------------------------------------------
| 함 수 명  : menuCallback(Ref *sender)
| 매개변수  : sender = 메뉴 터치 시 넘어오는 값.
| 리 턴 값  :
| 설    명  : 메뉴 터치 시 화면 전환.
|------------------------------------------------------------------------------------*/
void HelpScene::menuCallback(Ref *sender)
{
	auto menu = (MenuItem*)sender;

	switch (menu->getTag())
	{
		// Next
		case TAG_HELP_NEXT:
		{
			SimpleAudioEngine::getInstance()->playEffect("menu/button.mp3");
		
			break;
		}

		// Back
		case TAG_HELP_BACK:
		{
			SimpleAudioEngine::getInstance()->playEffect("menu/button.mp3");
			auto scene = TransitionFadeTR::create(1.0, MenuScene::createScene());
			Director::getInstance()->replaceScene(scene);
			break;
		}

		default:
			break;
			
	}

		
	
}