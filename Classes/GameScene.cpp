#include "GameScene.h"


USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

/*------------------------------------------------------------------------------------
| 함 수 명  : init(void)
| 매개변수  :
| 리 턴 값  :
| 설    명  : 게임에 관련한 모든 설정 초기화
|------------------------------------------------------------------------------------*/
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	// 배경 초기화
	initBackGround();

	// 각종 스프라이트에 쓸 레이어 생성
	auto layer = Layer::create();
	this->addChild(layer);

	// 초기화
	Player.initPlayer(layer);
	Missile.initMissile(layer);
	Item.initItem(layer);
	Enemy.initEnemy(layer);


	// 매번 호출 할 함수 지정
	this->schedule(schedule_selector(GameScene::scheduleMissile), 0.1);				
	this->schedule(schedule_selector(GameScene::scheduleItem), 5.0 + rand() % 4);
	this->schedule(schedule_selector(GameScene::scheduleEnemy), 1.0 + rand() % 2);
//	this->scheduleOnce(schedule_selector(GameItem::resetisItem), 5.0);
	this->scheduleUpdate();

	return true;
}

/*------------------------------------------------------------------------------------
| 함 수 명  : scheduleMissile(float delta)
| 매개변수  : delta = 초
| 리 턴 값  :
| 설    명  : 미사일 스케줄
|------------------------------------------------------------------------------------*/
void GameScene::scheduleMissile(float delta)
{
	// 미사일 발사
	Missile.setMissile(delta, Item.getisItem());
}

/*------------------------------------------------------------------------------------
| 함 수 명  : scheduleItem(float delta)
| 매개변수  : delta = 초
| 리 턴 값  :
| 설    명  : 아이템 스케줄
|------------------------------------------------------------------------------------*/
void GameScene::scheduleItem(float delta)
{
	// 아이템 생성 및 이동
	Item.setItem(delta);
}

/*------------------------------------------------------------------------------------
| 함 수 명  : scheduleEnemy(float delta)
| 매개변수  : delta = 초
| 리 턴 값  :
| 설    명  : 아이템 스케줄
|------------------------------------------------------------------------------------*/
void GameScene::scheduleEnemy(float delta)
{
	// 아이템 생성 및 이동
	Enemy.setEnemy(delta);
}

void GameScene::menuCloseCallback(Ref* pSender)
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
| 설    명  : 게임 배경화면 초기화
|------------------------------------------------------------------------------------*/
void GameScene::initBackGround()
{
	auto bgLayer = Layer::create();
	this->addChild(bgLayer);

	// 화면 비율에 맞게 스프라이트 생성.
	auto spr_0 = Sprite::create("game/bg_back.png");
	spr_0->setAnchorPoint(Point::ZERO);
	spr_0->setPosition(Point::ZERO);
	spr_0->setScaleX(Director::getInstance()->getWinSize().width / 1280);
	spr_0->setScaleY(Director::getInstance()->getWinSize().height / 720);
	bgLayer->addChild(spr_0);

	// 움직이는 배경을 위해 같은 스프라이트 생성.
	auto spr_1 = Sprite::create("game/bg_back.png");
	spr_1->setAnchorPoint(Point::ZERO);
	spr_1->setPosition(Point(0, Director::getInstance()->getWinSize().height));
	spr_1->setScaleX(Director::getInstance()->getWinSize().width / 1280);
	spr_1->setScaleY(Director::getInstance()->getWinSize().height / 720);
	bgLayer->addChild(spr_1);

	// 액션을 이용해서 배경을 움직임.
	auto action_0 = MoveBy::create(10.0, Point(0, -(Director::getInstance()->getWinSize().height)));
	auto action_1 = Place::create(Point::ZERO);
	auto action_2 = Sequence::create(action_0, action_1, NULL);
	auto action_3 = RepeatForever::create(action_2);
	bgLayer->runAction(action_3);

}

void GameScene::update(float delta)
{
	Item.updateItem();
//	Missile.updateMissile(Item.getisItem());
//	Missile.setMissile(delta, Item.getisItem());

	if (Item.getisItem())
		this->scheduleOnce(schedule_selector(GameScene::resetisItem), 5.0);

}

void GameScene::resetisItem(float delta)
{
	Item.resetisItem( delta);
}