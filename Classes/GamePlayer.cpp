#include "GamePlayer.h"

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
bool GamePlayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	return true;
}


void GamePlayer::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif 

}

/*------------------------------------------------------------------------------------
| �� �� ��  : initPlayer(cocos2d::Layer* lay)
| �Ű�����  : lay = ����ȭ�� ���̾
| �� �� ��  :
| ��    ��  : �÷��̾� ����� �ʱ�ȭ
|------------------------------------------------------------------------------------*/
void GamePlayer::initPlayer(cocos2d::Layer* lay)
{
	// ���̾ ����
	layerScene = lay;

	// �÷��̾� ����� ����
	auto spr = Sprite::create();
	spr->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	spr->setTag(TAG_SPRITE_PLAYER);
	layerScene->addChild(spr, 1);

	auto texture = Director::getInstance()->getTextureCache()->addImage("game/Spaceship.png");

	// �ִϸ��̼� ����
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	for (int i = 0; i<4; i++) {
		animation->addSpriteFrameWithTexture(texture, Rect(i % 4 * 96, 106 + i / 4 * 106, 96, 104));
	}

	auto animate = Animate::create(animation);
//	action->setTag(TAG_MOVE_ACTION);
	spr->runAction(RepeatForever::create(animate));

	// ����� ��ġ �� �̵� �̺�Ʈ
	listener = EventListenerTouchOneByOne::create();
	listener->setEnabled(true);
	listener->onTouchBegan = CC_CALLBACK_2(GamePlayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GamePlayer::onTouchMoved, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
}

/*------------------------------------------------------------------------------------
| �� �� ��  : onTouchBegan(Touch *touch, Event *unused_event)
| �Ű�����  : touch = ��ġ����, unused_event = �̺�Ʈ ����
| �� �� ��  : bool = ����, ����.
| ��    ��  : �÷��̾� ����� ��ġ
|------------------------------------------------------------------------------------*/
bool GamePlayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto sprPlayer = (Sprite*)layerScene->getChildByTag(TAG_SPRITE_PLAYER);

	// ��������Ʈ�� ���ٸ� ����
	if (!sprPlayer) 
		return true;

	if (sprPlayer->getActionByTag(TAG_MOVE_ACTION)) 
		sprPlayer->stopActionByTag(TAG_MOVE_ACTION);
	
	// ó�� ��ġ�� ����Ʈ
	posStartTouch = touch->getLocation();			// �����̴� ��ġ �� �� �� �Է�
	posStartPlayer = sprPlayer->getPosition();
	Point posTouch = touch->getLocation();
	Point posPlayer = sprPlayer->getPosition();


	float distance = sqrtf((posTouch.x - posPlayer.x)*(posTouch.x - posPlayer.x) 
		+ (posTouch.y - posPlayer.y)*(posTouch.y - posPlayer.y));
	
	
	auto action = MoveTo::create(distance / 500.0, posTouch);
	action->setTag(TAG_MOVE_ACTION);
	sprPlayer->runAction(action);

	return true;
}

/*------------------------------------------------------------------------------------
| �� �� ��  : onTouchMoved(Touch *touch, Event *unused_event)
| �Ű�����  : touch = ��ġ����, unused_event = �̺�Ʈ ����
| �� �� ��  : 
| ��    ��  : �÷��̾� ����� ��ġ �ϸ鼭 �̵�.
|------------------------------------------------------------------------------------*/
void GamePlayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	Point location = touch->getLocation();
	Point posChange = location - posStartTouch;
	Point pos = posStartPlayer + posChange;

	if (pos.x < 0)
		pos.x = 0;
	if (pos.x > Director::getInstance()->getWinSize().width)
		pos.x = Director::getInstance()->getWinSize().width;

	if (pos.y < 0)
		pos.y = 0;
	if (pos.y > Director::getInstance()->getWinSize().height)
		pos.y = Director::getInstance()->getWinSize().height;


	// �̵��ϴ� ��ο� �°� ����� ȭ�鿡 �Ѹ���.
	auto sprPlayer = (Sprite*)layerScene->getChildByTag(TAG_SPRITE_PLAYER);
	sprPlayer->setPosition(pos);

}

/*------------------------------------------------------------------------------------
| �� �� ��  : ChangeScene()
| �Ű�����  : 
| �� �� ��  :
| ��    ��  : ȭ�� ��ȯ �� ��� �̺�Ʈ �Է� �ߴ�
|------------------------------------------------------------------------------------*/
void GamePlayer::ChangeScene()
{
	listener->setEnabled(false);
}