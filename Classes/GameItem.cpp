#include "GameItem.h"

USING_NS_CC;

/*Scene* GameItem::createScene()
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
bool GameItem::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	return true;
}


void GameItem::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif 

}

/*------------------------------------------------------------------------------------
| 함 수 명  : setItem(float delta)
| 매개변수  : delta = 초
| 리 턴 값  :
| 설    명  : 움직이는 아이템 셋팅
|------------------------------------------------------------------------------------*/
void GameItem::setItem(float delta)
{
	// x값 랜덤 생성
	int x = PADDING_SCREEN + rand() % ((int)Director::getInstance()->getWinSize().width - PADDING_SCREEN * 2);

	Sprite* sprItem;
	
	// 아이템 스프라이트 생성
	if (rand() % 2 == 1)
	{
		sprItem = Sprite::create("game/buffitem.png");
		sprItem->setPosition(Point(x, Director::getInstance()->getWinSize().height));
		sprItem->setScale(1.5f);
		layerScene->addChild(sprItem);

		// 생성한 아이템 백터에 넣기
		BufItems.pushBack(sprItem);
	}

	else
	{
		sprItem = Sprite::create("game/debuffitem.png");
		sprItem->setPosition(Point(x, Director::getInstance()->getWinSize().height));
		sprItem->setScale(0.08f);
		layerScene->addChild(sprItem);

		// 생성한 아이템 백터에 넣기
		DebufItems.pushBack(sprItem);
	}


	// 아래로 떨어지는 액션 실행
	auto action = Sequence::create(MoveBy::create(fSpeed, Point(0, -(Director::getInstance()->getWinSize().height))),
		CallFuncN::create(CC_CALLBACK_1(GameItem::resetItem, this)), NULL);
	sprItem->runAction(action);

}

/*------------------------------------------------------------------------------------
| 함 수 명  : resetItem(Ref *sender)
| 매개변수  : sender = 화면 밖으로 나간 스프라이트
| 리 턴 값  :
| 설    명  : 스프라이트 해제
|------------------------------------------------------------------------------------*/
void GameItem::resetItem(Ref *sender)
{
	auto sprItem = (Sprite*)sender;

	if (BufItems.contains(sprItem))
	{
		BufItems.eraseObject(sprItem);
	}
	else
	{
		DebufItems.eraseObject(sprItem);
	}
		
	layerScene->removeChild(sprItem);

}

/*------------------------------------------------------------------------------------
| 함 수 명  : initItem(cocos2d::Layer* lay)
| 매개변수  : lay = 게임화면 레이어
| 리 턴 값  :
| 설    명  : 게임화면 레이어값과 아이템 설정값 초기화
|------------------------------------------------------------------------------------*/
void GameItem::initItem(cocos2d::Layer* lay)
{
	layerScene = lay;
	fSpeed = 3.0;
	BufItems.clear();
	DebufItems.clear();
	Type = 0;
}

/*------------------------------------------------------------------------------------
| 함 수 명  : updatBbufItem(Ref *sender)
| 매개변수  : sender = 충돌 한 아이템 스프라이트
| 리 턴 값  :
| 설    명  : 충돌 된 버프 아이템 초기화 
|------------------------------------------------------------------------------------*/
void GameItem::updateBufItem(Ref *sender)
{
	auto sprItem = (Sprite*)sender;

	if (BufItems.contains(sprItem))
	{
		resetItem(sprItem);
		Type = 1;
	}
}

/*------------------------------------------------------------------------------------
| 함 수 명  : updateDebufItem(Ref *sender)
| 매개변수  : sender = 충돌 한 아이템 스프라이트
| 리 턴 값  :
| 설    명  : 충돌 된 디버프 아이템 초기화
|------------------------------------------------------------------------------------*/
void GameItem::updateDebufItem(Ref *sender)
{
	auto sprItem = (Sprite*)sender;

	if (DebufItems.contains(sprItem))
	{
		resetItem(sprItem);
		Type = 2;
	}
}

/*------------------------------------------------------------------------------------
| 함 수 명  : getBufSprItems()
| 매개변수  :
| 리 턴 값  : Vector<Sprite*> = 아이템 vecor
| 설    명  : 버프 아이템 vecotr 리턴
|------------------------------------------------------------------------------------*/
Vector<Sprite*>	GameItem::getBufSprItems()
{
	return BufItems;
}

/*------------------------------------------------------------------------------------
| 함 수 명  : getDebufSprItems()
| 매개변수  :
| 리 턴 값  : Vector<Sprite*> = 아이템 vecor
| 설    명  : 디아이템 vecotr 리턴
|------------------------------------------------------------------------------------*/
Vector<Sprite*>	GameItem::getDebufSprItems()
{
	return DebufItems;
}

/*------------------------------------------------------------------------------------
| 함 수 명  : setType(int ty)
| 매개변수  : ty = 아이템 종류
| 리 턴 값  : 
| 설    명  : 아이템 종류 셋팅
|------------------------------------------------------------------------------------*/
void GameItem::setType(int ty)
{
	Type = ty;
}

/*------------------------------------------------------------------------------------
| 함 수 명  : getType()
| 매개변수  : 
| 리 턴 값  : int = 아이템 종류 ( 0 = 아이템 미습득, 1 = 버프 아이템, 2 = 디버프 아이템 )
| 설    명  : 아이템 종류 리턴
|------------------------------------------------------------------------------------*/
int GameItem::getType()
{
	return Type;
}