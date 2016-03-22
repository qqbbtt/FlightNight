#include "MenuScene.h"


USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	initBackGround();
	initMenu();
    
    return true;
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif 

}

/*------------------------------------------------------------------------------------
| �� �� ��  : initBackGround(void)
| �Ű�����  :
| �� �� ��  :
| ��    ��  : �޴� ���ȭ�� �ʱ�ȭ
|------------------------------------------------------------------------------------*/
void MenuScene::initBackGround()
{
	auto spr = Sprite::create("menu/menu.jpg");
	spr->setAnchorPoint(Point::ZERO);
	spr->setPosition(Point::ZERO);
	spr->setScaleX(Director::getInstance()->getWinSize().width / 640);
	spr->setScaleY(Director::getInstance()->getWinSize().height / 400);
//	spr->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(spr);

}


/*------------------------------------------------------------------------------------
| �� �� ��  : initMenu(void)
| �Ű�����  :
| �� �� ��  :
| ��    ��  : �޴� �ʱ�ȭ
|------------------------------------------------------------------------------------*/
void MenuScene::initMenu()
{
	// �޴� ������ ���� 
	auto menu_0 = MenuItemImage::create("menu/play-0.png", "menu/play-1.png", CC_CALLBACK_1(MenuScene::menuCallback, this));
	auto menu_1 = MenuItemImage::create("menu/help-0.png", "menu/help-1.png", CC_CALLBACK_1(MenuScene::menuCallback, this));
	auto menu_2 = MenuItemImage::create("menu/option-0.png", "menu/option-1.png", CC_CALLBACK_1(MenuScene::menuCallback, this));
	auto menu_3 = MenuItemImage::create("menu/quit-0.png", "menu/quit-1.png", CC_CALLBACK_1(MenuScene::menuCallback, this));

	// �޴��� ������ ID �Է�
	menu_0->setTag(ID_MENU::PLAY);
	menu_1->setTag(ID_MENU::HELP);
	menu_2->setTag(ID_MENU::OPTION);
	menu_3->setTag(ID_MENU::QUIT);

	// �޴� ����
	auto menu = Menu::create(menu_0, menu_1, menu_2, menu_3, NULL);

	// ȭ�� ����� 20�ȼ� �������� ��ġ
	menu->alignItemsVerticallyWithPadding(20);

	// ȭ�鿡 �Ѹ���
	this->addChild(menu);
}


/*------------------------------------------------------------------------------------
| �� �� ��  : menuCallback(Ref *sender)
| �Ű�����  : sender = �޴� ��ġ �� �Ѿ���� ��.
| �� �� ��  :
| ��    ��  : �޴� ��ġ �� ȭ�� ��ȯ.
|------------------------------------------------------------------------------------*/
void MenuScene::menuCallback(Ref *sender)
{
	auto menu = (MenuItem*)sender;

	switch (menu->getTag())
	{
		// ���� �÷���
		case ID_MENU::PLAY:
		{
			Director::getInstance()->pushScene(GameScene::createScene());
			break;
		}

		// ����
		case ID_MENU::HELP:
			break;

		// �ɼ�
		case ID_MENU::OPTION:
			break;

		// ����
		case ID_MENU::QUIT:
		{
			 Director::getInstance()->end();

			#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
							  exit(0);
			#endif 

			break;
		}

		default:
			break;
	}
}