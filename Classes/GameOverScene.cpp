#include "GameOverScene.h"


USING_NS_CC;

Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	// 터치 초기화
	isTouch = false;


	// 게임 오버 글자
	auto label = Label::createWithSystemFont("GAME OVER", "Thonburi", 50);		
	label->setPosition(Point(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height/2));
	this->addChild(label);


	// 이벤트 생성
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameOverScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameOverScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	listener->setEnabled(true);
   
    
    return true;
}


void GameOverScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif 

}

/*------------------------------------------------------------------------------------
| 함 수 명  : onTouchEnded(Touch *touch, Event *unused_event)
| 매개변수  : touch = 터치정보, unused_event = 이벤트 정보
| 리 턴 값  :
| 설    명  : 터치에서 손을 때면 화면 전환
|------------------------------------------------------------------------------------*/
void GameOverScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (isTouch)
	{
		listener->setEnabled(false);
	//	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
		auto scene = TransitionFadeTR::create(1.0, MenuScene::createScene());
		Director::getInstance()->replaceScene(scene);
	}

}

/*------------------------------------------------------------------------------------
| 함 수 명  : onTouchBegan(Touch *touch, Event *unused_event)
| 매개변수  : touch = 터치정보, unused_event = 이벤트 정보
| 리 턴 값  :
| 설    명  : 터치 시작
|------------------------------------------------------------------------------------*/
bool GameOverScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (!isTouch)
	{
		isTouch = true;
	}
		
	return true;
}

