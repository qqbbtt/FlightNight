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
| 함 수 명  : setMissile(float delta, int type)
| 매개변수  : delta = 초, type = 아이템 종류
| 리 턴 값  :
| 설    명  : 움직이는 미사일 셋팅 (플레이어 미사일)
|------------------------------------------------------------------------------------*/
void GameMissile::setMissile(float delta, int type)
{
	// 게임화면 레이어에서 플레이어 비행기 정보 가져오기
	auto sprPlayer = (Sprite*)layerScene->getChildByTag(TAG_SPRITE_PLAYER);

	// 미사일 스프라이트 생성
	Sprite *sprMissile;
	if ( type == 1 )  // 버프 아이템을 먹었다면
	{
		sprMissile = Sprite::create("game/missile2.png");
		sprMissile->setScale(1.0f);
		sprMissile->setTag(5);
	}
	else 
	{
		sprMissile = Sprite::create("game/missile1.png");
		sprMissile->setScale(0.5f);
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

	SimpleAudioEngine::getInstance()->playEffect("game/enemy_missile.wav");
}

/*------------------------------------------------------------------------------------
| 함 수 명  : setMissile(float delta, Vector<Sprite*> enemy, bool item, bool type)
| 매개변수  : delta = 초, enemy = 적 비행기, type = 아이템 종류
| 리 턴 값  :
| 설    명  : 움직이는 미사일 셋팅 (적비행기 미사일)
|------------------------------------------------------------------------------------*/
void GameMissile::setMissile(float delta, Vector<Sprite*> enemy, int type)
{
	// 적 비행기만큼 미사일 생성
	for (Sprite* sprEnemy : enemy)
	{
		Sprite* sprMissile;

		if ( type == 2 )
		{
			sprMissile = Sprite::create("game/missile4.png");

			sprMissile->setPosition(sprEnemy->getPosition() + Point(1, 20));
			sprMissile->setScale(2.0f);
			layerScene->addChild(sprMissile, 1);
			Missiles.pushBack(sprMissile);
		}
		else
		{
			sprMissile = Sprite::create("game/missile3.png");

			sprMissile->setPosition(sprEnemy->getPosition() + Point(1, 20));
			sprMissile->setScale(2.0f);
			layerScene->addChild(sprMissile, 1);
			Missiles.pushBack(sprMissile);
		}


		// 발사되는 미사일 액션 활성화
		auto action = Sequence::create(MoveBy::create(fSpeed, Point(0, -Director::getInstance()->getWinSize().height)),
			CallFuncN::create(CC_CALLBACK_1(GameMissile::resetMissile, this)), NULL);
		sprMissile->runAction(action);

		SimpleAudioEngine::getInstance()->playEffect("game/enemy_missile.wav");

	}

}

/*------------------------------------------------------------------------------------
| 함 수 명  : resetMissile(Ref *sender)
| 매개변수  : sender = 화면 밖으로 나간 스프라이트
| 리 턴 값  :
| 설    명  : 스프라이트 해제
|------------------------------------------------------------------------------------*/
void GameMissile::resetMissile(Ref *sender)
{
	auto sprMissile = (Sprite*)sender;
	Missiles.eraseObject(sprMissile);
	layerScene->removeChild(sprMissile);
}

/*------------------------------------------------------------------------------------
| 함 수 명  : initMissile(cocos2d::Layer* lay)
| 매개변수  : lay = 게임화면 레이어값
| 리 턴 값  :
| 설    명  : 게임화면 레이어값 및 초기화
|------------------------------------------------------------------------------------*/
void GameMissile::initMissile(cocos2d::Layer* lay)
{
	layerScene = lay;
	fSpeed = 1.0f;
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

/*------------------------------------------------------------------------------------
| 함 수 명  : getSprMissiles()
| 매개변수  :
| 리 턴 값  : Vector<Sprite*> = 미사일 vecor
| 설    명  : 미사일 vecotr 리턴
|------------------------------------------------------------------------------------*/
Vector<Sprite*>	GameMissile::getSprMissiles()
{
	return Missiles;
}
