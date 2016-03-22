#include "GameEnemy.h"

USING_NS_CC;

/*Scene* GameEnemy::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameEnemy::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}*/


// on "init" you need to initialize your instance
bool GameEnemy::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	return true;
}


void GameEnemy::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif 

}

/*------------------------------------------------------------------------------------
| 함 수 명  : setEnemy(float delta)
| 매개변수  : delta = 초
| 리 턴 값  :
| 설    명  : 움직이는 적비행기 셋팅
|------------------------------------------------------------------------------------*/
void GameEnemy::setEnemy(float delta)
{
	// x값 랜덤 생성
	int x = PADDING_SCREEN + rand() % ((int)Director::getInstance()->getWinSize().width - PADDING_SCREEN * 2);

	// 적 비행기 스프라이트 부르기.
	auto sprEnemy = Sprite::create();
	sprEnemy->setPosition(Point(x, Director::getInstance()->getWinSize().height));
	layerScene->addChild(sprEnemy);

	// 적 비행기 백터에 넣기
	Enemies.pushBack(sprEnemy);

	// 적 비행기 애니메이션
	auto texture = Director::getInstance()->getTextureCache()->addImage("game/Spaceship.png");

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	for (int i = 0; i<4; i++) {
		animation->addSpriteFrameWithTexture(texture, Rect((96*4)+(i % 4 * 96), 106 + i / 4 * 106, 96, 104));
	}

	auto animate = Animate::create(animation);
	//	action->setTag(TAG_MOVE_ACTION);
	sprEnemy->runAction(RepeatForever::create(animate));

	// 아래로 떨어지는 액션 실행
	auto action = Sequence::create(MoveBy::create(fSpeed, Point(0, -(Director::getInstance()->getWinSize().height))),
		CallFuncN::create(CC_CALLBACK_1(GameEnemy::resetEnemy, this)), NULL);
	sprEnemy->runAction(action);

}

/*------------------------------------------------------------------------------------
| 함 수 명  : resetEnemy(Ref *sender)
| 매개변수  : sender = 화면 밖으로 나간 스프라이트
| 리 턴 값  :
| 설    명  : 스프라이트 해제
|------------------------------------------------------------------------------------*/
void GameEnemy::resetEnemy(Ref *sender)
{
	auto sprEnemy = (Sprite*)sender;
	Enemies.eraseObject(sprEnemy);
	layerScene->removeChild(sprEnemy);

}

/*------------------------------------------------------------------------------------
| 함 수 명  : initEnemy(cocos2d::Layer* lay)
| 매개변수  : lay = 게임화면 레이어
| 리 턴 값  :
| 설    명  : 게임화면 레이어값과 아이템 설정값 초기화
|------------------------------------------------------------------------------------*/
void GameEnemy::initEnemy(cocos2d::Layer* lay)
{
	layerScene = lay;
	fSpeed = 3.0;
	Enemies.clear();
}

/*void GameEnemy::updateEnemy()
{
	auto sprPlayer = (Sprite*)layerScene->getChildByTag(TAG_SPRITE_PLAYER);
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

	}
}

void GameEnemy::resetisItem(float delta)
{
	isItem = false;
}

bool GameEnemy::getisItem()
{
	return isItem;
}
*/

/*------------------------------------------------------------------------------------
| 함 수 명  : getSprEnemies()
| 매개변수  : 
| 리 턴 값  : Vector<Sprite*> = 적비행기 vecor
| 설    명  : 적비행기 vecotr 리턴
|------------------------------------------------------------------------------------*/
Vector<Sprite*>	GameEnemy::getSprEnemies()
{
	return Enemies;
}