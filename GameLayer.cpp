#include "GameLayer.h"
#include "Comres.h"
#include "VisibleRect.h"


GameLayer::GameLayer()
{
	_leveString = NULL;
	_iplifeString = NULL;
	_enemyString = NULL;
}


GameLayer::~GameLayer()
{
	CC_SAFE_RELEASE(this);
}

cocos2d::Scene* GameLayer::createScene()
{
	auto theScene = cocos2d::Scene::create();
	auto theLayer = GameLayer::create();
	CC_SAFE_RETAIN(theLayer);
	theScene->addChild(theLayer);
	return theScene;
}

bool GameLayer::init()
{
	do 
	{
		CC_BREAK_IF(!cocos2d::Layer::init());
		_gameLevel = 1;
		_tankLifeCount = 4;
		_enemyTankCount = 10;
		initCreate();
		return true;
	} while (0);
	return false;
}

void GameLayer::initCreate()
{

	CreateOtherItem();
	CreateMapLayer();
	CreateHRockerLayer();
	CreateFireButton();
	this->scheduleUpdate();
}

void GameLayer::loadMap()
{
	Size wSize = VisibleRect::getVisibleRect().size;

	TMXTiledMap *gameMap = TMXTiledMap::create("map2.tmx");

	//Ëõ·Å±ÈÁÐ  
	float scale = wSize.height / (gameMap->getContentSize().height);
	gameMap->setScale(scale);
	gameMap->setPosition(wSize.width / 6.0, 0);

	this->addChild(gameMap);
}

void GameLayer::CreateMapLayer()
{
	auto backColor = LayerColor::create(ccc4(192, 192, 192, 225));
	this->addChild(backColor);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images.plist");

	auto ipLife = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("IP.png"));
	ipLife->setPosition(Vec2(30 * 2, VisibleRect::getVisibleRect().size.height - 90));
	ipLife->setScale(1.5f);
	this->addChild(ipLife);

	auto ipLifeIcok = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("p1.png"));
	ipLifeIcok->setPosition(Vec2(40, VisibleRect::getVisibleRect().size.height - 70 * 2));
	ipLifeIcok->setScale(1.0f);
	this->addChild(ipLifeIcok);
	this->showLife();

	auto flag = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("flag.png"));
	flag->setPosition(Vec2(VisibleRect::getVisibleRect().size.width - 150, VisibleRect::getVisibleRect().size.height - 200 * 2) + Vec2(0, 200));
	flag->setScale(2.0f);
	this->addChild(flag);

	this->showLeve();
	_mapLayer = MapLayer::create();
	_mapLayer->initWithMap(_gameLevel, kBorn, _tankLifeCount);
	_mapLayer->setPosition(Vec2(VisibleRect::getVisibleRect().size.width / 6.0, 0));
	this->addChild(_mapLayer, 0);




}

void GameLayer::showLife()
{
	if (_iplifeString)
	{
		_iplifeString->removeFromParentAndCleanup(true);

	}
	_iplifeString = cocos2d::LabelTTF::create(__String::createWithFormat("%d", _tankLifeCount)->getCString(), "Courier-Bold", 40);

	_iplifeString->setColor(ccc3(0, 0, 0));
	_iplifeString->setPosition(45 * 2, VisibleRect::getVisibleRect().size.height - 70 * 2);
	this->addChild(_iplifeString, 1);
}

void GameLayer::showLeve()
{
	if (_leveString)
	{
		_leveString->removeAllChildrenWithCleanup(true);
	}

	_leveString = cocos2d::LabelTTF::create(__String::createWithFormat("%d", _gameLevel)->getCString(), "Courier-Bold", 40);
	_leveString->setColor(ccc3(0, 0, 0));
	_leveString->setPosition(Vec2(VisibleRect::getVisibleRect().size.width - 150, VisibleRect::getVisibleRect().size.height - 230 * 2)+Vec2(0,200));
	this->addChild(_leveString, 1);
}

void GameLayer::preLoadMusic()
{
	auto* audioEngin = CocosDenshion::SimpleAudioEngine::getInstance();
	audioEngin->preloadBackgroundMusic("start.aif");
	audioEngin->preloadEffect("start.aif");
}


void GameLayer::CreateHRockerLayer()
{
	auto controlSprite = Sprite::create("cen.png");
	auto controlbgSprite = Sprite::create("control_bg.png");
	controlbgSprite->setOpacity(100);
	controlSprite->setOpacity(100);
	_HRockerLayer = HRockerLayer::HRockerWithCenter(Vec2(100.0f, 250.0f), 70.0f, controlSprite, controlbgSprite, false);
	this->addChild(_HRockerLayer);
}

void GameLayer::CreateFireButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto fireButton = MenuItemImage::create(
		"fire_button_default.png",
		"fire_button_press.png",
		CC_CALLBACK_1(GameLayer::menuCallback_PlayerFire, this));

	fireButton->setPosition(Vec2(origin.x + visibleSize.width - fireButton->getContentSize().width / 2,
		origin.y + fireButton->getContentSize().height / 2) + Vec2(-100, 200));

	auto menu = Menu::create(fireButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

void GameLayer::menuCallback_PlayerFire(cocos2d::Ref* pSender)
{
	_mapLayer->_tankSprite->command(cmdFire);
}

void GameLayer::update(float delta)
{
	_HRockerLayer->update(delta);
	_mapLayer->update(delta,_HRockerLayer->getRetation());
	showEnemyCount();
}

void GameLayer::NextLevel()
{
	_gameLevel+=1;
	if (_gameLevel>MaxLevel)
	{
		GameOver();
	}
	else
	{
		ClearPreLevel();
		_enemyTankCount = _gameLevel;
		initCreate();
		showLeve();
		showLife();
		showEnemyCount();
		this->scheduleUpdate();	
	}
}

void GameLayer::GameOver()
{

}

void GameLayer::menuCallback_NextLevel(cocos2d::Ref* pSender)
{
	NextLevel();
}

void GameLayer::CreateOtherItem()
{
	auto menuItem01 = cocos2d::MenuItemFont::create("Next", this, menu_selector(GameLayer::menuCallback_NextLevel));
	//menuItem01->setPosition(VisibleRect::center()+Vec2(0,-150));
	menuItem01->setPosition(Vec2(0,0));
	menuItem01->setFontSize(32);
	menuItem01->setFontNameObj("Marker Felt");

	auto menuItem02 = cocos2d::MenuItemFont::create("P/C", this, menu_selector(GameLayer::menuCallback_Pause));
	menuItem02->setPosition(Vec2(100,0));
	//menuItem02->setPosition(Vec2(0, 0));
	menuItem02->setFontSize(32);
	menuItem02->setFontNameObj("Marker Felt");

	auto menu = cocos2d::Menu::create(menuItem01,menuItem02, NULL);
	menu->setPosition(VisibleRect::leftTop() + Vec2(menuItem01->getContentSize().width, -menuItem01->getContentSize().height));
	this->addChild(menu);
}

void GameLayer::showEnemyCount()
{
	if (_enemyString)
	{
		_enemyString->removeAllChildrenWithCleanup(true);
	}

	_enemyString = cocos2d::LabelTTF::create(__String::createWithFormat("Enemy:%d", _enemyTankCount)->getCString(), "Courier-Bold", 40);
	_enemyString->setColor(ccc3(0, 0, 0));
	_enemyString->setPosition(Vec2(VisibleRect::getVisibleRect().size.width - 150, VisibleRect::getVisibleRect().size.height - 230 * 2) + Vec2(0, 400));
	this->addChild(_enemyString);
}

void GameLayer::ClearPreLevel()
{
	this->removeAllChildren();
	this->_leveString = NULL;
	this->_enemyString = NULL;
	this->_iplifeString = NULL;
	this->unscheduleUpdate();
}

void GameLayer::menuCallback_Pause(cocos2d::Ref* pSender)
{
	GamePause();
}

void GameLayer::GamePause()
{
	static bool ispause = false;
	if (ispause)
	{
		ispause = false;
		Director::getInstance()->startAnimation();
	}
	else
	{
		ispause = true;
		Director::getInstance()->stopAnimation();
	}
	
}


