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
| �� �� ��  : setEnemy(float delta)
| �Ű�����  : delta = ��
| �� �� ��  :
| ��    ��  : �����̴� ������� ����
|------------------------------------------------------------------------------------*/
void GameEnemy::setEnemy(float delta)
{
	// x�� ���� ����
	int start_x = PADDING_SCREEN + rand() % ((int)SizeW - PADDING_SCREEN * 2);
	int end_x = PADDING_SCREEN + rand() % ((int)SizeW - PADDING_SCREEN * 2);

	// �� ����� ��������Ʈ �θ���.
	auto sprEnemy = Sprite::create();
	sprEnemy->setPosition(Point(start_x, SizeH));
	layerScene->addChild(sprEnemy);

	// �� ����� ���Ϳ� �ֱ�
	Enemies.pushBack(sprEnemy);

	// �� ����� �ִϸ��̼�
	auto texture = Director::getInstance()->getTextureCache()->addImage("game/Spaceship.png");

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	for (int i = 0; i<4; i++) {
		animation->addSpriteFrameWithTexture(texture, Rect((96*4)+(i % 4 * 96), 106 + i / 4 * 106, 96, 104));
	}

	auto animate = Animate::create(animation);
	//	action->setTag(TAG_MOVE_ACTION);
	sprEnemy->runAction(RepeatForever::create(animate));

	// �Ʒ��� �������� �׼� ����
	auto action = Sequence::create(MoveTo::create(fSpeed, Point(end_x, -(SizeH))),
		CallFuncN::create(CC_CALLBACK_1(GameEnemy::resetEnemy, this)), NULL);
	sprEnemy->runAction(action);

}

/*------------------------------------------------------------------------------------
| �� �� ��  : resetEnemy(Ref *sender)
| �Ű�����  : sender = ���� �� ��������Ʈ
| �� �� ��  :
| ��    ��  : ��������Ʈ ����
|------------------------------------------------------------------------------------*/
void GameEnemy::resetEnemy(Ref *sender)
{
	auto sprEnemy = (Sprite*)sender;
	Enemies.eraseObject(sprEnemy);
	layerScene->removeChild(sprEnemy);

}

/*------------------------------------------------------------------------------------
| �� �� ��  : initEnemy(cocos2d::Layer* lay)
| �Ű�����  : lay = ����ȭ�� ���̾�
| �� �� ��  :
| ��    ��  : ����ȭ�� ���̾�� ������ ������ �ʱ�ȭ
|------------------------------------------------------------------------------------*/
void GameEnemy::initEnemy(cocos2d::Layer* lay)
{
	layerScene = lay;
	fSpeed = 5.0;			// ���ڰ� Ŭ���� õõ�� ������.
	Enemies.clear();
	SizeW = Director::getInstance()->getWinSize().width;
	SizeH = Director::getInstance()->getWinSize().height;
}

/*------------------------------------------------------------------------------------
| �� �� ��  : explosionEnemy(Ref *sender)
| �Ű�����  : sender = �浹�� ��������Ʈ
| �� �� ��  :
| ��    ��  : ����� ����
|------------------------------------------------------------------------------------*/
void  GameEnemy::explosionEnemy(Ref *sender)
{
	auto sprEnemy = (Sprite*)sender;

	auto particle = ParticleSystemQuad::create("game/explosion.plist");
	particle->setPosition(sprEnemy->getPosition());
	particle->setScale(0.5);
	layerScene->addChild(particle);

	auto action = Sequence::create(
		DelayTime::create(1.0),
		CallFuncN::create(CC_CALLBACK_1(GameEnemy::resetBoom, this)),
		NULL);
	particle->runAction(action);
}

/*------------------------------------------------------------------------------------
| �� �� ��  : resetBoom(Ref *sender)
| �Ű�����  : sender = ���� ��������Ʈ
| �� �� ��  :
| ��    ��  : ���� ��������Ʈ �ʱ�ȭ
|------------------------------------------------------------------------------------*/
void GameEnemy::resetBoom(Ref *sender)
{
	auto particle = (ParticleSystemQuad*)sender;

	layerScene->removeChild(particle);
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
| �� �� ��  : getSprEnemies()
| �Ű�����  : 
| �� �� ��  : Vector<Sprite*> = ������� vecor
| ��    ��  : ������� vecotr ����
|------------------------------------------------------------------------------------*/
Vector<Sprite*>	GameEnemy::getSprEnemies()
{
	return Enemies;
}