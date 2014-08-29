#include "WelcomeLayer.h"
#include "Comres.h"
#include "VisibleRect.h"
#include "GameLayer.h"


WelcomeLayer::WelcomeLayer()
{
}


WelcomeLayer::~WelcomeLayer()
{
}


cocos2d::Scene* WelcomeLayer::createScene()
{
	auto thescene = cocos2d::Scene::create();
	auto thelayer = WelcomeLayer::create();
	thescene->addChild(thelayer);
	return thescene;
}

bool WelcomeLayer::init()
{
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());
		init_Create();
		return true;
	} while (0);
	return false;
}

void WelcomeLayer::init_Create()
{
	auto logoSprite = cocos2d::Sprite::create(logo_FileName);
	logoSprite->setPosition(VisibleRect::center()+Vec2(0,100));
	this->addChild(logoSprite);
	//////////////////////////////////////////////////////////////////////////
	auto menuItem01 = cocos2d::MenuItemFont::create("Start Game", this, menu_selector(WelcomeLayer::startGame));
	menuItem01->setPosition(VisibleRect::center() + Vec2(0, -50));
	menuItem01->setFontSize(55);
	//menuItem01->setFontNameObj("Georgia-Bold");
	
	menuItem01->setFontNameObj("Marker Felt");

	auto menu = cocos2d::Menu::create(menuItem01, NULL);
	menu->setPosition(Vec2(0, 0));
	this->addChild(menu);
	

	
}

void WelcomeLayer::startGame(Ref* pNode)
{
	auto theScene = GameLayer::createScene();
	//Director::getInstance()->replaceScene(theScene);

	//
	//CCTransitionMoveInR::transitionWithDuration(t, s);//新场景从右移入覆盖  
	//Director::getInstance()->replaceScene(TransitionMoveInR::create(5.0f, theScene));

	//CCTransitionFade::transitionWithDuration(t, s)
	Director::getInstance()->replaceScene(TransitionFade::create(1.5f, theScene));

}
