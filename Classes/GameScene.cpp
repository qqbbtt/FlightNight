#include "GameScene.h"
#include "GameData.h"
#include "FlightNightDataBase.h"

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
| �� �� ��  : init(void)
| �Ű�����  :
| �� �� ��  :
| ��    ��  : ���ӿ� ������ ��� ���� �ʱ�ȭ
|------------------------------------------------------------------------------------*/
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	// ȭ�� ������
	SizeW = Director::getInstance()->getWinSize().width;
	SizeH = Director::getInstance()->getWinSize().height;

	// �̻��� �ӵ�
	speedEn = 0.5f;
	speedPl = 0.3f;

	// ��� �ʱ�ȭ
	initBackGround();

	// ������� �ʱ�ȭ
	initSound();

	// ���� ��������Ʈ�� �� ���̾� ����
	auto layer = Layer::create();
	this->addChild(layer);
	layerScene = layer;

	// �� �ʱ�ȭ
	initLabel();

	// ����� �ʱ�ȭ
	Player.initPlayer(layer);
	PlayerMissile.initMissile(layer);

	Enemy.initEnemy(layer);
	EnemyMissile.initMissile(layer);

	Item.initItem(layer);

	// ������ �ʱ�ȭ
	gmData.initTime();

	// �Ź� ȣ�� �� �Լ� ���� (�ӵ� ����)
	this->schedule(schedule_selector(GameScene::scheduleEnMissile), speedEn);		
	this->schedule(schedule_selector(GameScene::schedulePlMissile), speedPl);
	this->schedule(schedule_selector(GameScene::scheduleItem), 5.0 + rand() % 4);
	this->schedule(schedule_selector(GameScene::scheduleEnemy), 1.0f);
	this->scheduleUpdate();

	return true;
}

void GameScene::initSound()
{
//	if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	{
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic("game/bgm.mp3");
		SimpleAudioEngine::getInstance()->playBackgroundMusic("game/bgm.mp3", true);

		SimpleAudioEngine::getInstance()->preloadEffect("game/enemy_missile.wav");
		SimpleAudioEngine::getInstance()->preloadEffect("game/explosion.wav");
		SimpleAudioEngine::getInstance()->preloadEffect("game/player_missile.wav");
//	}
}

/*------------------------------------------------------------------------------------
| �� �� ��  : initLabel()
| �Ű�����  :
| �� �� ��  :
| ��    ��  : �� �ʱ�ȭ
|------------------------------------------------------------------------------------*/
void GameScene::initLabel()
{
	auto labelcurScore = Label::createWithTTF("", "fonts/Marker Felt.ttf", 30);
	auto labelbuffItem = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
	auto labeldebuffItem = Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);

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
| �� �� ��  : scheduleEnMissile(float delta)
| �Ű�����  : delta = ��
| �� �� ��  :
| ��    ��  : ������� �̻��� ������
|------------------------------------------------------------------------------------*/
void GameScene::scheduleEnMissile(float delta)
{
	// �̻��� �߻�
	EnemyMissile.setMissile(delta, Enemy.getSprEnemies(), Item.getType());
}

/*------------------------------------------------------------------------------------
| �� �� ��  : schedulePlMissile(float delta)
| �Ű�����  : delta = ��
| �� �� ��  :
| ��    ��  : �÷��̾� �̻��� ������
|------------------------------------------------------------------------------------*/
void GameScene::schedulePlMissile(float delta)
{
	// �̻��� �߻�
	PlayerMissile.setMissile(delta, Item.getType());
}

/*------------------------------------------------------------------------------------
| �� �� ��  : scheduleItem(float delta)
| �Ű�����  : delta = ��
| �� �� ��  :
| ��    ��  : ������ ������
|------------------------------------------------------------------------------------*/
void GameScene::scheduleItem(float delta)
{
	// ������ ���� �� �̵�
	Item.setItem(delta);
}

/*------------------------------------------------------------------------------------
| �� �� ��  : scheduleEnemy(float delta)
| �Ű�����  : delta = ��
| �� �� ��  :
| ��    ��  : ������� ������
|------------------------------------------------------------------------------------*/
void GameScene::scheduleEnemy(float delta)
{
	// ������ ���� �� �̵�
	Enemy.setEnemy(delta);
	
}

/*------------------------------------------------------------------------------------
| �� �� ��  : initBackGround(void)
| �Ű�����  :
| �� �� ��  :
| ��    ��  : ���� ���ȭ�� �ʱ�ȭ
|------------------------------------------------------------------------------------*/
void GameScene::initBackGround()
{

	// ParallaxNode �̿�. ���� �̹��� ��� ��ũ��
	auto node = ParallaxNode::create();
	this->addChild(node);
	auto action_0 = MoveBy::create(10.0, Point(0, -720));
	auto action_1 = Place::create(Point::ZERO);
	auto action_2 = Sequence::create(action_0, action_1, NULL);
	auto action_3 = RepeatForever::create(action_2);
	node->runAction(action_3);


	// ���� ���� ���. �ӵ� 1���
	auto spr_00 = Sprite::create("game/bg_back.png");
	spr_00->setAnchorPoint(Point::ZERO);
	spr_00->setScaleX(SizeW / 1280);
	node->addChild(spr_00, 0, Point(0, 1), Point::ZERO);

	auto spr_01 = Sprite::create("game/bg_back.png");
	spr_01->setAnchorPoint(Point::ZERO);
	spr_01->setScaleX(SizeW / 1280);
	node->addChild(spr_01, 0, Point(0, 1), Point(0, 720));


	// �߰� ���, �ӵ� 0.5���
	auto spr_10 = Sprite::create("game/bg_middle.png");
	spr_10->setAnchorPoint(Point::ZERO);
	spr_10->setScaleX(SizeW / 1280);
	node->addChild(spr_10, 1, Point(0, 0.5), Point::ZERO);

	auto spr_11 = Sprite::create("game/bg_middle.png");
	spr_11->setAnchorPoint(Point::ZERO);
	spr_11->setScaleX(SizeW / 1280);
	node->addChild(spr_11, 1, Point(0, 0.5), Point(0, 360));


	// �ٱ� ���. �ӵ� 2���
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
| �� �� ��  : update(float delta)
| �Ű�����  : delta = ��
| �� �� ��  :
| ��    ��  : update
|------------------------------------------------------------------------------------*/
void GameScene::update(float delta)
{
	auto sprPlayer = (Sprite*)layerScene->getChildByTag(TAG_SPRITE_PLAYER);
	Rect rectPlayer = sprPlayer->getBoundingBox();

	Rect rect1, rect2;

	// �÷��̾�� ���� ������ �浹 üũ
	for (Sprite* sprItem : Item.getBufSprItems())
	{
		rect1 = sprItem->getBoundingBox();

		if (rectPlayer.intersectsRect(rect1))
		{
			speedPl = 0.1f;
			Item.updateBufItem(sprItem);
			this->unschedule(schedule_selector(GameScene::schedulePlMissile));
			this->schedule(schedule_selector(GameScene::schedulePlMissile), speedPl);
			this->scheduleOnce(schedule_selector(GameScene::resetItem), 5.0);
			gmData.setBufItem(1);			// ���������� �����
			SimpleAudioEngine::getInstance()->playEffect("game/item.mp3");
			
			break;
		}		
	}

	// �÷��̾�� ����� ������ �浹 üũ
	for (Sprite* sprItem : Item.getDebufSprItems())
	{
		rect1 = sprItem->getBoundingBox();

		if (rectPlayer.intersectsRect(rect1))
		{
			speedEn = 0.2f;
			Item.updateDebufItem(sprItem);
			this->unschedule(schedule_selector(GameScene::scheduleEnMissile));
			this->schedule(schedule_selector(GameScene::scheduleEnMissile), speedEn);
			this->scheduleOnce(schedule_selector(GameScene::resetItem), 5.0);
			gmData.setDebufItem(1);			// ����� ������ �����
			SimpleAudioEngine::getInstance()->playEffect("game/item.mp3");
			

			break;
		}
	}

	// �÷��̾� �̻��ϰ� ������� �浹 üũ
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
				 gmData.setScore(10);

				 if (gmData.getScore() % 50 == 0 && gmData.getScore() != 0 && gmData.getScore() / 50 < 7)
				 {
					 float sp = 0.1f * (gmData.getScore() / 50);
					 CCLOG("gmData.getScore() : %d  |  sp : %f", gmData.getScore(), sp);
					 this->unschedule(schedule_selector(GameScene::scheduleEnemy));
					 this->schedule(schedule_selector(GameScene::scheduleEnemy), 1.0f - sp);
				 }

				 break;
			}
		}
	}

	// �÷��̾�� ���̻��� �浹 üũ
	for (Sprite* sprmissile : EnemyMissile.getSprMissiles())
	{
		rect1 = sprmissile->getBoundingBox();

		if (rectPlayer.intersectsRect(rect1))
		{
			EnemyMissile.resetMissile(sprmissile);
			changeScene();
			break;
		}
	}

	// �÷��̾�� ������� �浹 üũ
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
			changeScene();
			break;
		}
	}	

	updateLabel();

}

/*------------------------------------------------------------------------------------
| �� �� ��  : updateLabel()
| �Ű�����  : 
| �� �� ��  :
| ��    ��  : �� ������Ʈ
|------------------------------------------------------------------------------------*/
void GameScene::updateLabel()
{
	auto labelScore = (Label*)this->getChildByTag(TAG_LABEL_SCORE);
	labelScore->setString(StringUtils::format("SCORE : %d", gmData.getScore()));

	auto labelBuffItem = (Label*)this->getChildByTag(TAG_LABEL_BUFFITEM);
	labelBuffItem->setString(StringUtils::format("BUFFITEM : %d", gmData.getBufItem()));

	auto labelDeBuffItem = (Label*)this->getChildByTag(TAG_LABEL_DEBUFFITEM);
	labelDeBuffItem->setString(StringUtils::format("DEBUFFITEM : %d", gmData.getDebufItem()));
}

/*------------------------------------------------------------------------------------
| �� �� ��  : resetItem(float delta)
| �Ű�����  : delta = ��
| �� �� ��  :
| ��    ��  : ���� ������ ����
|------------------------------------------------------------------------------------*/
void GameScene::resetItem(float delta)
{

	speedPl = 0.3f;
	speedEn = 0.5f;
	Item.setType(0);

	this->unschedule(schedule_selector(GameScene::schedulePlMissile));
	this->schedule(schedule_selector(GameScene::schedulePlMissile), speedPl);
	this->unschedule(schedule_selector(GameScene::scheduleEnMissile));
	this->schedule(schedule_selector(GameScene::scheduleEnMissile), speedEn);
}

void GameScene::resetEnemy(float delta)
{

}

/*------------------------------------------------------------------------------------
| �� �� ��  : changeScene()
| �Ű�����  : 
| �� �� ��  :
| ��    ��  : ȭ�� ��ȯ
|------------------------------------------------------------------------------------*/
void GameScene::changeScene()
{
	this->unscheduleAllSelectors();

	Director::getInstance()->resume();
	
	FNDB.insertdData(gmData.getTime().Year, gmData.getTime().Month, gmData.getTime().Day, gmData.getTime().Hour,
		gmData.getTime().Min, gmData.getScore(), gmData.getBufItem(), gmData.getDebufItem());

	Player.ChangeScene();					// �÷��̾� �̺�Ʈ ��� ����
	auto scene = TransitionTurnOffTiles::create(1.0, GameOverScene::createScene());
	Director::getInstance()->replaceScene(scene);	

	SimpleAudioEngine::getInstance()->unloadEffect("game/enemy_missile.wav");
	SimpleAudioEngine::getInstance()->unloadEffect("game/explosion.wav");
	SimpleAudioEngine::getInstance()->unloadEffect("game/player_missile.wav");
	
}