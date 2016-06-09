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
| �� �� ��  : setMissile(float delta, int type)
| �Ű�����  : delta = ��, type = ������ ����
| �� �� ��  :
| ��    ��  : �����̴� �̻��� ���� (�÷��̾� �̻���)
|------------------------------------------------------------------------------------*/
void GameMissile::setMissile(float delta, int type)
{
	// ����ȭ�� ���̾�� �÷��̾� ����� ���� ��������
	auto sprPlayer = (Sprite*)layerScene->getChildByTag(TAG_SPRITE_PLAYER);

	// �̻��� ��������Ʈ ����
	Sprite *sprMissile;
	if ( type == 1 )  // ���� �������� �Ծ��ٸ�
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

	// ������� ��ġ�� ����ؼ� ��������Ʈ ��ġ ����
	sprMissile->setPosition(sprPlayer->getPosition() + Point(-1, 20));
	// ȭ�鿡 �Ѹ���
	layerScene->addChild(sprMissile, 1);

	Missiles.pushBack(sprMissile);

	// �߻�Ǵ� �̻��� �׼� Ȱ��ȭ
	auto action = Sequence::create(MoveBy::create(fSpeed, Point(0, Director::getInstance()->getWinSize().height)),
		CallFuncN::create(CC_CALLBACK_1(GameMissile::resetMissile, this)), NULL);
	sprMissile->runAction(action);

	SimpleAudioEngine::getInstance()->playEffect("game/enemy_missile.wav");
}

/*------------------------------------------------------------------------------------
| �� �� ��  : setMissile(float delta, Vector<Sprite*> enemy, bool item, bool type)
| �Ű�����  : delta = ��, enemy = �� �����, type = ������ ����
| �� �� ��  :
| ��    ��  : �����̴� �̻��� ���� (������� �̻���)
|------------------------------------------------------------------------------------*/
void GameMissile::setMissile(float delta, Vector<Sprite*> enemy, int type)
{
	// �� ����⸸ŭ �̻��� ����
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


		// �߻�Ǵ� �̻��� �׼� Ȱ��ȭ
		auto action = Sequence::create(MoveBy::create(fSpeed, Point(0, -Director::getInstance()->getWinSize().height)),
			CallFuncN::create(CC_CALLBACK_1(GameMissile::resetMissile, this)), NULL);
		sprMissile->runAction(action);

		SimpleAudioEngine::getInstance()->playEffect("game/enemy_missile.wav");

	}

}

/*------------------------------------------------------------------------------------
| �� �� ��  : resetMissile(Ref *sender)
| �Ű�����  : sender = ȭ�� ������ ���� ��������Ʈ
| �� �� ��  :
| ��    ��  : ��������Ʈ ����
|------------------------------------------------------------------------------------*/
void GameMissile::resetMissile(Ref *sender)
{
	auto sprMissile = (Sprite*)sender;
	Missiles.eraseObject(sprMissile);
	layerScene->removeChild(sprMissile);
}

/*------------------------------------------------------------------------------------
| �� �� ��  : initMissile(cocos2d::Layer* lay)
| �Ű�����  : lay = ����ȭ�� ���̾
| �� �� ��  :
| ��    ��  : ����ȭ�� ���̾ �� �ʱ�ȭ
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
| �� �� ��  : getSprMissiles()
| �Ű�����  :
| �� �� ��  : Vector<Sprite*> = �̻��� vecor
| ��    ��  : �̻��� vecotr ����
|------------------------------------------------------------------------------------*/
Vector<Sprite*>	GameMissile::getSprMissiles()
{
	return Missiles;
}
