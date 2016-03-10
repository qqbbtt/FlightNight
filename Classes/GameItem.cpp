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
| �� �� ��  : setItem(float delta)
| �Ű�����  : delta = ��
| �� �� ��  :
| ��    ��  : �����̴� ������ ����
|------------------------------------------------------------------------------------*/
void GameItem::setItem(float delta)
{
	// x�� ���� ����
	int x = PADDING_SCREEN + rand() % ((int)Director::getInstance()->getWinSize().width - PADDING_SCREEN * 2);

	// ������ ��������Ʈ �Ҹ���.
	auto sprItem = Sprite::create("game/item.png");
	sprItem->setPosition(Point(x, Director::getInstance()->getWinSize().height));
	layerScene->addChild(sprItem);

	// ������ ������ ���Ϳ� �ֱ�
	Items.pushBack(sprItem);

	// �Ʒ��� �������� �׼� ����
	auto action = Sequence::create(MoveBy::create(fSpeed, Point(0, -(Director::getInstance()->getWinSize().height))),
		CallFuncN::create(CC_CALLBACK_1(GameItem::resetItem, this)), NULL);
	sprItem->runAction(action);

}

/*------------------------------------------------------------------------------------
| �� �� ��  : resetItem(Ref *sender)
| �Ű�����  : sender = ȭ�� ������ ���� ��������Ʈ
| �� �� ��  :
| ��    ��  : �������� ȭ�� ������ �̵��ϸ� ��������Ʈ ����
|------------------------------------------------------------------------------------*/
void GameItem::resetItem(Ref *sender)
{
	auto sprItem = (Sprite*)sender;
	Items.eraseObject(sprItem);
	layerScene->removeChild(sprItem);

}

/*------------------------------------------------------------------------------------
| �� �� ��  : initItem(cocos2d::Layer* lay)
| �Ű�����  : lay = ����ȭ�� ���̾�
| �� �� ��  :
| ��    ��  : ����ȭ�� ���̾�� ������ ������ �ʱ�ȭ
|------------------------------------------------------------------------------------*/
void GameItem::initItem(cocos2d::Layer* lay)
{
	layerScene = lay;
	fSpeed = 3.0;
	Items.clear();
	isItem = false;
}

void GameItem::updateItem()
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
//		this->scheduleOnce(schedule_selector(GameItem::resetisItem), 5.0);

	}
}

void GameItem::resetisItem(float delta)
{
	isItem = false;
}

bool GameItem::getisItem()
{
	return isItem;
}

