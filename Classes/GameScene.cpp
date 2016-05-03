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

	// 화면 사이즈
	SizeW = Director::getInstance()->getWinSize().width;
	SizeH = Director::getInstance()->getWinSize().height;

	// 배경 초기화
	initBackGround();

	// 각종 스프라이트에 쓸 레이어 생성
	auto layer = Layer::create();
	this->addChild(layer);
	layerScene = layer;

	// 라벨 초기화
	initLabel();

	// 비행기 초기화
	Player.initPlayer(layer);
	PlayerMissile.initMissile(layer);

	Enemy.initEnemy(layer);
	EnemyMissile.initMissile(layer);

	Item.initItem(layer);

	// 배경음악 초기화
	SimpleAudioEngine::getInstance()->playBackgroundMusic("game/bgm.mp3", true);

	// 데이터 초기화
	Data.initTime();

	// 매번 호출 할 함수 지정
	this->schedule(schedule_selector(GameScene::scheduleEnMissile), 0.5f);		
	this->schedule(schedule_selector(GameScene::schedulePlMissile), 0.1f);
	this->schedule(schedule_selector(GameScene::scheduleItem), 5.0 + rand() % 4);
	this->schedule(schedule_selector(GameScene::scheduleEnemy), 1.0f - Data.getLevel()); 
//	this->scheduleOnce(schedule_selector(GameItem::resetisItem), 5.0);
	this->scheduleUpdate();

	return true;
}

/*------------------------------------------------------------------------------------
| 함 수 명  : initLabel()
| 매개변수  :
| 리 턴 값  :
| 설    명  : 라벨 초기화
|------------------------------------------------------------------------------------*/
void GameScene::initLabel()
{
	auto labelcurScore = Label::createWithSystemFont("", "Thonburi", 20);
	auto labelbuffItem = Label::createWithSystemFont("", "Thonburi", 20);
	auto labeldebuffItem = Label::createWithSystemFont("", "Thonburi", 20);

	labelcurScore->setAnchorPoint(Point(1, 1));
	labelcurScore->setPosition(Point(SizeW - 10, SizeH - 10));
	labelcurScore->setTag(TAG_LABEL_SCORE);
	this->addChild(labelcurScore);

	labelbuffItem->setAnchorPoint(Point(0, 0));
	labelbuffItem->setPosition(Point(10, 40 ));
	labelbuffItem->setTag(TAG_LABEL_BUFFITEM);
	this->addChild(labelbuffItem);

	labeldebuffItem->setAnchorPoint(Point(0, 0));
	labeldebuffItem->setPosition(Point(10, 10));
	labeldebuffItem->setTag(TAG_LABEL_DEBUFFITEM);
	this->addChild(labeldebuffItem);
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

	// ParallaxNode 이용. 다중 이미지 배경 스크롤
	auto node = ParallaxNode::create();
	this->addChild(node);
	auto action_0 = MoveBy::create(10.0, Point(0, -720));
	auto action_1 = Place::create(Point::ZERO);
	auto action_2 = Sequence::create(action_0, action_1, NULL);
	auto action_3 = RepeatForever::create(action_2);
	node->runAction(action_3);


	// 가장 뒤의 배경. 속도 1배속
	auto spr_00 = Sprite::create("game/bg_back.png");
	spr_00->setAnchorPoint(Point::ZERO);
	spr_00->setScaleX(SizeW / 1280);
	node->addChild(spr_00, 0, Point(0, 1), Point::ZERO);

	auto spr_01 = Sprite::create("game/bg_back.png");
	spr_01->setAnchorPoint(Point::ZERO);
	spr_01->setScaleX(SizeW / 1280);
	node->addChild(spr_01, 0, Point(0, 1), Point(0, 720));


	// 중간 배경, 속도 0.5배속
	auto spr_10 = Sprite::create("game/bg_middle.png");
	spr_10->setAnchorPoint(Point::ZERO);
	spr_10->setScaleX(SizeW / 1280);
	node->addChild(spr_10, 1, Point(0, 0.5), Point::ZERO);

	auto spr_11 = Sprite::create("game/bg_middle.png");
	spr_11->setAnchorPoint(Point::ZERO);
	spr_11->setScaleX(SizeW / 1280);
	node->addChild(spr_11, 1, Point(0, 0.5), Point(0, 360));


	// 바깥 배경. 속도 2배속
	auto spr_20 = Sprite::create("game/bg_front.png");
	spr_20->setAnchorPoint(Point::ZERO);
	spr_20->setScaleX(SizeW / 1280);
	node->addChild(spr_20, 2, Point(0, 2), Point::ZERO);

	auto spr_21 = Sprite::create("game/bg_front.png");
	spr_21->setAnchorPoint(Point::ZERO);
	spr_21->setScaleX(SizeW / 1280);
	node->addChild(spr_21, 2, Point(0, 2), Point(0, 720));

	auto spr_22 = Sprite::create("game/bg_front.png");
	spr_22->setAnchorPoint(Point::ZERO);
	spr_22->setScaleX(SizeW / 1280);
	node->addChild(spr_22, 2, Point(0, 2), Point(0, 1440));

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
			Data.setBuffItem(1);			// 버프아이템 습득시
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
				 Data.setScore(10);
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
		//	Player.ChangeScene();					// 플레이어 이벤트 모두 끄기
		//	auto scene = TransitionTurnOffTiles::create(1.0, GameOverScene::createScene());
		//	Director::getInstance()->replaceScene(scene);
		//	Director::getInstance()->popScene();
			changeScene();
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

	updateLabel();


//	PlayerMissile.updateMissile(Item.getisItem());

}

/*------------------------------------------------------------------------------------
| 함 수 명  : updateLabel()
| 매개변수  : 
| 리 턴 값  :
| 설    명  : 라벨 업데이트
|------------------------------------------------------------------------------------*/
void GameScene::updateLabel()
{
	auto labelScore = (Label*)this->getChildByTag(TAG_LABEL_SCORE);
	labelScore->setString(StringUtils::format("SCORE : %d", Data.getScore()));

	auto labelBuffItem = (Label*)this->getChildByTag(TAG_LABEL_BUFFITEM);
	labelBuffItem->setString(StringUtils::format("BUFFITEM : %d", Data.getBuffItem()));

//	auto labelDeBuffItem = (Label*)this->getChildByTag(TAG_LABEL_DEBUFFITEM);
//	labelDeBuffItem->setString(StringUtils::format("DEBUFFITEM : %d", Data.getDeBuffItem()));
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

/*------------------------------------------------------------------------------------
| 함 수 명  : changeScene()
| 매개변수  : 
| 리 턴 값  :
| 설    명  : 화면 전환
|------------------------------------------------------------------------------------*/
void GameScene::changeScene()
{
/*	this->unschedule(schedule_selector(GameScene::scheduleEnMissile));
	this->unschedule(schedule_selector(GameScene::schedulePlMissile));
	this->unschedule(schedule_selector(GameScene::scheduleItem));
	this->unschedule(schedule_selector(GameScene::scheduleEnemy));
	//	this->scheduleOnce(schedule_selector(GameItem::resetisItem), 5.0);
	this->unscheduleUpdate();*/

	this->unscheduleAllSelectors();

	Director::getInstance()->resume();
	

	Player.ChangeScene();					// 플레이어 이벤트 모두 끄기
	auto scene = TransitionTurnOffTiles::create(1.0, GameOverScene::createScene());
	Director::getInstance()->replaceScene(scene);
	
	
}