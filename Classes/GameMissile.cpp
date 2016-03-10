#include "GameMissile.h"

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
bool GameMissile::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	return true;
}


void GameMissile::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif 

}

/*------------------------------------------------------------------------------------
| 함 수 명  : setMissile(float delta)
| 매개변수  : delta = 초
| 리 턴 값  :
| 설    명  : 움직이는 미사일 셋팅
|------------------------------------------------------------------------------------*/
void GameMissile::setMissile(float delta, bool item)
{
	// 게임화면 레이어에서 플레이어 비행기 정보 가져오기
	auto sprPlayer = (Sprite*)layerScene->getChildByTag(TAG_SPRITE_PLAYER);

	// 미사일 스프라이트 생성
//	auto sprMissile = Sprite::create("game/missile.png");

	Sprite *sprMissile;

	if (item) 
	{
		sprMissile = Sprite::create("game/missile_pow.png");
		sprMissile->setTag(5);
	}
	else 
	{
		sprMissile = Sprite::create("game/missile.png");
		sprMissile->setTag(1);
	}


	// 비행기의 위치를 고려해서 스프라이트 위치 지정
	sprMissile->setPosition(sprPlayer->getPosition() + Point(-1, 20));
	// 화면에 뿌리기
	layerScene->addChild(sprMissile, 1);

	Missiles.pushBack(sprMissile);

	// 발사되는 미사일 액션 활성화
	auto action = Sequence::create(MoveBy::create(fSpeed, Point(0, Director::getInstance()->getWinSize().height)),
		CallFuncN::create(CC_CALLBACK_1(GameMissile::resetMissile, this)), NULL);
	sprMissile->runAction(action);
}


/*------------------------------------------------------------------------------------
| 함 수 명  : resetMissile(Ref *sender)
| 매개변수  : sender = 화면 밖으로 나간 스프라이트
| 리 턴 값  :
| 설    명  : 미사일이 화면 밖으로 이동하면 스프라이트 해제
|------------------------------------------------------------------------------------*/
void GameMissile::resetMissile(Ref *sender)
{
	auto sprMissile = (Sprite*)sender;
	Missiles.eraseObject(sprMissile);
	layerScene->removeChild(sprMissile);
}

/*------------------------------------------------------------------------------------
| 함 수 명  : initMissile(cocos2d::Layer* lay, int tag)
| 매개변수  : lay = 게임화면 레이어, tag = 플레이어 테그
| 리 턴 값  :
| 설    명  : 게임화면 레이어값과 플레이어 테그 값 셋팅
|------------------------------------------------------------------------------------*/
void GameMissile::initMissile(cocos2d::Layer* lay)
{
	layerScene = lay;
	fSpeed = 1.0;
	Missiles.clear();
}

void GameMissile::updateMissile(bool item)
{
	auto sprMissile = (Sprite*)layerScene->getChildByTag(TAG_SPRITE_PLAYER);

	if (item)
	{
		auto sprMissile = (Sprite*)layerScene->getChildByTag(5);
	//	sprMissile->setTag(5);
	}
	else
	{
		auto sprMissile = (Sprite*)layerScene->getChildByTag(1);
//		sprMissile->setTag(1);
	}

/*	auto sprPlayer = (Sprite*)layerScene->getChildByTag(TAG_SPRITE_PLAYER);
	Rect rectPlayer = sprPlayer->getBoundingBox();

	auto removeSpr = Sprite::create();

	for (Sprite* sprItem : Items)
	{

		Rect rectItem = sprItem->getBoundingBox();

		if (rectPlayer.intersectsRect(rectItem))
			removeSpr = sprItem;
	}

	if (Items.contains(removeSpr))
	{
		resetItem(removeSpr);
		isItem = true;
		layerScene->scheduleOnce(schedule_selector(GameItem::resetisItem), 5.0);

	}*/
}