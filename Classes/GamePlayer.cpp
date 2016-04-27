#include "GamePlayer.h"

USING_NS_CC;

/*Scene* GamePlayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GamePlayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}*/


// on "init" you need to initialize your instance
bool GamePlayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	return true;
}


void GamePlayer::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif 

}

/*------------------------------------------------------------------------------------
| 함 수 명  : initPlayer(cocos2d::Layer* lay)
| 매개변수  : lay = 게임화면 레이어값
| 리 턴 값  :
| 설    명  : 플레이어 비행기 초기화
|------------------------------------------------------------------------------------*/
void GamePlayer::initPlayer(cocos2d::Layer* lay)
{
	// 레이어값 저장
	layerScene = lay;

	// 플레이어 비행기 생성
	auto spr = Sprite::create();
	spr->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	spr->setTag(TAG_SPRITE_PLAYER);
	layerScene->addChild(spr, 1);

	auto texture = Director::getInstance()->getTextureCache()->addImage("game/Spaceship.png");

	// 애니메이션 생성
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	for (int i = 0; i<4; i++) {
		animation->addSpriteFrameWithTexture(texture, Rect(i % 4 * 96, 106 + i / 4 * 106, 96, 104));
	}

	auto animate = Animate::create(animation);
//	action->setTag(TAG_MOVE_ACTION);
	spr->runAction(RepeatForever::create(animate));

	// 비행기 터치 및 이동 이벤트
	listener = EventListenerTouchOneByOne::create();
	listener->setEnabled(true);
	listener->onTouchBegan = CC_CALLBACK_2(GamePlayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GamePlayer::onTouchMoved, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
}

/*------------------------------------------------------------------------------------
| 함 수 명  : onTouchBegan(Touch *touch, Event *unused_event)
| 매개변수  : touch = 터치정보, unused_event = 이벤트 정보
| 리 턴 값  : bool = 실패, 성공.
| 설    명  : 플레이어 비행기 터치
|------------------------------------------------------------------------------------*/
bool GamePlayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto sprPlayer = (Sprite*)layerScene->getChildByTag(TAG_SPRITE_PLAYER);

	// 스프라이트가 없다면 리턴
	if (!sprPlayer) 
		return true;

	if (sprPlayer->getActionByTag(TAG_MOVE_ACTION)) 
		sprPlayer->stopActionByTag(TAG_MOVE_ACTION);
	
	// 처음 터치한 포인트
	posStartTouch = touch->getLocation();			// 움직이는 터치 때 쓸 값 입력
	posStartPlayer = sprPlayer->getPosition();
	Point posTouch = touch->getLocation();
	Point posPlayer = sprPlayer->getPosition();


	float distance = sqrtf((posTouch.x - posPlayer.x)*(posTouch.x - posPlayer.x) 
		+ (posTouch.y - posPlayer.y)*(posTouch.y - posPlayer.y));
	
	
	auto action = MoveTo::create(distance / 500.0, posTouch);
	action->setTag(TAG_MOVE_ACTION);
	sprPlayer->runAction(action);

	return true;
}

/*------------------------------------------------------------------------------------
| 함 수 명  : onTouchMoved(Touch *touch, Event *unused_event)
| 매개변수  : touch = 터치정보, unused_event = 이벤트 정보
| 리 턴 값  : 
| 설    명  : 플레이어 비행기 터치 하면서 이동.
|------------------------------------------------------------------------------------*/
void GamePlayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	Point location = touch->getLocation();
	Point posChange = location - posStartTouch;
	Point pos = posStartPlayer + posChange;

	if (pos.x < 0)
		pos.x = 0;
	if (pos.x > Director::getInstance()->getWinSize().width)
		pos.x = Director::getInstance()->getWinSize().width;

	if (pos.y < 0)
		pos.y = 0;
	if (pos.y > Director::getInstance()->getWinSize().height)
		pos.y = Director::getInstance()->getWinSize().height;


	// 이동하는 경로에 맞게 비행기 화면에 뿌리기.
	auto sprPlayer = (Sprite*)layerScene->getChildByTag(TAG_SPRITE_PLAYER);
	sprPlayer->setPosition(pos);

}

/*------------------------------------------------------------------------------------
| 함 수 명  : ChangeScene()
| 매개변수  : 
| 리 턴 값  :
| 설    명  : 화면 전환 시 모든 이벤트 입력 중단
|------------------------------------------------------------------------------------*/
void GamePlayer::ChangeScene()
{
	listener->setEnabled(false);
}