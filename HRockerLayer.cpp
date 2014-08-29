#include "HRockerLayer.h"
#include "MapLayer.h"
#include "TankSprite.h"

bool HRockerLayer::init()
{
	do
	{
		CC_BREAK_IF(!cocos2d::Layer::init());
		AddEventTouch();
		return true;
	} while (0);
	return false;
}


void HRockerLayer::Active()
{
	if (!_active)
	{
		_active = true;
		//schedule(schedule_selector(HRockerLayer::update));
	}
}

void HRockerLayer::Inactive()
{
	if (_active)
	{
		_active = false;
		//unschedule(schedule_selector(HRockerLayer::update));
	}

}

cocos2d::Vec2 HRockerLayer::getDirection()
{
	auto direction = ccpNormalize(ccpSub(_centerPoint, _currentPoint));
	//log("direction.x=%d,direction.y=%d", direction.x, direction.y);
	return direction;
}

HRockerLayer* HRockerLayer::HRockerWithCenter(Vec2 aPoint, float aRadius, Sprite* aJsSprite, Sprite* aJsBg, bool _isFollowRole)
{
	HRockerLayer* jstick = HRockerLayer::create();
	jstick->initWithCenter(aPoint, aRadius, aJsSprite, aJsBg, _isFollowRole);
	return jstick;
	return NULL;
}

HRockerLayer* HRockerLayer::initWithCenter(Vec2 aPoint, float aRadius, Sprite* aJsSprite, Sprite* aJsBg, bool _isFollowRole)
{
	this->_isFollowRole = _isFollowRole;
	_active = false;
	_radius = aRadius;
	if (!_isFollowRole
		)
	{
		_centerPoint = aPoint;
	}
	else
	{
		_centerPoint = Vec2(0, 0);
	}
	_currentPoint = _centerPoint;
	_jsSprite = aJsSprite;
	_jsSprite->setPosition(_centerPoint);
	aJsBg->setPosition(_centerPoint);
	aJsBg->setTag(88);
	this->addChild(aJsBg);
	this->addChild(_jsSprite);
	if (_isFollowRole)
	{
		this->setVisible(true);
	}
	this->Active();
	return this;
	return NULL;
}

float HRockerLayer::getVelocity()
{
	return ccpDistance(_centerPoint, _currentPoint);
	return 0;
}

void HRockerLayer::update(float delta)
{
	_jsSprite->setPosition(ccpAdd(_jsSprite->getPosition(), ccpMult(ccpSub(_currentPoint, _jsSprite->getPosition()), 0.5)));
	static float deltaTimes = 0.0f;
	deltaTimes += delta;
	if (deltaTimes>=0.2f)
	{
		deltaTimes = 0;
		_order = CalculateRetation();
	}
	
	switch (_order)
	{
	case cmdNothing:
		//log("cmdNothing");
		break;
	case cmdGoUP:
		//log("cmdGoUP");
		break;
	case cmdGoRight:
		//log("cmdGoRight");
		break;
	case cmdGoDown:
		//log("cmdGoDown");
		break;
	case cmdGoLeft:
		//log("cmdGoLeft");
		break;
	case cmdFire:
		//log("cmdFire");
		break;
	default:
		break;
	}
	//moveTank();

}


bool HRockerLayer::TouchBegan(Touch *pTouch, Event *pEvent)
{
	if (!_active)
	{
		return false;
	}
	this->setVisible(true);
	Vec2 touchpoint = pTouch->getLocationInView();
	touchpoint = Director::getInstance()->convertToGL(touchpoint);
	if (!_isFollowRole)
	{
		if (ccpDistance(touchpoint,_centerPoint)>_radius)
		{
			return false;
		}
	}
	_currentPoint = touchpoint;
	if (_isFollowRole)
	{
		_centerPoint = _currentPoint;
		_jsSprite->setPosition(_currentPoint);
		this->getChildByTag(88)->setPosition(_currentPoint);
	}
	return true;
}

void HRockerLayer::TouchMoved(Touch *pTouch, Event *pEvent)
{
	Vec2 touchpoint = pTouch->getLocationInView();
	touchpoint = Director::getInstance()->convertToGL(touchpoint);
	if (ccpDistance(touchpoint,_centerPoint)>_radius)
	{
		_currentPoint = ccpAdd(_centerPoint, ccpMult(ccpNormalize(ccpSub(touchpoint, _centerPoint)), _radius));
	}
	else
	{
		_currentPoint = touchpoint;
	}
	//moveTank();
}

void HRockerLayer::TouchEnded(Touch *pTouch, Event *pEvent)
{
	_currentPoint = _centerPoint;
	if (_isFollowRole)
	{
		this->setVisible(true);
	}
}

void HRockerLayer::AddEventTouch()
{

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HRockerLayer::TouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HRockerLayer::TouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HRockerLayer::TouchEnded, this);
	listener->setSwallowTouches(true);//是否向下传递
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}



enumOrder HRockerLayer::CalculateRetation()
{
	auto direction = getDirection();
	auto velocity = getVelocity();

	auto angle = atan2(direction.x, direction.y) * 180 / 3.14;
	if (angle == 0)
	{
		return cmdNothing;
	}
	if (angle < -45 && angle >-135) return cmdGoRight;
	if (angle > 45 && angle <135) return cmdGoLeft;
	if (angle < 45 && angle > -45) return cmdGoDown;
	if (angle >135 || angle < -135) return cmdGoUP;
}

enumOrder HRockerLayer::getRetation()
{
	return _order;
}

