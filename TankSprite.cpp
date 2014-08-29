#include "TankSprite.h"
#include "SimpleAudioEngine.h"
#include "MapLayer.h"
#include "CommonValue.h"

USING_NS_CC;
using namespace CocosDenshion;



TankSprite::TankSprite()
{

}
TankSprite::~TankSprite()
{

}
TankSprite* TankSprite::initWithDelegate(int numLife, int tKind, Size mSize,MapLayer* maplayer)
{
	initActionSet();
	TankSprite* tank;
	switch (tKind)
	{
	case kBorn:
		//tank = (TankSprite*)Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName("p1.png"));
		tank = (TankSprite*)Sprite::createWithSpriteFrameName("p1.png");
		tank->_isEnemy = false;
		tank->_speed = 1;
		break;
	case kPlusStarOne:
		tank = (TankSprite*)Sprite::createWithSpriteFrameName("en1.png");
		tank->_isEnemy = true;
		tank->_speed = 1;
		break;
	case kPlusStarTwo:
		tank = (TankSprite*)Sprite::createWithSpriteFrameName("en2.png");
		tank->_isEnemy = true;
		tank->_speed = 1;
		break;
	case kPlusStarThree:
		tank = (TankSprite*)Sprite::createWithSpriteFrameName("en6.png");
		tank->_isEnemy = true;
		tank->_speed = 1;
		break;
	default:
		break;
	}

	tank->_life = numLife;
	tank->_mapSize = mSize;
	tank->_kind = (TankKind)tKind;
	tank->setScale(0.7f);
	//默认向上  
	tank->_kaction = kUp;
	tank->_mapLayer = maplayer;
	tank->_mapLayer->_gameMap = maplayer->_gameMap;
	tank->_bullet = BulletSprite::createBulletWithTank(tank);
	return tank;
}

void TankSprite::bindSprite(Sprite* sprite)
{
	_sprite = sprite;
	_sprite->setAnchorPoint(Vec2(0,0));
	this->addChild(_sprite);
}



Sprite* TankSprite::getSprite()
{
	return _sprite;
}

void TankSprite::moveUp()                                                                                               
{
	//log("MOVE UP");
	//设置旋转方向  
	//this->setRotation(0);

	_kaction = kUp;
	CCPoint tp = this->getPosition();
	CCPoint tnp = ccp(tp.x, tp.y + this->boundingBox().size.height / 2 + _speed);
	//边界检测---顶部  
	if ((tp.y + this->boundingBox().size.height / 2 + _speed) > _mapSize.height)
	{
		_IsBlock = true;
		return;
	}

	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}


	tnp = ccp(tp.x - this->boundingBox().size.width / 2, tp.y + this->boundingBox().size.height / 2 + _speed);
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}

	tnp = ccp(tp.x - this->boundingBox().size.width / 3, tp.y + this->boundingBox().size.height / 2 + _speed);
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}

	tnp = ccp(tp.x + this->boundingBox().size.width / 2, tp.y + this->boundingBox().size.height / 2 + _speed);
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}

	tnp = ccp(tp.x + this->boundingBox().size.width / 3, tp.y + this->boundingBox().size.height / 2 + _speed);
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}
	//IsBlock = false;
	this->setPosition(ccp(this->getPosition().x, this->getPosition().y + _speed));

}

void TankSprite::moveDown()
{
	
	//log("MOVE DOWN");
	//this->setRotation(180);
	_kaction = kDown;
	CCPoint tp = this->getPosition();
	CCPoint tnp = ccp(tp.x, tp.y - this->boundingBox().size.height / 2 - _speed);
	//  
	if ((tp.y - this->boundingBox().size.height / 2 - _speed) < 0)
	{
		_IsBlock = true;
		return;
	}
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}
	tnp = ccp(tp.x - this->boundingBox().size.width / 2, tp.y - this->boundingBox().size.height / 2 - _speed);
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}
	tnp = ccp(tp.x - this->boundingBox().size.width / 3, tp.y - this->boundingBox().size.height / 2 - _speed);
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}
	tnp = ccp(tp.x + this->boundingBox().size.width / 2, tp.y - this->boundingBox().size.height / 2 - _speed);
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}
	tnp = ccp(tp.x + this->boundingBox().size.width / 3, tp.y - this->boundingBox().size.height / 2 - _speed);
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}
	//IsBlock = false;
	this->setPosition(ccp(this->getPosition().x, this->getPosition().y - _speed));


}

void TankSprite::moveLeft()
{
	//log("MOVE LEFT");
	//this->setRotation(-90);
	_kaction = kLeft;
	CCPoint tp = this->getPosition();
	CCPoint tnp = ccp(tp.x - this->boundingBox().size.width / 2 - _speed, tp.y);
	//  
	if (tp.x - this->boundingBox().size.width / 2 - _speed < 0)
	{
		_IsBlock = true;
		return;
	}
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}
	tnp = ccp(tp.x - this->boundingBox().size.width / 2 - _speed, tp.y + this->boundingBox().size.height / 2 - 2);
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}
	tnp = ccp(tp.x - this->boundingBox().size.width / 2 - _speed, tp.y + this->boundingBox().size.height / 3);
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}
	tnp = ccp(tp.x - this->boundingBox().size.width / 2 - _speed, tp.y - this->boundingBox().size.height / 2 + 2);
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}
	tnp = ccp(tp.x - this->boundingBox().size.width / 2 - _speed, tp.y - this->boundingBox().size.height / 3);
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}

	//IsBlock = false;
	this->setPosition(ccp(this->getPosition().x - _speed, this->getPosition().y));


}

void TankSprite::moveRight()
{
	//log("MOVE RIGHT");
	//this->setRotation(90);
	_kaction = kRight;
	CCPoint tp = this->getPosition();
	CCPoint tnp = ccp(tp.x + this->boundingBox().size.width / 2 + _speed, tp.y);	
	//  
	if (tp.x + this->boundingBox().size.width / 2 + _speed > _mapSize.width)
	{
		_IsBlock = true;
		return;
	}
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}
	tnp = ccp(tp.x - this->boundingBox().size.width / 2 + _speed, tp.y + this->boundingBox().size.height / 2 - 2);
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}
	tnp = ccp(tp.x - this->boundingBox().size.width / 2 + _speed, tp.y + this->boundingBox().size.height / 3);
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}
	tnp = ccp(tp.x - this->boundingBox().size.width / 2 + _speed, tp.y - this->boundingBox().size.height / 2 + 2);
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}
	tnp = ccp(tp.x - this->boundingBox().size.width / 2 + _speed, tp.y - this->boundingBox().size.height / 3);
	if (this->checkPoint(tnp))
	{
		_IsBlock = true;
		return;
	}
	//IsBlock = false;
	this->setPosition(ccp(this->getPosition().x + _speed, this->getPosition().y));


}

bool TankSprite::checkPoint(Vec2 pon)
{
	CCPoint tnp = pon;
	unsigned int tid;
	tid = _mapLayer->tileDFromPosition(tnp);
	//log("TID=%d", tid);
	//if (tid != 0 && tid != 9 && tid != 10 && tid != 37 && tid != 38) return true;
	int gid = gidToTileType[tid];
	if (gid==tileNone||gid==tileGrass||gid==tileRiver||gid==tileRiver2)
	{
		return false;
	}
	else
	{
		return true;
	}

	return false;

}

void TankSprite::onFire()
{
	if (_life == 0) {

		return;
	}


	//当tank只能发射一颗子弹的时候  
	if (_kind == kBorn || _kind == kPlusStarOne) {

		//能否继续开火  
		if (_isCanFire == false) {

			return;
		}
		//子弹方向即坦克方向  
		_buttleOrientation = _kaction;

		CCSprite *buttle = CCSprite::createWithSpriteFrameName("bullet.png");

		_gameMap->addChild(buttle, -1);

		//隐藏  
		buttle->setVisible(false);

		_isCanFire = false;

		this->fire(buttle, (TankAction)_buttleOrientation);


	}

}

void TankSprite::fire(Sprite* buttle, TankAction buttleOrientation)
{
	//发射子弹的声音  
	SimpleAudioEngine::sharedEngine()->playEffect("bullet.aif");

	CCPoint ptn;

	switch (buttleOrientation) {
	case kUp:

		CCLOG("%f", this->getPosition().x);

		buttle->setRotation(0);

		buttle->setPosition(ccp(this->getPosition().x, this->getPosition().y + this->boundingBox().size.height / 2));

		//终点  
		ptn = ccp(this->getPosition().x, this->getPosition().y + _mapSize.width);

		break;
	case kDown:

		buttle->setRotation(180);

		buttle->setPosition(ccp(this->getPosition().x, this->getPosition().y - this->boundingBox().size.height / 2));


		ptn = ccp(this->getPosition().x, this->getPosition().y - _mapSize.width);

		break;
	case kRight:

		buttle->setRotation(90);

		buttle->setPosition(ccp(this->getPosition().x + this->boundingBox().size.width / 2, this->getPosition().y));


		ptn = ccp(this->getPosition().x + _mapSize.width, this->getPosition().y);

		break;
	case kLeft:

		buttle->setRotation(-90);

		buttle->setPosition(ccp(this->getPosition().x - this->boundingBox().size.width / 2, this->getPosition().y));

		{
			float f = this->getPosition().x - _mapSize.width;
			float f2 = _mapLayer->getPosition().x;
			int i = 0;
		}

		ptn = ccp(this->getPosition().x - _mapSize.width, this->getPosition().y);
		//ptn = ccp(this->getPosition().x - _mapSize.width, this->getPosition().y);
		

		

		break;


	default:
		break;
	}


	const CCPoint realyPosition = ptn;

	//创建子弹移动动画  
	CCShow *ac1 = CCShow::create();
	CCMoveTo *ac2 = CCMoveTo::create(2.0, realyPosition);

	CCFiniteTimeAction *seq = CCSequence::create(ac1, ac2, CCCallFunc::create(this, callfunc_selector(TankSprite::makeCanFire)), NULL);

	buttle->runAction(seq);


}

void TankSprite::makeCanFire()
{
	_isCanFire = true;
}

TankAction TankSprite::getTankDirection()
{
	return _kaction;
}

bool TankSprite::command(enumOrder order)
{
	switch (order)
	{
	case cmdNothing:
		break;
	case cmdGoUP:
		setRotation(0.0f);
		moveUp();
		break;
	case cmdGoDown:
		setRotation(180.0f);
		moveDown();
		break;
	case cmdGoLeft:
		setRotation(-90.0f);
		moveLeft();
		break;
	case cmdGoRight:
		setRotation(90.0f);
		moveRight();
		break;
	case cmdFire:
		//调用子弹开火
		//onFire();
		_bullet->fire();
	default:
		break;
	}
	return true;
}

void TankSprite::move()
{
	if (!_IsBlock)
	{
		setPosition(ccp(mMovedRect.getMidX(), mMovedRect.getMidY()));
	}
}

void TankSprite::autoChangeDirection()
{
	if (_IsBlock)
	{
		//float f1 = (int)(CCRANDOM_0_1() * 3.2) * 90;
		float f = nextRotation(getRotation());
		//log("after ROtation=%f", f);
		setRotation(f);
		_IsBlock = false;
		//log("Rotation=%f",f);
	}

}

void TankSprite::update(float delta, enumOrder order)
{
	this->command(order);
}

int TankSprite::nextRotation(int rotation)
{
	//up=0 down=180 left=-90 right=90
	int nrand;
	int nnow;
	int nextrotation;
	switch (rotation)
	{
	case 0:
		nnow = 0;
		break;
	case 180:
		nnow = 1;
		break;
	case -90:
		nnow = 2;
		break;
	case 90:
		nnow = 3;
		break;
	default:
		break;
	}
	nrand = nnow;
	do 
	{
		//nrand += 1;
		//nrand = nrand % 4;
		nrand = (int)(CCRANDOM_0_1() * 10) % 4;//
		if (nrand==nnow)
		{
			continue;
		}
		else
		{
			break;
		}

	} while (1);
	switch (nrand)
	{
	case 0:
		nextrotation = 0;
		break;
	case 1:
		nextrotation = 180;
		break;
	case 2:
		nextrotation = -90;
		break;
	case 3:
		nextrotation = 90;
		break;
	default:
		break;
	}
	return nextrotation;
}

enumOrder TankSprite::rotationToEnumOrder(int rotation)
{

	switch (rotation)
	{
	case 0:
		return cmdGoUP;
		break;
	case 180:
		return cmdGoDown;
		break;
	case -90:
		return cmdGoLeft;
		break;
	case 90:
		return cmdGoRight;
		break;
	default:
		break;
	}
}

void TankSprite::test()
{

}

void TankSprite::setBlock(bool bvaule)
{
	_IsBlock = bvaule;
}

bool TankSprite::getBlock()
{
	return _IsBlock;
}

void TankSprite::tankBoom()
{
	if (_isEnemy)
	{
		auto animation = AnimationCache::getInstance()->animationByName("enemyboom");
		auto action = Animate::create(animation);
		auto repeatdone = CCCallFuncN::create(this, callfuncN_selector(TankSprite::boomDone));
		auto sequence = CCSequence::create(action, repeatdone, NULL);
		this->runAction(sequence);
	}
	else
	{
		auto animation = AnimationCache::getInstance()->animationByName("tankboom");
		auto action = Animate::create(animation);
		auto repeatdone = CCCallFuncN::create(this, callfuncN_selector(TankSprite::boomDone));
		auto sequence = CCSequence::create(action, repeatdone, NULL);
		this->runAction(sequence);
	}

}

void TankSprite::initActionSet()
{
	auto frameCache = SpriteFrameCache::getInstance();
	SpriteFrame* frame = NULL;
	//3.0中改用vector 而不是用Array
	Vector<SpriteFrame*>frameVector;

	/* 1.----------------加载跑动的Animation-----------------*/
	for (int i = 1; i <= 2; i++) {
		//从缓存池中加载精灵到Vector
		frame = frameCache->spriteFrameByName(String::createWithFormat("explode%d.png", i)->getCString());
		frameVector.pushBack(frame);
	}
	//CCAnimate* animate = CCAnimate::create(animation);
	//CCRepeat* repeat = CCRepeat::create(animate, 2);
	//CCCallFuncN* repeatdone = CCCallFuncN::create(this, callfuncN_selector(WelcomeLayer::loadingDone));
	//CCSequence* sequence = CCSequence::create(repeat, repeatdone, NULL);

	//用vector里面的SpriteFrame列表创建Animation  以及设置一些参数
	auto run_animation = Animation::createWithSpriteFrames(frameVector, 0.1f, 2);
	auto animate = CCAnimate::create(run_animation);
	//将跑动的 Animation 取名为 running 
	AnimationCache::getInstance()->addAnimation(run_animation, "tankboom");

	/*4---------------*/
	frameVector.clear();
	for (int i = 1; i <= 3; i++){
		frame = frameCache->spriteFrameByName(String::createWithFormat("explode-%d.png", i)->getCString());
		frameVector.pushBack(frame);
	}
	auto jumpUp_animation = Animation::createWithSpriteFrames(frameVector, 0.2);//不设置无限循环
	AnimationCache::getInstance()->addAnimation(jumpUp_animation, "enemyboom");

	//CCAnimate* animate = CCAnimate::create(animation);
	//CCRepeat* repeat = CCRepeat::create(animate, 2);
	//CCCallFuncN* repeatdone = CCCallFuncN::create(this, callfuncN_selector(WelcomeLayer::loadingDone));
	//CCSequence* sequence = CCSequence::create(repeat, repeatdone, NULL);

}

void TankSprite::boomDone(Node* pNode)
{
	//this->getParent()->removeChild(this);
	//this->_mapLayer->_enemyAi->_mTank = NULL;
	this->setVisible(false);
}

//void TankSprite::setBulletDelta(float delta)
//{
//	_mBulletDelta = delta;
//}
//
//float TankSprite::getBulletDelta()
//{
//	return _mBulletDelta;
//}



