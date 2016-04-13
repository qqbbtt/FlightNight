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

void GameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif 

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

	layerScene = layer;

	// 초기화
	Player.initPlayer(layer);
	PlayerMissile.initMissile(layer);

	Enemy.initEnemy(layer);
	EnemyMissile.initMissile(layer);

	Item.initItem(layer);

	// 배경음악 초기화
	SimpleAudioEngine::getInstance()->playBackgroundMusic("game/bgm.mp3", true);
	

	// 매번 호출 할 함수 지정
	this->schedule(schedule_selector(GameScene::scheduleEnMissile), 0.5);		
	this->schedule(schedule_selector(GameScene::schedulePlMissile), 0.1);
	this->schedule(schedule_selector(GameScene::scheduleItem), 5.0 + rand() % 4);
	this->schedule(schedule_selector(GameScene::scheduleEnemy), 1.0 + rand() % 2);
//	this->scheduleOnce(schedule_selector(GameItem::resetisItem), 5.0);
	this->scheduleUpdate();

	return true;
}

/*------------------------------------------------------------------------------------
| 함 수 명  : scheduleEnMissile(float delta)
| 매개변수  : delta = 초
| 리 턴 값  :
| 설    명  : 적비행기 미사일 스케줄
|------------------------------------------------------------------------------------*/
void GameScene::scheduleEnMissile(float delta)
{
	// 미사일 발사
	EnemyMissile.setMissile(delta, Enemy.getSprEnemies());
}

/*------------------------------------------------------------------------------------
| 함 수 명  : schedulePlMissile(float delta)
| 매개변수  : delta = 초
| 리 턴 값  :
| 설    명  : 플레이어 미사일 스케줄
|------------------------------------------------------------------------------------*/
void GameScene::schedulePlMissile(float delta)
{
	// 미사일 발사
	PlayerMissile.setMissile(delta, Item.getisItem());
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

/*------------------------------------------------------------------------------------
| 함 수 명  : update(float delta)
| 매개변수  : delta = 초
| 리 턴 값  :
| 설    명  : update
|------------------------------------------------------------------------------------*/
void GameScene::update(float delta)
{
	auto sprPlayer = (Sprite*)layerScene->getChildByTag(TAG_SPRITE_PLAYER);
	Rect rectPlayer = sprPlayer->getBoundingBox();

	Rect rect1, rect2;

	// 플레이어와 아이템 충돌 체크
	for (Sprite* sprItem : Item.getSprItems())
	{
		rect1 = sprItem->getBoundingBox();

		if (rectPlayer.intersectsRect(rect1))
		{
			Item.updateItem(sprItem);
			this->scheduleOnce(schedule_selector(GameScene::resetisItem), 5.0);
			break;
		}		
	}

	// 플레이어 미사일과 적비행기 충돌 체크
	for (Sprite* missile : PlayerMissile.getSprMissiles()) 
	{
		rect1 = missile->getBoundingBox();

		for (Sprite* sprEnemy : Enemy.getSprEnemies() )
		{
			 rect2 = sprEnemy->getBoundingBox();

			 if (rect2.intersectsRect(rect1))
			{
				 Enemy.explosionEnemy(sprEnemy);
				 PlayerMissile.resetMissile(missile);
				 Enemy.resetEnemy(sprEnemy);
				 SimpleAudioEngine::getInstance()->playEffect("game/boom.wav");
				 break;
			}
		}
	}

	// 플레이어와 적미사일 충돌 체크
	for (Sprite* sprmissile : EnemyMissile.getSprMissiles())
	{
		rect1 = sprmissile->getBoundingBox();

		if (rectPlayer.intersectsRect(rect1))
		{
			EnemyMissile.resetMissile(sprmissile);
		//	Player.ChangeScene();
		//	Director::getInstance()->popScene();
			break;
		}
	}

	// 플레이어와 적비행기 충돌 체크
	for (Sprite* sprEnemy : Enemy.getSprEnemies())
	{
		rect1 = sprEnemy->getBoundingBox();
		rect1 = Rect(rect1.origin.x + 30, rect1.origin.y + 30, rect1.size.width - 30, rect1.size.height - 30);
		rect2 = sprPlayer->getBoundingBox();
		rect2 = Rect(rect2.origin.x + 30, rect2.origin.y + 30, rect2.size.width - 30, rect2.size.height - 30);


		if (rect2.intersectsRect(rect1))
		{
			Enemy.explosionEnemy(sprEnemy);
			Enemy.resetEnemy(sprEnemy);
		//	Player.ChangeScene();		
		//	Director::getInstance()->popScene();
			break;
		}
	}
	


//	PlayerMissile.updateMissile(Item.getisItem());

}

/*------------------------------------------------------------------------------------
| 함 수 명  : resetisItem(float delta)
| 매개변수  : delta = 초
| 리 턴 값  :
| 설    명  : 아이템 리셋
|------------------------------------------------------------------------------------*/
void GameScene::resetisItem(float delta)
{
	Item.resetisItem(delta);
}