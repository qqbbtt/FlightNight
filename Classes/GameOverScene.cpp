#include "GameOverScene.h"


USING_NS_CC;

Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	// ��ġ �ʱ�ȭ
	isTouch = false;


	// ���� ���� ����
	auto label = Label::createWithSystemFont("GAME OVER", "Thonburi", 50);		
	label->setPosition(Point(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height/2));
	this->addChild(label);


	// �̺�Ʈ ����
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameOverScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameOverScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	listener->setEnabled(true);
   
    
    return true;
}


void GameOverScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif 

}

/*------------------------------------------------------------------------------------
| �� �� ��  : onTouchEnded(Touch *touch, Event *unused_event)
| �Ű�����  : touch = ��ġ����, unused_event = �̺�Ʈ ����
| �� �� ��  :
| ��    ��  : ��ġ���� ���� ���� ȭ�� ��ȯ
|------------------------------------------------------------------------------------*/
void GameOverScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (isTouch)
	{
		listener->setEnabled(false);
	//	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
		auto scene = TransitionFadeTR::create(1.0, MenuScene::createScene());
		Director::getInstance()->replaceScene(scene);
	}

}

/*------------------------------------------------------------------------------------
| �� �� ��  : onTouchBegan(Touch *touch, Event *unused_event)
| �Ű�����  : touch = ��ġ����, unused_event = �̺�Ʈ ����
| �� �� ��  :
| ��    ��  : ��ġ ����
|------------------------------------------------------------------------------------*/
bool GameOverScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (!isTouch)
	{
		isTouch = true;
	}
		
	return true;
}

