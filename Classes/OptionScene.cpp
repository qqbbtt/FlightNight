#include "OptionScene.h"

USING_NS_CC;


Scene* OptionScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = OptionScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool OptionScene::init()
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

	iMusic = SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();

	// 메뉴 배경화면 초기화
	initBackGround();

	// 메뉴 초기화
	initMenu();

	// 라벨 초기화
	initLabel();


	menuView();

    return true;
}



void OptionScene::menuCloseCallback(Ref* pSender)
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
void OptionScene::initBackGround()
{
	auto spr = Sprite::create("menu/menu.jpg");
	spr->setAnchorPoint(Point::ZERO);
	spr->setPosition(Point::ZERO);
	spr->setScaleX(SizeW / 640);
	spr->setScaleY(SizeH / 400);
	this->addChild(spr);

	auto label = Label::createWithTTF("게임 옵션", "fonts/hans punch.ttf", 60);
	label->setPosition(Point(SizeW / 2, (SizeH / 4) * 3.2f));
	this->addChild(label);


}


/*------------------------------------------------------------------------------------
| 함 수 명  : initMenu(void)
| 매개변수  :
| 리 턴 값  :
| 설    명  : 메뉴 초기화
|------------------------------------------------------------------------------------*/
void OptionScene::initMenu()
{
	// 데이터 정렬 메뉴
	auto label_Music = Label::createWithTTF("배경음악", "fonts/hans punch.ttf", 30);
//	label_Time->enableShadow(Color4B::YELLOW, Size(2, -2));
	label_Music->enableOutline(Color4B::GRAY, 1);
	label_Music->setColor(Color3B(255, 255, 0));
	auto menu_Music = MenuItemLabel::create(label_Music, CC_CALLBACK_1(OptionScene::menuCallback, this));
	menu_Music->setTag(TAG_OPTION_MENU_MUSIC);

	auto label_Effect = Label::createWithTTF("효과음", "fonts/hans punch.ttf", 30);
	label_Effect->enableOutline(Color4B::GRAY, 1);
	label_Effect->setColor(Color3B(255, 255, 0));
	auto menu_Effect = MenuItemLabel::create(label_Effect, CC_CALLBACK_1(OptionScene::menuCallback, this));
	menu_Effect->setTag(TAG_OPTION_MENU_EFFECT);

	auto label_Delete = Label::createWithTTF("순위 데이터 삭제", "fonts/hans punch.ttf", 30);
	label_Delete->enableOutline(Color4B::GRAY, 1);
	label_Delete->setColor(Color3B(255, 255, 0));
	auto menu_Delete = MenuItemLabel::create(label_Delete, CC_CALLBACK_1(OptionScene::menuCallback, this));
	menu_Delete->setTag(TAG_OPTION_MENU_DELETE);

	auto menu = Menu::create(menu_Music, menu_Effect, menu_Delete, NULL);
	menu->alignItemsVertically();
	menu->setPositionY(SizeH-250);
	this->addChild(menu);

	// 좌우 이동 메뉴 아이템 셋팅
	auto menu_Back = MenuItemImage::create("menu/Back_0.png", "menu/Back_1.png", CC_CALLBACK_1(OptionScene::menuCallback, this));
	menu_Back->setTag(TAG_DATA_MENU_BACK);
	menu_Back->setScale(0.1f);

	auto menu2 = Menu::create(menu_Back, NULL);
	menu2->setAnchorPoint(Point(1, 0));
	menu2->setPosition(Point(50, 50));
	this->addChild(menu2);

}

/*------------------------------------------------------------------------------------
| 함 수 명  : initLabel(void)
| 매개변수  :
| 리 턴 값  :
| 설    명  : 라벨 초기화
|------------------------------------------------------------------------------------*/
void OptionScene::initLabel()
{
	auto labe_Music = Label::createWithTTF("", "fonts/hans punch.ttf", 25);
//	labe_Music->setAnchorPoint(Point(0, 1));
	labe_Music->setPosition(Point(SizeW/2, SizeH - 200));
	labe_Music->enableOutline(Color4B::GRAY, 1);
	labe_Music->setTag(TAG_OPTION_LABEL_MUSIC);
	this->addChild(labe_Music);

	auto label_Effect = Label::createWithTTF("", "fonts/hans punch.ttf", 25);
//	label_Effect->setAnchorPoint(Point(0, 1));
	label_Effect->setPosition(Point(SizeW / 2, SizeH - 280));
	label_Effect->enableOutline(Color4B::GRAY, 1);
	label_Effect->setTag(TAG_OPTION_LABEL_EFFECT);
	this->addChild(label_Effect);
}


/*------------------------------------------------------------------------------------
| 함 수 명  : menuView()
| 매개변수  : 
| 리 턴 값  :
| 설    명  : 메뉴 선택 후 화면 전환
|------------------------------------------------------------------------------------*/
void OptionScene::menuView()
{
	auto label_Music = (Label*)this->getChildByTag(TAG_OPTION_LABEL_MUSIC);

	if (iMusic == true)
	{
		label_Music->setString("켜짐");
	}
	else
	{
		label_Music->setString("꺼짐");
	}

	auto label_Effect = (Label*)this->getChildByTag(TAG_OPTION_LABEL_EFFECT);

	if (iEffect == true)
	{
		label_Effect->setString("켜짐");
	}
	else
	{
		label_Effect->setString("꺼짐");
	}
	
}

/*------------------------------------------------------------------------------------
| 함 수 명  : menuCallback(Ref *sender)
| 매개변수  : sender = 메뉴 터치 시 넘어오는 값.
| 리 턴 값  :
| 설    명  : 메뉴 터치 시 화면 전환.
|------------------------------------------------------------------------------------*/
void OptionScene::menuCallback(Ref *sender)
{
	auto menu = (MenuItem*)sender;

	switch (menu->getTag())
	{
		// Back
		case TAG_DATA_MENU_BACK:
		{
			if (iEffect == true) SimpleAudioEngine::getInstance()->playEffect("menu/button.mp3");

			auto scene = TransitionFadeTR::create(1.0, MenuScene::createScene());
			Director::getInstance()->replaceScene(scene);
			break;
		}

		case TAG_OPTION_MENU_MUSIC:
		{
			iMusic = !iMusic;
			if (iMusic == true)
			{
				SimpleAudioEngine::getInstance()->playBackgroundMusic("menu/Darker_Thoughts.mp3", true);
			}
			else
			{
				SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			}
			menuView();
			break;
		}

		case TAG_OPTION_MENU_EFFECT:
		{
			iEffect = !iEffect;

	/*		if (iEffect == true)
			{
				SimpleAudioEngine::getInstance()->resumeAllEffects();
			}
			else
			{
			//	SimpleAudioEngine::getInstance()->stopAllEffects();
				SimpleAudioEngine::getInstance()->resumeAllEffects();
			}*/
				
			menuView();
			break;
		}

		case TAG_OPTION_MENU_DELETE:
		{
			 FNDB.deleteDatabase();
			 break;
		}

		default:
			break;
			
	}

	
}