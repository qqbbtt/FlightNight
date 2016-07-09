#include "DataScene.h"

USING_NS_CC;


Scene* DataScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = DataScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool DataScene::init()
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

	// 라벨 초기화
	initLabel();

	// 초기 화면 정렬
	FNDB.orderDate();
	menuView();

    return true;
}



void DataScene::menuCloseCallback(Ref* pSender)
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
void DataScene::initBackGround()
{
	auto spr = Sprite::create("menu/menu.jpg");
	spr->setAnchorPoint(Point::ZERO);
	spr->setPosition(Point::ZERO);
	spr->setScaleX(SizeW / 640);
	spr->setScaleY(SizeH / 400);
	this->addChild(spr);

	auto label = Label::createWithTTF("게임 순위", "fonts/hans punch.ttf", 60);
	label->setPosition(Point(SizeW / 2, (SizeH / 4) * 3.2f));
	this->addChild(label);


}


/*------------------------------------------------------------------------------------
| 함 수 명  : initMenu(void)
| 매개변수  :
| 리 턴 값  :
| 설    명  : 메뉴 초기화
|------------------------------------------------------------------------------------*/
void DataScene::initMenu()
{
	// 데이터 정렬 메뉴
	auto label_Time = Label::createWithTTF("    날 짜    ", "fonts/hans punch.ttf", 25);
//	label_Time->enableShadow(Color4B::YELLOW, Size(2, -2));
	label_Time->enableOutline(Color4B::GRAY, 1);
	label_Time->setColor(Color3B(255, 255, 0));
	auto menu_Time = MenuItemLabel::create(label_Time, CC_CALLBACK_1(DataScene::menuCallback, this));
	menu_Time->setTag(TAG_DATA_MENU_TIME);

	auto label_Score = Label::createWithTTF("점수  ", "fonts/hans punch.ttf", 23);
	label_Score->enableOutline(Color4B::GRAY, 1);
	label_Score->setColor(Color3B(255, 255, 0));
	auto menu_Score = MenuItemLabel::create(label_Score, CC_CALLBACK_1(DataScene::menuCallback, this));
	menu_Score->setTag(TAG_DATA_MENU_SCORE);

	auto label_Buf = Label::createWithTTF("BUF ", "fonts/hans punch.ttf", 20);
	label_Buf->enableOutline(Color4B::GRAY, 1);
	label_Buf->setColor(Color3B(255, 255, 0));
	auto menu_Buf = MenuItemLabel::create(label_Buf, CC_CALLBACK_1(DataScene::menuCallback, this));
	menu_Buf->setTag(TAG_DATA_MENU_BUF);

	auto label_Debuf = Label::createWithTTF("DE ", "fonts/hans punch.ttf", 20);
	label_Debuf->enableOutline(Color4B::GRAY, 1);
	label_Debuf->setColor(Color3B(255, 255, 0));
	auto menu_Debuf = MenuItemLabel::create(label_Debuf, CC_CALLBACK_1(DataScene::menuCallback, this));
	menu_Debuf->setTag(TAG_DATA_MENU_DEBUF);

	auto menu = Menu::create(menu_Time, menu_Score, menu_Buf, menu_Debuf, NULL);
	menu->alignItemsHorizontally();
	menu->setPositionY(SizeH-140);
	this->addChild(menu);

	// 좌우 이동 메뉴 아이템 셋팅
	auto menu_Next = MenuItemImage::create("menu/Next_0.png", "menu/Next_1.png", CC_CALLBACK_1(DataScene::menuCallback, this));
	menu_Next->setTag(TAG_DATA_MENU_NEXT);
	menu_Next->setScale(0.1f);
	
	auto menu1 = Menu::create(menu_Next, NULL);
	menu1->setAnchorPoint(Point(1, 0));
	menu1->setPosition(Point(SizeW - 50, 50));
	this->addChild(menu1);


	auto menu_Back = MenuItemImage::create("menu/Back_0.png", "menu/Back_1.png", CC_CALLBACK_1(DataScene::menuCallback, this));
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
void DataScene::initLabel()
{
	auto labelDate = Label::createWithTTF("", "fonts/hans punch.ttf", 18, Size(180, 200), TextHAlignment::CENTER);
	labelDate->setAnchorPoint(Point(0, 1));
	labelDate->setPosition(Point(10, SizeH - 160));
	labelDate->setTag(TAG_DATA_LABEL_TIME);
	this->addChild(labelDate);

	auto labelScore = Label::createWithTTF("", "fonts/hans punch.ttf", 18);
	labelScore->setAnchorPoint(Point(0, 1));
	labelScore->setPosition(Point(200, SizeH - 160));
	labelScore->setTag(TAG_DATA_LABEL_SCORE);
	this->addChild(labelScore);

	auto labelBuf = Label::createWithTTF("", "fonts/hans punch.ttf", 18);
	labelBuf->setAnchorPoint(Point(0, 1));
	labelBuf->setPosition(Point(260, SizeH - 160));
	labelBuf->setTag(TAG_DATA_LABEL_BUF);
	this->addChild(labelBuf);

	auto labelDebuf = Label::createWithTTF("", "fonts/hans punch.ttf", 18);
	labelDebuf->setAnchorPoint(Point(0, 1));
	labelDebuf->setPosition(Point(300, SizeH - 160));
	labelDebuf->setTag(TAG_DATA_LABEL_DEBUF);
	this->addChild(labelDebuf);
}


/*------------------------------------------------------------------------------------
| 함 수 명  : menuView()
| 매개변수  : 
| 리 턴 값  :
| 설    명  : 데이터 정보 정렬 화면
|------------------------------------------------------------------------------------*/
void DataScene::menuView()
{
	int(*arr)[8] = FNDB.getFNDB();

	auto labelTime = (Label*)this->getChildByTag(TAG_DATA_LABEL_TIME);
	labelTime->setString(StringUtils::format("%d년%d월%d일 %d시%d분, \n%d년%d월%d일 %d시%d분 \n%d년%d월%d일 %d시%d분 \n%d년%d월%d일 %d시%d분 \n%d년%d월%d일 %d시%d분"
		, arr[0][0], arr[0][1], arr[0][2], arr[0][3], arr[0][4], arr[1][0], arr[1][1], arr[1][2], arr[1][3], arr[1][4], arr[2][0], arr[2][1], arr[2][2], arr[2][3], arr[2][4], arr[3][0], arr[3][1], arr[3][2], arr[3][3], arr[3][4], arr[4][0], arr[4][1], arr[4][2], arr[4][3], arr[4][4]));

	auto labelScore = (Label*)this->getChildByTag(TAG_DATA_LABEL_SCORE);
	labelScore->setString(StringUtils::format("%d\n%d\n%d\n%d\n%d"
		, arr[0][5], arr[1][5], arr[2][5], arr[3][5], arr[4][5]));

	auto labelBuf = (Label*)this->getChildByTag(TAG_DATA_LABEL_BUF);
	labelBuf->setString(StringUtils::format("%d\n%d\n%d\n%d\n%d"
		, arr[0][6], arr[1][6], arr[2][6], arr[3][6], arr[4][6]));

	auto labelDebuf = (Label*)this->getChildByTag(TAG_DATA_LABEL_DEBUF);
	labelDebuf->setString(StringUtils::format("%d\n%d\n%d\n%d\n%d"
		, arr[0][7], arr[1][7], arr[2][7], arr[3][7], arr[4][7]));
}

/*------------------------------------------------------------------------------------
| 함 수 명  : menuCallback(Ref *sender)
| 매개변수  : sender = 메뉴 터치 시 넘어오는 값.
| 리 턴 값  :
| 설    명  : 메뉴 터치 시 화면 전환.
|------------------------------------------------------------------------------------*/
void DataScene::menuCallback(Ref *sender)
{
	auto menu = (MenuItem*)sender;

	switch (menu->getTag())
	{
		// Next
		case TAG_DATA_MENU_NEXT:
		{
			SimpleAudioEngine::getInstance()->playEffect("menu/button.mp3");
			auto scene = TransitionFadeTR::create(1.0, MenuScene::createScene());
			Director::getInstance()->replaceScene(scene);
		
			break;
		}

		// Back
		case TAG_DATA_MENU_BACK:
		{
			SimpleAudioEngine::getInstance()->playEffect("menu/button.mp3");
			auto scene = TransitionFadeTR::create(1.0, HelpScene::createScene());
			Director::getInstance()->replaceScene(scene);
			break;
		}

		case TAG_DATA_MENU_TIME:
		{
			FNDB.orderDate();
			menuView();
			break;
		}

		case TAG_DATA_MENU_SCORE:
		{
			FNDB.orderScore();
			menuView();
			break;
		}

		case TAG_DATA_MENU_BUF:
		{
			 FNDB.orderBuf();
			 menuView();
			 break;
		}

		case TAG_DATA_MENU_DEBUF:
		{
			FNDB.orderDebuf();
			menuView();
			break;
		}

		default:
			break;
			
	}

	
}