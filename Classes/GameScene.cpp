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

	// ��� �ʱ�ȭ
	initBackGround();

	// ���� ��������Ʈ�� �� ���̾� ����
	auto layer = Layer::create();
	this->addChild(layer);

	layerScene = layer;

	// �ʱ�ȭ
	Player.initPlayer(layer);
	PlayerMissile.initMissile(layer);

	Enemy.initEnemy(layer);
	EnemyMissile.initMissile(layer);

	Item.initItem(layer);

	// ������� �ʱ�ȭ
	SimpleAudioEngine::getInstance()->playBackgroundMusic("game/bgm.mp3", true);
	

	// �Ź� ȣ�� �� �Լ� ����
	this->schedule(schedule_selector(GameScene::scheduleEnMissile), 0.5);		
	this->schedule(schedule_selector(GameScene::schedulePlMissile), 0.1);
	this->schedule(schedule_selector(GameScene::scheduleItem), 5.0 + rand() % 4);
	this->schedule(schedule_selector(GameScene::scheduleEnemy), 1.0 + rand() % 2);
//	this->scheduleOnce(schedule_selector(GameItem::resetisItem), 5.0);
	this->scheduleUpdate();

	return true;
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
	EnemyMissile.setMissile(delta, Enemy.getSprEnemies());
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
	PlayerMissile.setMissile(delta, Item.getisItem());
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
| ��    ��  : ������ ������
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
	auto bgLayer = Layer::create();
	this->addChild(bgLayer);

	// ȭ�� ������ �°� ��������Ʈ ����.
	auto spr_0 = Sprite::create("game/bg_back.png");
	spr_0->setAnchorPoint(Point::ZERO);
	spr_0->setPosition(Point::ZERO);
	spr_0->setScaleX(Director::getInstance()->getWinSize().width / 1280);
	spr_0->setScaleY(Director::getInstance()->getWinSize().height / 720);
	bgLayer->addChild(spr_0);

	// �����̴� ����� ���� ���� ��������Ʈ ����.
	auto spr_1 = Sprite::create("game/bg_back.png");
	spr_1->setAnchorPoint(Point::ZERO);
	spr_1->setPosition(Point(0, Director::getInstance()->getWinSize().height));
	spr_1->setScaleX(Director::getInstance()->getWinSize().width / 1280);
	spr_1->setScaleY(Director::getInstance()->getWinSize().height / 720);
	bgLayer->addChild(spr_1);

	// �׼��� �̿��ؼ� ����� ������.
	auto action_0 = MoveBy::create(10.0, Point(0, -(Director::getInstance()->getWinSize().height)));
	auto action_1 = Place::create(Point::ZERO);
	auto action_2 = Sequence::create(action_0, action_1, NULL);
	auto action_3 = RepeatForever::create(action_2);
	bgLayer->runAction(action_3);

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

	// �÷��̾�� ������ �浹 üũ
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
		//	Player.ChangeScene();
		//	Director::getInstance()->popScene();
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
		//	Player.ChangeScene();		
		//	Director::getInstance()->popScene();
			break;
		}
	}
	


//	PlayerMissile.updateMissile(Item.getisItem());

}

/*------------------------------------------------------------------------------------
| �� �� ��  : resetisItem(float delta)
| �Ű�����  : delta = ��
| �� �� ��  :
| ��    ��  : ������ ����
|------------------------------------------------------------------------------------*/
void GameScene::resetisItem(float delta)
{
	Item.resetisItem(delta);
}