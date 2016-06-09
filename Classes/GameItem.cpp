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

	Sprite* sprItem;
	
	// ������ ��������Ʈ ����
	if (rand() % 2 == 1)
	{
		sprItem = Sprite::create("game/buffitem.png");
		sprItem->setPosition(Point(x, Director::getInstance()->getWinSize().height));
		sprItem->setScale(1.5f);
		layerScene->addChild(sprItem);

		// ������ ������ ���Ϳ� �ֱ�
		BufItems.pushBack(sprItem);
	}

	else
	{
		sprItem = Sprite::create("game/debuffitem.png");
		sprItem->setPosition(Point(x, Director::getInstance()->getWinSize().height));
		sprItem->setScale(0.08f);
		layerScene->addChild(sprItem);

		// ������ ������ ���Ϳ� �ֱ�
		DebufItems.pushBack(sprItem);
	}


	// �Ʒ��� �������� �׼� ����
	auto action = Sequence::create(MoveBy::create(fSpeed, Point(0, -(Director::getInstance()->getWinSize().height))),
		CallFuncN::create(CC_CALLBACK_1(GameItem::resetItem, this)), NULL);
	sprItem->runAction(action);

}

/*------------------------------------------------------------------------------------
| �� �� ��  : resetItem(Ref *sender)
| �Ű�����  : sender = ȭ�� ������ ���� ��������Ʈ
| �� �� ��  :
| ��    ��  : ��������Ʈ ����
|------------------------------------------------------------------------------------*/
void GameItem::resetItem(Ref *sender)
{
	auto sprItem = (Sprite*)sender;

	if (BufItems.contains(sprItem))
	{
		BufItems.eraseObject(sprItem);
	}
	else
	{
		DebufItems.eraseObject(sprItem);
	}
		
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
	BufItems.clear();
	DebufItems.clear();
	Type = 0;
}

/*------------------------------------------------------------------------------------
| �� �� ��  : updatBbufItem(Ref *sender)
| �Ű�����  : sender = �浹 �� ������ ��������Ʈ
| �� �� ��  :
| ��    ��  : �浹 �� ���� ������ �ʱ�ȭ 
|------------------------------------------------------------------------------------*/
void GameItem::updateBufItem(Ref *sender)
{
	auto sprItem = (Sprite*)sender;

	if (BufItems.contains(sprItem))
	{
		resetItem(sprItem);
		Type = 1;
	}
}

/*------------------------------------------------------------------------------------
| �� �� ��  : updateDebufItem(Ref *sender)
| �Ű�����  : sender = �浹 �� ������ ��������Ʈ
| �� �� ��  :
| ��    ��  : �浹 �� ����� ������ �ʱ�ȭ
|------------------------------------------------------------------------------------*/
void GameItem::updateDebufItem(Ref *sender)
{
	auto sprItem = (Sprite*)sender;

	if (DebufItems.contains(sprItem))
	{
		resetItem(sprItem);
		Type = 2;
	}
}

/*------------------------------------------------------------------------------------
| �� �� ��  : getBufSprItems()
| �Ű�����  :
| �� �� ��  : Vector<Sprite*> = ������ vecor
| ��    ��  : ���� ������ vecotr ����
|------------------------------------------------------------------------------------*/
Vector<Sprite*>	GameItem::getBufSprItems()
{
	return BufItems;
}

/*------------------------------------------------------------------------------------
| �� �� ��  : getDebufSprItems()
| �Ű�����  :
| �� �� ��  : Vector<Sprite*> = ������ vecor
| ��    ��  : ������� vecotr ����
|------------------------------------------------------------------------------------*/
Vector<Sprite*>	GameItem::getDebufSprItems()
{
	return DebufItems;
}

/*------------------------------------------------------------------------------------
| �� �� ��  : setType(int ty)
| �Ű�����  : ty = ������ ����
| �� �� ��  : 
| ��    ��  : ������ ���� ����
|------------------------------------------------------------------------------------*/
void GameItem::setType(int ty)
{
	Type = ty;
}

/*------------------------------------------------------------------------------------
| �� �� ��  : getType()
| �Ű�����  : 
| �� �� ��  : int = ������ ���� ( 0 = ������ �̽���, 1 = ���� ������, 2 = ����� ������ )
| ��    ��  : ������ ���� ����
|------------------------------------------------------------------------------------*/
int GameItem::getType()
{
	return Type;
}